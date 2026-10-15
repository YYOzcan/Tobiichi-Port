// GOW-Port: Windows gamepad rumble (raylib's GLFW backend has none): XInput pads, and Sony DualShock 4 / DualSense
// pads through their HID output report (they are not XInput devices unless Steam or DS4Windows wraps them). The DLLs
// are loaded at run time, so the runner needs no import libraries; without them (or without a pad) rumble is off.
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <xinput.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace
{
bool xinputRumble(uint16_t lowFrequency, uint16_t highFrequency)
{
    using GetStateFn = DWORD(WINAPI *)(DWORD, XINPUT_STATE *);
    using SetStateFn = DWORD(WINAPI *)(DWORD, XINPUT_VIBRATION *);
    static const auto functions = [] {
        HMODULE module = LoadLibraryA("xinput1_4.dll");
        if (!module)
            module = LoadLibraryA("xinput9_1_0.dll");
        return std::pair<GetStateFn, SetStateFn>(
            module ? reinterpret_cast<GetStateFn>(GetProcAddress(module, "XInputGetState")) : nullptr,
            module ? reinterpret_cast<SetStateFn>(GetProcAddress(module, "XInputSetState")) : nullptr);
    }();
    if (!functions.first || !functions.second)
        return false;
    // raylib's gamepad index does not map to an XInput user index; every connected XInput pad gets the state.
    XINPUT_VIBRATION vibration{lowFrequency, highFrequency};
    bool any = false;
    for (DWORD user = 0; user < XUSER_MAX_COUNT; ++user)
    {
        XINPUT_STATE state{};
        if (functions.first(user, &state) == ERROR_SUCCESS)
            any = functions.second(user, &vibration) == ERROR_SUCCESS || any;
    }
    return any;
}

// ---- Sony pads over HID (report layouts as in Linux hid-sony / hid-playstation) ----

struct HidAttributes
{
    ULONG Size;
    USHORT VendorID, ProductID, VersionNumber;
};
struct HidCaps
{
    USHORT Usage, UsagePage, InputReportByteLength, OutputReportByteLength, FeatureReportByteLength, Reserved[17];
    USHORT counts[10];
};
struct DeviceInterfaceData
{
    DWORD cbSize;
    GUID InterfaceClassGuid;
    DWORD Flags;
    ULONG_PTR Reserved;
};

enum class SonyKind
{
    DualShock4,
    DualSense
};

struct SonyPad
{
    HANDLE handle;
    SonyKind kind;
    bool bluetooth;
    size_t reportLength; // the device's output report length (WriteFile needs exactly this size)
    uint8_t sequence;
};

uint32_t crc32(uint32_t crc, const uint8_t *data, size_t size)
{
    crc = ~crc;
    for (size_t i = 0; i < size; ++i)
    {
        crc ^= data[i];
        for (int bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}

// Bluetooth output reports end with a CRC-32 over the HID output header byte 0xA2 and the first 74 report bytes.
void sealBluetoothReport(uint8_t *report)
{
    const uint8_t header = 0xA2;
    const uint32_t crc = crc32(crc32(0, &header, 1), report, 74);
    std::memcpy(report + 74, &crc, 4);
}

std::vector<SonyPad> openSonyPads()
{
    std::vector<SonyPad> pads;
    HMODULE hid = LoadLibraryA("hid.dll"), setup = LoadLibraryA("setupapi.dll");
    if (!hid || !setup)
        return pads;
    using GetHidGuidFn = void(WINAPI *)(GUID *);
    using GetAttributesFn = BOOLEAN(WINAPI *)(HANDLE, HidAttributes *);
    using GetPreparsedFn = BOOLEAN(WINAPI *)(HANDLE, void **);
    using FreePreparsedFn = BOOLEAN(WINAPI *)(void *);
    using GetCapsFn = LONG(WINAPI *)(void *, HidCaps *);
    using GetClassDevsFn = HANDLE(WINAPI *)(const GUID *, const char *, HWND, DWORD);
    using EnumInterfacesFn = BOOL(WINAPI *)(HANDLE, void *, const GUID *, DWORD, DeviceInterfaceData *);
    using GetDetailFn = BOOL(WINAPI *)(HANDLE, DeviceInterfaceData *, void *, DWORD, DWORD *, void *);
    using DestroyListFn = BOOL(WINAPI *)(HANDLE);
    const auto getHidGuid = reinterpret_cast<GetHidGuidFn>(GetProcAddress(hid, "HidD_GetHidGuid"));
    const auto getAttributes = reinterpret_cast<GetAttributesFn>(GetProcAddress(hid, "HidD_GetAttributes"));
    const auto getPreparsed = reinterpret_cast<GetPreparsedFn>(GetProcAddress(hid, "HidD_GetPreparsedData"));
    const auto freePreparsed = reinterpret_cast<FreePreparsedFn>(GetProcAddress(hid, "HidD_FreePreparsedData"));
    const auto getCaps = reinterpret_cast<GetCapsFn>(GetProcAddress(hid, "HidP_GetCaps"));
    const auto getClassDevs = reinterpret_cast<GetClassDevsFn>(GetProcAddress(setup, "SetupDiGetClassDevsA"));
    const auto enumInterfaces = reinterpret_cast<EnumInterfacesFn>(GetProcAddress(setup, "SetupDiEnumDeviceInterfaces"));
    const auto getDetail = reinterpret_cast<GetDetailFn>(GetProcAddress(setup, "SetupDiGetDeviceInterfaceDetailA"));
    const auto destroyList = reinterpret_cast<DestroyListFn>(GetProcAddress(setup, "SetupDiDestroyDeviceInfoList"));
    if (!getHidGuid || !getAttributes || !getPreparsed || !freePreparsed || !getCaps || !getClassDevs || !enumInterfaces || !getDetail ||
        !destroyList)
        return pads;

    GUID hidGuid{};
    getHidGuid(&hidGuid);
    const HANDLE list = getClassDevs(&hidGuid, nullptr, nullptr, 0x2 /*DIGCF_PRESENT*/ | 0x10 /*DIGCF_DEVICEINTERFACE*/);
    if (list == INVALID_HANDLE_VALUE)
        return pads;
    for (DWORD index = 0;; ++index)
    {
        DeviceInterfaceData data{sizeof(DeviceInterfaceData)};
        if (!enumInterfaces(list, nullptr, &hidGuid, index, &data))
            break;
        DWORD size = 0;
        getDetail(list, &data, nullptr, 0, &size, nullptr);
        if (size < sizeof(DWORD) + 2)
            continue;
        std::vector<uint8_t> detail(size);
        *reinterpret_cast<DWORD *>(detail.data()) = sizeof(void *) == 8 ? 8 : 5; // SP_DEVICE_INTERFACE_DETAIL_DATA_A::cbSize
        if (!getDetail(list, &data, detail.data(), size, nullptr, nullptr))
            continue;
        const char *path = reinterpret_cast<const char *>(detail.data() + sizeof(DWORD));
        const HANDLE handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
            continue;
        HidAttributes attributes{sizeof(HidAttributes)};
        HidCaps caps{};
        void *preparsed = nullptr;
        bool keep = false;
        if (getAttributes(handle, &attributes) && attributes.VendorID == 0x054C && getPreparsed(handle, &preparsed))
        {
            getCaps(preparsed, &caps);
            freePreparsed(preparsed);
            const USHORT product = attributes.ProductID;
            const bool ds4 = product == 0x05C4 || product == 0x09CC || product == 0x0BA0;
            const bool dualSense = product == 0x0CE6 || product == 0x0DF2;
            // the game-pad collection (usage page 1, usage 5) carries the output report; USB reports are 32 / 48
            // bytes, Bluetooth ones 78 or more
            if ((ds4 || dualSense) && caps.UsagePage == 1 && caps.Usage == 5 && caps.OutputReportByteLength >= 32)
            {
                // Bluetooth: the first output report switches the pad to its extended input report, which DirectInput
                // (raylib's GLFW input) may not read any more, so it is opt-in (GOW_PAD_BT_RUMBLE=1)
                static const bool bluetoothRumble = std::getenv("GOW_PAD_BT_RUMBLE") != nullptr;
                const bool bluetooth = caps.OutputReportByteLength >= 78;
                std::fprintf(stderr, "[pad] rumble: %s over %s%s\n", ds4 ? "DualShock 4" : "DualSense", bluetooth ? "Bluetooth" : "USB",
                             bluetooth && !bluetoothRumble ? " (off: set GOW_PAD_BT_RUMBLE=1)" : "");
                if (!bluetooth || bluetoothRumble)
                {
                    pads.push_back({handle, ds4 ? SonyKind::DualShock4 : SonyKind::DualSense, bluetooth, caps.OutputReportByteLength, 0});
                    keep = true;
                }
            }
        }
        if (!keep)
            CloseHandle(handle);
    }
    destroyList(list);
    return pads;
}

// large = strong (left, low-frequency) motor 0-255; small = weak (right, high-frequency) motor 0-255
bool sendSonyRumble(SonyPad &pad, uint8_t large, uint8_t small)
{
    std::vector<uint8_t> report(pad.reportLength, 0);
    if (pad.kind == SonyKind::DualShock4)
    {
        if (!pad.bluetooth)
        {
            report[0] = 0x05;
            report[1] = 0x01; // flags: motors only (the light bar and its flash stay as they are)
            report[4] = small;
            report[5] = large;
        }
        else
        {
            report[0] = 0x11;
            report[1] = 0xC0; // HID report with CRC
            report[3] = 0x01;
            report[6] = small;
            report[7] = large;
            sealBluetoothReport(report.data());
        }
    }
    else
    {
        // the common part: valid_flag0 (compatible vibration + haptics select), valid_flag1, right motor, left motor;
        // valid_flag2 bit 2 is the vibration flag of newer firmware
        size_t common = 1;
        if (pad.bluetooth)
        {
            report[0] = 0x31;
            report[1] = static_cast<uint8_t>(pad.sequence << 4);
            pad.sequence = static_cast<uint8_t>((pad.sequence + 1u) & 0xFu);
            report[2] = 0x10;
            common = 3;
        }
        else
            report[0] = 0x02;
        report[common + 0] = 0x03;
        report[common + 2] = small;
        report[common + 3] = large;
        report[common + 38] = 0x04;
        if (pad.bluetooth)
            sealBluetoothReport(report.data());
    }
    DWORD written = 0;
    return WriteFile(pad.handle, report.data(), static_cast<DWORD>(report.size()), &written, nullptr) && written == report.size();
}

bool sonyRumble(uint8_t large, uint8_t small)
{
    static std::vector<SonyPad> pads;
    static ULONGLONG lastScan = 0;
    // (re)scan when there is no pad, at most every 2 s, so a pad plugged in later is found
    const ULONGLONG now = GetTickCount64();
    if (pads.empty() && (lastScan == 0 || now - lastScan >= 2000))
    {
        lastScan = now;
        pads = openSonyPads();
    }
    bool any = false;
    for (size_t i = 0; i < pads.size();)
        if (sendSonyRumble(pads[i], large, small))
        {
            any = true;
            ++i;
        }
        else
        {
            CloseHandle(pads[i].handle); // unplugged
            pads.erase(pads.begin() + static_cast<std::ptrdiff_t>(i));
        }
    return any;
}
} // namespace

bool ps2PadWindowsRumble(uint8_t large, bool small)
{
    const bool xinput = xinputRumble(static_cast<uint16_t>(large * 257u), small ? 0xFFFFu : 0u);
    const bool sony = sonyRumble(large, small ? 0xFFu : 0u);
    return xinput || sony;
}
#endif
