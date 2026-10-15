// GOW-Port: sound output on a chosen device. raylib's audio always opens the system default output; when a device is
// named (GOW_AUDIO_DEVICE=<part of its name>, or the first line of %LOCALAPPDATA%\GodOfWarNative\audio_device.txt so
// every instance follows it: test runs; play.cmd sets GOW_AUDIO_DEVICE=default for the system default output), the
// sound engine's stream is played on that device through miniaudio directly. The
// miniaudio implementation is raylib's own (compiled in raudio.c); the configuration macros below must stay identical
// to raudio.c's, because they change miniaudio's structure layouts.
#if !defined(PLATFORM_VITA)
#define MA_NO_JACK
#define MA_NO_WAV
#define MA_NO_FLAC
#define MA_NO_MP3
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_GENERATION
#define MA_COINIT_VALUE 2
#include "external/miniaudio.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

namespace
{
ma_context g_context;
ma_device g_device;
bool g_open = false;
void (*g_fill)(void *, unsigned int) = nullptr;

std::string lower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

std::string configuredName()
{
    if (const char *name = std::getenv("GOW_AUDIO_DEVICE"))
        return name;
    std::string name;
    if (const char *base = std::getenv("LOCALAPPDATA"))
    {
        std::ifstream file(std::string(base) + "\\GodOfWarNative\\audio_device.txt");
        std::getline(file, name);
    }
    while (!name.empty() && (name.back() == '\r' || name.back() == '\n' || name.back() == ' '))
        name.pop_back();
    return name;
}

void dataCallback(ma_device *, void *output, const void *, ma_uint32 frames)
{
    g_fill(output, frames);
}
} // namespace

// Opens the configured device for 16-bit stereo at sampleRate, pulling samples from fill. False when no device is
// configured or it cannot be opened (the caller then uses raylib's default output).
bool ps2AudioOpenNamedDevice(void (*fill)(void *, unsigned int), unsigned int sampleRate)
{
    const std::string wanted = lower(configuredName());
    if (wanted.empty() || wanted == "default" || g_open) // "default": the system default output (play.cmd)
        return false;
    if (ma_context_init(nullptr, 0, nullptr, &g_context) != MA_SUCCESS)
        return false;
    ma_device_info *devices = nullptr;
    ma_uint32 count = 0;
    const ma_device_info *chosen = nullptr;
    if (ma_context_get_devices(&g_context, &devices, &count, nullptr, nullptr) == MA_SUCCESS)
        for (ma_uint32 i = 0; i < count && !chosen; ++i)
            if (lower(devices[i].name).find(wanted) != std::string::npos)
                chosen = &devices[i];
    if (!chosen)
    {
        std::fprintf(stderr, "[audio] no output device matches \"%s\"; default output used. Devices:\n", wanted.c_str());
        for (ma_uint32 i = 0; i < count; ++i)
            std::fprintf(stderr, "[audio]   %s\n", devices[i].name);
        ma_context_uninit(&g_context);
        return false;
    }
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.pDeviceID = &chosen->id;
    config.playback.format = ma_format_s16;
    config.playback.channels = 2;
    config.sampleRate = sampleRate;
    config.periodSizeInFrames = 1024; // as the raylib stream (SetAudioStreamBufferSizeDefault(1024))
    config.dataCallback = dataCallback;
    g_fill = fill;
    if (ma_device_init(&g_context, &config, &g_device) != MA_SUCCESS)
    {
        ma_context_uninit(&g_context);
        return false;
    }
    if (ma_device_start(&g_device) != MA_SUCCESS)
    {
        ma_device_uninit(&g_device);
        ma_context_uninit(&g_context);
        return false;
    }
    g_open = true;
    std::fprintf(stderr, "[audio] output device: %s\n", chosen->name);
    return true;
}

void ps2AudioCloseNamedDevice()
{
    if (!g_open)
        return;
    ma_device_uninit(&g_device); // waits for the callback in progress
    ma_context_uninit(&g_context);
    g_open = false;
}
#endif
