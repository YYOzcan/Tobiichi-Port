// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#include "gs_gl.h"
#include "runtime/gs/gs_shared_present.h"

#include <array>
#include <atomic>
#include <clocale>
#include <cstdlib>
#include <cstdio>
#include <mutex>
#include <string_view>

// GOW-Port: presentación compartida (PS2X_GS_DIRECT_PRESENT, activa por defecto): el contexto del GS comparte
// texturas con el de la ventana y entrega cada cuadro como textura, sin leerlo a la RAM. Los huecos, los fences y la
// carga de las funciones de GL son comunes; la captura del contexto de la ventana y la creación de los contextos
// dependen de la plataforma (WGL en Windows, GLFW en Linux).
namespace
{
    struct SharedSlot
    {
        GSSharedPresent::Frame frame;
        GSGL::GLsync produced = nullptr;
        GSGL::GLsync consumed = nullptr;
        GSGL::GLuint hashBuffer = 0;
        GSGL::GLuint hashDeviceBuffer = 0;
        const uint32_t *hash = nullptr;
        bool reading = false;
    };

    std::mutex s_sharedMutex;
    std::array<SharedSlot, 8> s_sharedSlots;
    GSGL::Api s_hostApi;
    int s_readingSlot = -1;
    uint64_t s_sharedSequence = 0;
    std::atomic<bool> s_sharedActive{false};

    bool completed(const GSGL::Api &gl, GSGL::GLsync fence)
    {
        if (!fence)
            return true;
        const auto status = gl.ClientWaitSync(fence, 0u, 0u);
        return status == GSGL::kAlreadySignaled || status == GSGL::kConditionSatisfied;
    }

    void releaseReading()
    {
        if (s_readingSlot < 0)
            return;
        SharedSlot &slot = s_sharedSlots[s_readingSlot];
        slot.consumed = s_hostApi.FenceSync(GSGL::kSyncGpuCommandsComplete, 0u);
        s_hostApi.Flush();
        slot.reading = false;
        s_readingSlot = -1;
    }

    // GOW-Port: false = presentación por la RAM (lectura y subida de cada cuadro).
    bool directPresentEnabled()
    {
        const char *value = std::getenv("PS2X_GS_DIRECT_PRESENT");
        return !(value && *value == '0');
    }

    using ProcLoader = void *(*)(const char *);

    template <typename T>
    bool loadWith(ProcLoader proc, T &target, const char *name, std::string &missing)
    {
        target = reinterpret_cast<T>(proc(name));
        if (!target)
        {
            missing += missing.empty() ? name : std::string(", ") + name;
            return false;
        }
        return true;
    }

    // Funciones que necesita la ventana para esperar y señalar los fences de los huecos compartidos.
    bool loadHostApi(ProcLoader proc, GSGL::Api &api, std::string &missing)
    {
        loadWith(proc, api.FenceSync, "glFenceSync", missing);
        loadWith(proc, api.ClientWaitSync, "glClientWaitSync", missing);
        loadWith(proc, api.DeleteSync, "glDeleteSync", missing);
        loadWith(proc, api.Flush, "glFlush", missing);
        return missing.empty();
    }

    // Todas las funciones del contexto del GS; missing recoge solo las obligatorias.
    void loadContextApi(ProcLoader proc, GSGL::Api &a, std::string &missing)
    {
        const auto load = [proc](auto &target, const char *name, std::string &list) { return loadWith(proc, target, name, list); };
        load(a.GenBuffers, "glGenBuffers", missing);
        load(a.DeleteBuffers, "glDeleteBuffers", missing);
        load(a.BindBuffer, "glBindBuffer", missing);
        load(a.BufferData, "glBufferData", missing);
        load(a.BufferSubData, "glBufferSubData", missing);
        load(a.GetBufferSubData, "glGetBufferSubData", missing);
        load(a.BindBufferBase, "glBindBufferBase", missing);
        load(a.BindBufferRange, "glBindBufferRange", missing);
        load(a.ClearBufferData, "glClearBufferData", missing);
        load(a.CopyBufferSubData, "glCopyBufferSubData", missing);
        load(a.BufferStorage, "glBufferStorage", missing);
        load(a.MapBufferRange, "glMapBufferRange", missing);
        load(a.UnmapBuffer, "glUnmapBuffer", missing);
        load(a.GenQueries, "glGenQueries", missing);
        load(a.DeleteQueries, "glDeleteQueries", missing);
        load(a.BeginQuery, "glBeginQuery", missing);
        load(a.EndQuery, "glEndQuery", missing);
        load(a.GetQueryObjectui64v, "glGetQueryObjectui64v", missing);
        load(a.QueryCounter, "glQueryCounter", missing);
        load(a.CreateShader, "glCreateShader", missing);
        load(a.ShaderSource, "glShaderSource", missing);
        load(a.CompileShader, "glCompileShader", missing);
        load(a.GetShaderiv, "glGetShaderiv", missing);
        load(a.GetShaderInfoLog, "glGetShaderInfoLog", missing);
        load(a.DeleteShader, "glDeleteShader", missing);
        load(a.CreateProgram, "glCreateProgram", missing);
        load(a.AttachShader, "glAttachShader", missing);
        load(a.LinkProgram, "glLinkProgram", missing);
        load(a.GetProgramiv, "glGetProgramiv", missing);
        load(a.GetProgramInfoLog, "glGetProgramInfoLog", missing);
        load(a.ProgramParameteri, "glProgramParameteri", missing);
        load(a.GetProgramBinary, "glGetProgramBinary", missing);
        load(a.ProgramBinary, "glProgramBinary", missing);
        load(a.DeleteProgram, "glDeleteProgram", missing);
        load(a.UseProgram, "glUseProgram", missing);
        load(a.GetUniformLocation, "glGetUniformLocation", missing);
        load(a.Uniform1ui, "glUniform1ui", missing);
        load(a.Uniform4ui, "glUniform4ui", missing);
        load(a.Uniform1uiv, "glUniform1uiv", missing);
        load(a.DispatchCompute, "glDispatchCompute", missing);
        load(a.MemBarrier, "glMemoryBarrier", missing);
        load(a.FenceSync, "glFenceSync", missing);
        load(a.ClientWaitSync, "glClientWaitSync", missing);
        load(a.DeleteSync, "glDeleteSync", missing);
        load(a.Finish, "glFinish", missing);
        load(a.Flush, "glFlush", missing);
        load(a.GetError, "glGetError", missing);
        load(a.GetString, "glGetString", missing);
        load(a.GenTextures, "glGenTextures", missing);
        load(a.DeleteTextures, "glDeleteTextures", missing);
        load(a.BindTexture, "glBindTexture", missing);
        load(a.TexParameteri, "glTexParameteri", missing);
        load(a.TexImage2D, "glTexImage2D", missing);
        load(a.TexSubImage2D, "glTexSubImage2D", missing);

        std::string graphicsMissing;
        load(a.GenFramebuffers, "glGenFramebuffers", graphicsMissing);
        load(a.DeleteFramebuffers, "glDeleteFramebuffers", graphicsMissing);
        load(a.BindFramebuffer, "glBindFramebuffer", graphicsMissing);
        load(a.FramebufferParameteri, "glFramebufferParameteri", graphicsMissing);
        load(a.Viewport, "glViewport", graphicsMissing);
        load(a.DrawArrays, "glDrawArrays", graphicsMissing);
        load(a.GenVertexArrays, "glGenVertexArrays", graphicsMissing);
        load(a.DeleteVertexArrays, "glDeleteVertexArrays", graphicsMissing);
        load(a.BindVertexArray, "glBindVertexArray", graphicsMissing);
        load(a.Enable, "glEnable", graphicsMissing);
        load(a.Disable, "glDisable", graphicsMissing);
        std::string hwMissing;
        load(a.ActiveTexture, "glActiveTexture", hwMissing);
        load(a.FramebufferTexture2D, "glFramebufferTexture2D", hwMissing);
        load(a.CheckFramebufferStatus, "glCheckFramebufferStatus", hwMissing);
        load(a.BlendFuncSeparate, "glBlendFuncSeparate", hwMissing);
        load(a.BlendEquationSeparate, "glBlendEquationSeparate", hwMissing);
        load(a.BlendColor, "glBlendColor", hwMissing);
        load(a.ColorMask, "glColorMask", hwMissing);
        load(a.DepthMask, "glDepthMask", hwMissing);
        load(a.DepthFunc, "glDepthFunc", hwMissing);
        load(a.ClearColor, "glClearColor", hwMissing);
        load(a.ClearDepth, "glClearDepth", hwMissing);
        load(a.Clear, "glClear", hwMissing);
        load(a.Scissor, "glScissor", hwMissing);
        load(a.Uniform1i, "glUniform1i", hwMissing);
        load(a.Uniform1f, "glUniform1f", hwMissing);
        load(a.Uniform2f, "glUniform2f", hwMissing);
        load(a.Uniform4f, "glUniform4f", hwMissing);
        load(a.Uniform4i, "glUniform4i", hwMissing);
        load(a.VertexAttribPointer, "glVertexAttribPointer", hwMissing);
        load(a.VertexAttribIPointer, "glVertexAttribIPointer", hwMissing);
        load(a.EnableVertexAttribArray, "glEnableVertexAttribArray", hwMissing);
        load(a.DrawBuffers, "glDrawBuffers", hwMissing);
        load(a.ReadPixels, "glReadPixels", hwMissing);
        load(a.BlitFramebuffer, "glBlitFramebuffer", hwMissing);
        load(a.PixelStorei, "glPixelStorei", hwMissing);
        load(a.TextureBarrier, "glTextureBarrier", hwMissing);
        std::string copyMissing;
        load(a.CopyImageSubData, "glCopyImageSubData", copyMissing);
        a.hwRaster = graphicsMissing.empty() && hwMissing.empty();
        if (!a.hwRaster)
            std::fprintf(stderr, "[gs-gl] classic raster entry points missing: %s (graphics=%d)\n", hwMissing.c_str(), graphicsMissing.empty() ? 1 : 0);
        std::string parallelMissing;
        load(a.MaxShaderCompilerThreads, "glMaxShaderCompilerThreadsARB", parallelMissing);
        if (!a.MaxShaderCompilerThreads)
            load(a.MaxShaderCompilerThreads, "glMaxShaderCompilerThreadsKHR", parallelMissing);
        a.graphics = graphicsMissing.empty();
    }
}

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace
{
    constexpr int kContextMajorVersion = 0x2091;
    constexpr int kContextMinorVersion = 0x2092;
    constexpr int kContextFlags = 0x2094;
    constexpr int kContextProfileMask = 0x9126;
    constexpr int kContextCoreProfileBit = 0x0001;

    using CreateContextAttribs = HGLRC(WINAPI *)(HDC, HGLRC, const int *);

    HGLRC s_hostContext = nullptr;
    HDC s_hostDc = nullptr;
    PIXELFORMATDESCRIPTOR s_hostFormat{};
    int s_hostFormatIndex = 0;

    HMODULE openGlModule()
    {
        static HMODULE module = LoadLibraryA("opengl32.dll");
        return module;
    }

    void *loadProc(const char *name)
    {
        void *proc = reinterpret_cast<void *>(wglGetProcAddress(name));
        const auto value = reinterpret_cast<intptr_t>(proc);
        if (value == 0 || value == 1 || value == 2 || value == 3 || value == -1)
            proc = reinterpret_cast<void *>(GetProcAddress(openGlModule(), name));
        return proc;
    }

    LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
    {
        return DefWindowProcA(window, message, wparam, lparam);
    }
}

namespace GSSharedPresent
{
    void CaptureHostContext()
    {
        // GOW-Port: on by default; PS2X_GS_DIRECT_PRESENT=0 keeps the RAM (readback + upload) presentation.
        if (!directPresentEnabled())
            return;
        const HDC dc = wglGetCurrentDC();
        const HGLRC context = wglGetCurrentContext();
        if (!dc || !context)
            return;
        std::string missing;
        GSGL::Api api;
        if (!loadHostApi(loadProc, api, missing))
        {
            std::fprintf(stderr, "[gs-present] shared presentation unavailable: %s\n", missing.c_str());
            return;
        }
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        s_hostFormatIndex = GetPixelFormat(dc);
        if (!DescribePixelFormat(dc, s_hostFormatIndex, sizeof(s_hostFormat), &s_hostFormat))
            return;
        s_hostApi = api;
        s_hostContext = context;
        s_hostDc = dc;
        wglMakeCurrent(nullptr, nullptr);
    }

    void RestoreHostContext()
    {
        if (s_hostDc && s_hostContext)
            wglMakeCurrent(s_hostDc, s_hostContext);
    }

    void ShutdownHost()
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        releaseReading();
        s_sharedActive.store(false, std::memory_order_release);
        s_hostContext = nullptr;
        s_hostDc = nullptr;
    }
}

namespace GSGL
{
    bool Context::Create(std::string &error)
    {
        Destroy();
        WNDCLASSA windowClass{};
        windowClass.style = CS_OWNDC;
        windowClass.lpfnWndProc = windowProc;
        windowClass.hInstance = GetModuleHandleA(nullptr);
        windowClass.lpszClassName = "PS2XGSGpuContext";
        RegisterClassA(&windowClass);
        HWND window = CreateWindowExA(0, windowClass.lpszClassName, "gs", WS_OVERLAPPEDWINDOW, 0, 0, 16, 16, nullptr, nullptr,
                                      windowClass.hInstance, nullptr);
        if (!window)
        {
            error = "CreateWindowEx failed";
            return false;
        }
        HDC dc = GetDC(window);
        PIXELFORMATDESCRIPTOR descriptor{};
        descriptor.nSize = sizeof(descriptor);
        descriptor.nVersion = 1;
        descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        descriptor.iPixelType = PFD_TYPE_RGBA;
        descriptor.cColorBits = 32;
        const int format = s_hostContext ? s_hostFormatIndex : ChoosePixelFormat(dc, &descriptor);
        if (s_hostContext)
            descriptor = s_hostFormat;
        if (format == 0 || !SetPixelFormat(dc, format, &descriptor))
        {
            ReleaseDC(window, dc);
            DestroyWindow(window);
            error = "no pixel format";
            return false;
        }
        HGLRC legacy = wglCreateContext(dc);
        if (!legacy || !wglMakeCurrent(dc, legacy))
        {
            if (legacy)
                wglDeleteContext(legacy);
            ReleaseDC(window, dc);
            DestroyWindow(window);
            error = "wglCreateContext failed";
            return false;
        }
        const auto createAttribs = reinterpret_cast<CreateContextAttribs>(wglGetProcAddress("wglCreateContextAttribsARB"));
        HGLRC context = nullptr;
        if (createAttribs)
        {
            const int attributes[] = {kContextMajorVersion, 4, kContextMinorVersion, 6, kContextProfileMask, kContextCoreProfileBit,
                                      kContextFlags, 0, 0};
            context = createAttribs(dc, s_hostContext, attributes);
            m_shared = context && s_hostContext;
            if (!context && s_hostContext)
            {
                std::fprintf(stderr, "[gs-present] WGL sharing failed (%lu); using RAM presentation\n", GetLastError());
                context = createAttribs(dc, nullptr, attributes);
            }
        }
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(legacy);
        if (!context || !wglMakeCurrent(dc, context))
        {
            if (context)
                wglDeleteContext(context);
            ReleaseDC(window, dc);
            DestroyWindow(window);
            error = "OpenGL 4.6 core context unavailable";
            return false;
        }
        m_window = window;
        m_dc = dc;
        m_context = context;

        std::string missing;
        loadContextApi(loadProc, m_api, missing);
        if (!missing.empty())
        {
            error = "missing GL functions: " + missing;
            Destroy();
            return false;
        }
        if (m_shared)
        {
            s_sharedActive.store(true, std::memory_order_release);
            std::fprintf(stderr, "[gs-present] shared GPU textures active\n");
        }
        return true;
    }

    void *Context::CreateWorker() const
    {
        const auto createAttribs = reinterpret_cast<CreateContextAttribs>(wglGetProcAddress("wglCreateContextAttribsARB"));
        if (!createAttribs || !m_context || !m_dc)
            return nullptr;
        const int attributes[] = {kContextMajorVersion, 4, kContextMinorVersion, 6, kContextProfileMask, kContextCoreProfileBit,
                                  kContextFlags, 0, 0};
        return createAttribs(static_cast<HDC>(m_dc), static_cast<HGLRC>(m_context), attributes);
    }

    bool Context::MakeWorkerCurrent(void *worker) const
    {
        return worker && m_dc && wglMakeCurrent(static_cast<HDC>(m_dc), static_cast<HGLRC>(worker));
    }

    void Context::DestroyWorker(void *worker)
    {
        if (!worker)
            return;
        if (wglGetCurrentContext() == static_cast<HGLRC>(worker))
            wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(static_cast<HGLRC>(worker));
    }

    void Context::Destroy()
    {
        if (m_context)
        {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(static_cast<HGLRC>(m_context));
            m_context = nullptr;
        }
        if (m_dc && m_window)
            ReleaseDC(static_cast<HWND>(m_window), static_cast<HDC>(m_dc));
        m_dc = nullptr;
        if (m_window)
            DestroyWindow(static_cast<HWND>(m_window));
        m_window = nullptr;
        m_api = {};
        m_shared = false;
    }
}
#else
// GOW-Port (Linux): contextos de GLFW (la misma biblioteca que usa raylib para la ventana). El contexto del GS es una
// ventana oculta que comparte objetos con la del juego; los contextos de los hilos auxiliares comparten con el del GS.
#include <GLFW/glfw3.h>

namespace
{
    // GOW-Port: ventana del juego (raylib), cuyo contexto comparte texturas con el del GS.
    GLFWwindow *s_hostWindow = nullptr;

    void *loadProc(const char *name)
    {
        return reinterpret_cast<void *>(glfwGetProcAddress(name));
    }

    void contextHints(int minor)
    {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
}

namespace GSSharedPresent
{
    void CaptureHostContext()
    {
        if (!directPresentEnabled())
            return;
        GLFWwindow *window = glfwGetCurrentContext();
        if (!window)
            return;
        std::string missing;
        GSGL::Api api;
        if (!loadHostApi(loadProc, api, missing))
        {
            std::fprintf(stderr, "[gs-present] shared presentation unavailable: %s\n", missing.c_str());
            return;
        }
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        s_hostApi = api;
        s_hostWindow = window;
    }

    void RestoreHostContext()
    {
        if (s_hostWindow && glfwGetCurrentContext() != s_hostWindow)
            glfwMakeContextCurrent(s_hostWindow);
    }

    void ShutdownHost()
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        releaseReading();
        s_sharedActive.store(false, std::memory_order_release);
        s_hostWindow = nullptr;
    }
}

namespace GSGL
{
    bool Context::Create(std::string &error)
    {
        Destroy();
        if (!glfwInit())
        {
            error = "Failed to initialize GLFW";
            return false;
        }
        // GOW-Port: glfwInit pone LC_CTYPE del sistema (tr_TR rompe tolower/toupper ASCII de 'I'/'i'); se restaura "C".
        std::setlocale(LC_CTYPE, "C");
        contextHints(6);
        GLFWwindow *window = glfwCreateWindow(16, 16, "gs", nullptr, s_hostWindow);
        m_shared = window && s_hostWindow;
        if (!window && s_hostWindow)
        {
            std::fprintf(stderr, "[gs-present] GLX/EGL sharing failed; using RAM presentation\n");
            window = glfwCreateWindow(16, 16, "gs", nullptr, nullptr);
        }
        if (!window)
        {
            error = "OpenGL 4.6 core context unavailable";
            return false;
        }
        glfwMakeContextCurrent(window);
        m_window = window;
        m_context = window;

        std::string missing;
        loadContextApi(loadProc, m_api, missing);
        if (!missing.empty())
        {
            error = "missing GL functions: " + missing;
            Destroy();
            return false;
        }
        if (m_shared)
        {
            s_sharedActive.store(true, std::memory_order_release);
            std::fprintf(stderr, "[gs-present] shared GPU textures active\n");
        }
        return true;
    }

    void *Context::CreateWorker() const
    {
        if (!m_window)
            return nullptr;
        contextHints(6);
        return glfwCreateWindow(16, 16, "gs-worker", nullptr, static_cast<GLFWwindow *>(m_window));
    }

    bool Context::MakeWorkerCurrent(void *worker) const
    {
        if (!worker)
            return false;
        glfwMakeContextCurrent(static_cast<GLFWwindow *>(worker));
        return glfwGetCurrentContext() == static_cast<GLFWwindow *>(worker);
    }

    void Context::DestroyWorker(void *worker)
    {
        if (!worker)
            return;
        if (glfwGetCurrentContext() == static_cast<GLFWwindow *>(worker))
            glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(static_cast<GLFWwindow *>(worker));
    }

    void Context::Destroy()
    {
        if (m_window)
        {
            if (glfwGetCurrentContext() == static_cast<GLFWwindow *>(m_window))
                glfwMakeContextCurrent(nullptr);
            glfwDestroyWindow(static_cast<GLFWwindow *>(m_window));
        }
        m_window = nullptr;
        m_context = nullptr;
        m_dc = nullptr;
        m_api = {};
        m_shared = false;
    }
}
#endif

namespace GSSharedPresent
{
    bool Active()
    {
        return s_sharedActive.load(std::memory_order_acquire);
    }

    bool Acquire(Frame &frame)
    {
        if (!Active())
            return false;
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        int newest = -1;
        uint64_t sequence = s_readingSlot >= 0 ? s_sharedSlots[s_readingSlot].frame.sequence : 0u;
        for (int i = 0; i < static_cast<int>(s_sharedSlots.size()); ++i)
        {
            const SharedSlot &slot = s_sharedSlots[i];
            if (!slot.reading && slot.frame.sequence > sequence && slot.produced && completed(s_hostApi, slot.produced))
            {
                newest = i;
                sequence = slot.frame.sequence;
            }
        }
        if (newest >= 0)
        {
            releaseReading();
            SharedSlot &slot = s_sharedSlots[newest];
            s_hostApi.DeleteSync(slot.produced);
            slot.produced = nullptr;
            if (slot.frame.hashValid)
                slot.frame.contentHash = static_cast<uint64_t>(slot.hash[0]) | (static_cast<uint64_t>(slot.hash[1]) << 32u);
            slot.reading = true;
            s_readingSlot = newest;
        }
        if (s_readingSlot < 0)
            return false;
        frame = s_sharedSlots[s_readingSlot].frame;
        return true;
    }
}

namespace GSGL
{
    bool SharedAvailable(const Api &gl)
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        for (const SharedSlot &slot : s_sharedSlots)
            if (!slot.reading && completed(gl, slot.produced) && completed(gl, slot.consumed))
                return true;
        return false;
    }

    bool PublishShared(const Api &gl, GLuint buffer, uint32_t width, uint32_t height, uint64_t renderSequence,
                       uint32_t displayFbp, uint32_t sourceFbp, bool usedPreferred, bool blank,
                       uint64_t vsyncTick, GLuint hashProgram, GLint hashLocation)
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        if (!s_sharedActive.load(std::memory_order_relaxed))
            return false;
        SharedSlot *available = nullptr;
        for (SharedSlot &slot : s_sharedSlots)
        {
            if (slot.reading || !completed(gl, slot.produced) || !completed(gl, slot.consumed))
                continue;
            if (!available || slot.frame.sequence < available->frame.sequence)
                available = &slot;
        }
        if (!available)
            return false;
        SharedSlot &slot = *available;
        if (slot.produced)
            gl.DeleteSync(slot.produced);
        if (slot.consumed)
            gl.DeleteSync(slot.consumed);
        slot.produced = slot.consumed = nullptr;
        slot.frame.hashValid = false;
        if (hashProgram)
        {
            if (!slot.hashBuffer)
            {
                gl.GenBuffers(1, &slot.hashBuffer);
                gl.BindBuffer(kShaderStorageBuffer, slot.hashBuffer);
                const GLbitfield flags = kMapReadBit | kMapPersistentBit | kMapCoherentBit;
                gl.BufferStorage(kShaderStorageBuffer, 8, nullptr, flags);
                slot.hash = static_cast<const uint32_t *>(gl.MapBufferRange(kShaderStorageBuffer, 0, 8, flags));
            }
            if (slot.hash)
            {
                static const bool deviceHash = [] {
                    const char *setting = std::getenv("PS2X_FRAME_HASH_DEVICE");
                    return !setting || std::string_view(setting) != "0";
                }();
                if (deviceHash && !slot.hashDeviceBuffer)
                {
                    gl.GenBuffers(1, &slot.hashDeviceBuffer);
                    gl.BindBuffer(kShaderStorageBuffer, slot.hashDeviceBuffer);
                    gl.BufferData(kShaderStorageBuffer, 8, nullptr, kDynamicDraw);
                }
                const GLuint output = deviceHash ? slot.hashDeviceBuffer : slot.hashBuffer;
                const uint32_t zero = 0u;
                gl.BindBuffer(kShaderStorageBuffer, output);
                gl.ClearBufferData(kShaderStorageBuffer, kR32UI, kRedInteger, kUnsignedInt, &zero);
                gl.BindBufferBase(kShaderStorageBuffer, 7u, buffer);
                gl.BindBufferBase(kShaderStorageBuffer, 10u, output);
                gl.MemBarrier(kAllBarrierBits);
                gl.UseProgram(hashProgram);
                gl.Uniform1ui(hashLocation, width * height);
                gl.DispatchCompute((width * height + 255u) / 256u, 1u, 1u);
                gl.MemBarrier(kAllBarrierBits);
                if (deviceHash)
                {
                    gl.BindBuffer(kCopyReadBuffer, output);
                    gl.BindBuffer(kCopyWriteBuffer, slot.hashBuffer);
                    gl.CopyBufferSubData(kCopyReadBuffer, kCopyWriteBuffer, 0, 0, 8);
                    gl.MemBarrier(kAllBarrierBits);
                }
                slot.frame.hashValid = true;
            }
        }
        gl.BindBuffer(kPixelUnpackBuffer, 0u);
        if (!slot.frame.texture)
            gl.GenTextures(1, &slot.frame.texture);
        gl.BindTexture(kTexture2D, slot.frame.texture);
        if (slot.frame.width != width || slot.frame.height != height)
        {
            gl.TexImage2D(kTexture2D, 0, kRgba8, width, height, 0, kRgba, kUnsignedByte, nullptr);
            // GOW-Port: igualar el filtrado por defecto de la textura CPU de raylib.
            gl.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
            gl.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
            gl.TexParameteri(kTexture2D, kTextureWrapS, kClampToEdge);
            gl.TexParameteri(kTexture2D, kTextureWrapT, kClampToEdge);
        }
        gl.MemBarrier(kAllBarrierBits);
        gl.BindBuffer(kPixelUnpackBuffer, buffer);
        gl.TexSubImage2D(kTexture2D, 0, 0, 0, width, height, kRgba, kUnsignedByte, nullptr);
        gl.MemBarrier(kAllBarrierBits);
        gl.BindBuffer(kPixelUnpackBuffer, 0u);
        gl.BindTexture(kTexture2D, 0u);
        slot.frame.width = width;
        slot.frame.height = height;
        slot.frame.sequence = ++s_sharedSequence;
        slot.frame.renderSequence = renderSequence;
        slot.frame.displayFbp = displayFbp;
        slot.frame.sourceFbp = sourceFbp;
        slot.frame.usedPreferred = usedPreferred;
        slot.frame.blank = blank;
        slot.frame.vsyncTick = vsyncTick;
        slot.produced = gl.FenceSync(kSyncGpuCommandsComplete, 0u);
        gl.Flush();
        return true;
    }

    bool PublishSharedTexture(const Api &gl, GLuint source, uint32_t width, uint32_t height, uint64_t renderSequence,
                              uint32_t displayFbp, uint32_t sourceFbp, uint64_t vsyncTick)
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        if (!s_sharedActive.load(std::memory_order_relaxed) || !gl.CopyImageSubData)
            return false;
        SharedSlot *available = nullptr;
        for (SharedSlot &slot : s_sharedSlots)
        {
            if (slot.reading || !completed(gl, slot.produced) || !completed(gl, slot.consumed))
                continue;
            if (!available || slot.frame.sequence < available->frame.sequence)
                available = &slot;
        }
        if (!available)
            return false;
        SharedSlot &slot = *available;
        if (slot.produced)
            gl.DeleteSync(slot.produced);
        if (slot.consumed)
            gl.DeleteSync(slot.consumed);
        slot.produced = slot.consumed = nullptr;
        slot.frame.hashValid = false;
        const bool blank = source == 0u || width == 0u || height == 0u;
        if (!blank)
        {
            if (!slot.frame.texture)
                gl.GenTextures(1, &slot.frame.texture);
            if (slot.frame.width != width || slot.frame.height != height)
            {
                gl.BindTexture(kTexture2D, slot.frame.texture);
                gl.TexImage2D(kTexture2D, 0, kRgba8, width, height, 0, kRgba, kUnsignedByte, nullptr);
                gl.TexParameteri(kTexture2D, kTextureMinFilter, kLinear);
                gl.TexParameteri(kTexture2D, kTextureMagFilter, kLinear);
                gl.TexParameteri(kTexture2D, kTextureWrapS, kClampToEdge);
                gl.TexParameteri(kTexture2D, kTextureWrapT, kClampToEdge);
                gl.BindTexture(kTexture2D, 0u);
                slot.frame.width = width;
                slot.frame.height = height;
            }
            gl.CopyImageSubData(source, kTexture2D, 0, 0, 0, 0, slot.frame.texture, kTexture2D, 0, 0, 0, 0,
                                static_cast<GLsizei>(width), static_cast<GLsizei>(height), 1);
        }
        slot.frame.sequence = ++s_sharedSequence;
        slot.frame.renderSequence = renderSequence;
        slot.frame.displayFbp = displayFbp;
        slot.frame.sourceFbp = sourceFbp;
        slot.frame.usedPreferred = false;
        slot.frame.blank = blank;
        slot.frame.vsyncTick = vsyncTick;
        slot.produced = gl.FenceSync(kSyncGpuCommandsComplete, 0u);
        gl.Flush();
        return true;
    }

    void DestroyShared(const Api &gl)
    {
        std::lock_guard<std::mutex> lock(s_sharedMutex);
        s_sharedActive.store(false, std::memory_order_release);
        for (SharedSlot &slot : s_sharedSlots)
        {
            if (slot.produced)
                gl.DeleteSync(slot.produced);
            if (slot.consumed)
                gl.DeleteSync(slot.consumed);
            if (slot.frame.texture)
                gl.DeleteTextures(1, &slot.frame.texture);
            if (slot.hashBuffer)
                gl.DeleteBuffers(1, &slot.hashBuffer);
            if (slot.hashDeviceBuffer)
                gl.DeleteBuffers(1, &slot.hashDeviceBuffer);
            slot = {};
        }
        s_readingSlot = -1;
    }

    Context::~Context()
    {
        Destroy();
    }
}
