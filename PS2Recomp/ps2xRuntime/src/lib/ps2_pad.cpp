#include "runtime/ps2_pad.h"
#include "ps2_host_backend.h"
#include <cstdlib>
#include <cstring>

namespace
{
    constexpr uint8_t kPadAnalogMarker = 0x73;
    constexpr uint8_t kPadStickCenter = 0x80;

    constexpr uint16_t PAD_LEFT = 0x0080u;
    constexpr uint16_t PAD_DOWN = 0x0040u;
    constexpr uint16_t PAD_RIGHT = 0x0020u;
    constexpr uint16_t PAD_UP = 0x0010u;
    constexpr uint16_t PAD_START = 0x0008u;
    constexpr uint16_t PAD_R3 = 0x0004u;
    constexpr uint16_t PAD_L3 = 0x0002u;
    constexpr uint16_t PAD_SELECT = 0x0001u;
    constexpr uint16_t PAD_SQUARE = 0x8000u;
    constexpr uint16_t PAD_CROSS = 0x4000u;
    constexpr uint16_t PAD_CIRCLE = 0x2000u;
    constexpr uint16_t PAD_TRIANGLE = 0x1000u;
    constexpr uint16_t PAD_R1 = 0x0800u;
    constexpr uint16_t PAD_L1 = 0x0400u;
    constexpr uint16_t PAD_R2 = 0x0200u;
    constexpr uint16_t PAD_L2 = 0x0100u;
}

bool PSPadBackend::readState(int /*port*/, int /*slot*/, uint8_t *data, size_t size)
{
    if (!data || size < 32)
        return false;

    std::memset(data, 0, 32);
    data[0] = 0x01;
    data[1] = kPadAnalogMarker;
    data[2] = 0xFF;
    data[3] = 0xFF;
    data[4] = data[5] = data[6] = data[7] = kPadStickCenter;

    uint16_t btns = 0xFFFFu;
    constexpr int kGamepad = 0;
    const bool useGamepad = IsGamepadAvailable(kGamepad);
    auto clearBit = [&btns](uint16_t mask)
    { btns &= ~mask; };

    // Tobiichi DMC5 Control Layout:
    // When enabled (via TOBIICHI_DMC5_CONTROLS=1, default 1):
    // Gamepad:
    //   Y (Triangle) -> Light/Normal Melee Attack (Square in GoW)
    //   B (Circle)   -> Heavy Melee Attack (Triangle in GoW)
    //   X (Square)   -> Grab / Special Interact (Circle in GoW)
    //   A (Cross)    -> Jump (Cross in GoW)
    //   LB (L1)      -> Parry / Block (L1 in GoW)
    //   RB (R1)      -> Lock-on / Combat Stance (R1 in GoW)
    //   LT (L2)      -> Magic / Devil Trigger (R2 in GoW)
    //   RT (R2)      -> Sub-weapon switch / Magic toggle (L2 in GoW)
    static const bool dmc5Controls = [] {
        const char *val = std::getenv("TOBIICHI_DMC5_CONTROLS");
        return val == nullptr || std::strcmp(val, "0") != 0;
    }();

    if (useGamepad)
    {
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
            clearBit(PAD_UP);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            clearBit(PAD_DOWN);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            clearBit(PAD_LEFT);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            clearBit(PAD_RIGHT);

        if (dmc5Controls)
        {
            // DMC5 mapping
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) // A -> Jump
                clearBit(PAD_CROSS);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) // B -> Heavy Attack
                clearBit(PAD_TRIANGLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) // X -> Grab / Interact
                clearBit(PAD_CIRCLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) // Y -> Light Attack
                clearBit(PAD_SQUARE);

            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) // LB -> Block / Parry
                clearBit(PAD_L1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) // RB -> Stance / Charge
                clearBit(PAD_R1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) // LT -> Magic
                clearBit(PAD_R2);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) // RT -> Magic Toggle / Secondary
                clearBit(PAD_L2);
        }
        else
        {
            // Classic PS2 GoW layout
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
                clearBit(PAD_CROSS);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
                clearBit(PAD_CIRCLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                clearBit(PAD_SQUARE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP))
                clearBit(PAD_TRIANGLE);

            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
                clearBit(PAD_L1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
                clearBit(PAD_R1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
                clearBit(PAD_L2);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
                clearBit(PAD_R2);
        }

        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            clearBit(PAD_START);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_MIDDLE_LEFT))
            clearBit(PAD_SELECT);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_THUMB))
            clearBit(PAD_L3);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_THUMB))
            clearBit(PAD_R3);

        float lx = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_LEFT_X);
        float ly = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_LEFT_Y);
        float rx = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_RIGHT_X);
        float ry = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_RIGHT_Y);
        data[6] = static_cast<uint8_t>(128 + lx * 127);
        data[7] = static_cast<uint8_t>(128 + ly * 127);
        data[4] = static_cast<uint8_t>(128 + rx * 127);
        data[5] = static_cast<uint8_t>(128 + ry * 127);
    }
    else
    {
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            clearBit(PAD_UP);
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            clearBit(PAD_DOWN);
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            clearBit(PAD_LEFT);
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            clearBit(PAD_RIGHT);

        if (dmc5Controls)
        {
            // DMC5 PC style keyboard layout:
            // Space -> Jump
            // J -> Light Attack (Square)
            // I -> Heavy Attack (Triangle)
            // K -> Grab / Special (Circle)
            // Shift -> Block / Parry (L1)
            // E -> Lock-on / Combat (R1)
            // Q -> Magic (R2)
            if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_X))
                clearBit(PAD_CROSS);
            if (IsKeyDown(KEY_I) || IsKeyDown(KEY_V))
                clearBit(PAD_TRIANGLE);
            if (IsKeyDown(KEY_K) || IsKeyDown(KEY_C))
                clearBit(PAD_CIRCLE);
            if (IsKeyDown(KEY_J) || IsKeyDown(KEY_Z))
                clearBit(PAD_SQUARE);

            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                clearBit(PAD_L1);
            if (IsKeyDown(KEY_E))
                clearBit(PAD_R1);
            if (IsKeyDown(KEY_Q))
                clearBit(PAD_R2);
            if (IsKeyDown(KEY_R))
                clearBit(PAD_L2);
        }
        else
        {
            if (IsKeyDown(KEY_X) || IsKeyDown(KEY_SPACE))
                clearBit(PAD_CROSS);
            if (IsKeyDown(KEY_C) || IsKeyDown(KEY_ESCAPE))
                clearBit(PAD_CIRCLE);
            if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_KP_0))
                clearBit(PAD_SQUARE);
            if (IsKeyDown(KEY_V) || IsKeyDown(KEY_KP_1))
                clearBit(PAD_TRIANGLE);
            if (IsKeyDown(KEY_Q))
                clearBit(PAD_L1);
            if (IsKeyDown(KEY_E))
                clearBit(PAD_R1);
            if (IsKeyDown(KEY_LEFT_SHIFT))
                clearBit(PAD_L2);
            if (IsKeyDown(KEY_RIGHT_SHIFT))
                clearBit(PAD_R2);
        }

        if (IsKeyDown(KEY_ENTER))
            clearBit(PAD_START);
        if (IsKeyDown(KEY_TAB))
            clearBit(PAD_SELECT);
    }

    data[2] = static_cast<uint8_t>(btns & 0xFF);
    data[3] = static_cast<uint8_t>(btns >> 8);
    return true;
}
