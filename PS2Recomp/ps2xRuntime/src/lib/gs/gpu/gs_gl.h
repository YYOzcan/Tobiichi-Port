// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace GSGL
{
    using GLenum = unsigned int;
    using GLuint = unsigned int;
    using GLint = int;
    using GLsizei = int;
    using GLboolean = unsigned char;
    using GLbitfield = unsigned int;
    using GLchar = char;
    using GLintptr = std::ptrdiff_t;
    using GLsizeiptr = std::ptrdiff_t;
    using GLuint64 = uint64_t;
    using GLsync = struct __GLsync *;

    constexpr GLenum kShaderStorageBuffer = 0x90D2;
    constexpr GLenum kComputeShader = 0x91B9;
    constexpr GLenum kVertexShader = 0x8B31;
    constexpr GLenum kFragmentShader = 0x8B30;
    constexpr GLenum kFramebuffer = 0x8D40;
    constexpr GLenum kFramebufferDefaultWidth = 0x9310;
    constexpr GLenum kFramebufferDefaultHeight = 0x9311;
    constexpr GLenum kTriangles = 0x0004;
    constexpr GLenum kConservativeRasterizationNV = 0x9346;
    constexpr GLenum kNoError = 0;
    constexpr GLenum kCompletionStatus = 0x91B1;
    constexpr GLenum kCompileStatus = 0x8B81;
    constexpr GLenum kLinkStatus = 0x8B82;
    constexpr GLenum kInfoLogLength = 0x8B84;
    constexpr GLenum kProgramBinaryLength = 0x8741;
    constexpr GLenum kProgramBinaryRetrievableHint = 0x8257;
    constexpr GLenum kDynamicDraw = 0x88E8;
    constexpr GLenum kStreamDraw = 0x88E0;
    constexpr GLenum kDynamicRead = 0x88E9;
    constexpr GLbitfield kShaderStorageBarrierBit = 0x00002000;
    constexpr GLbitfield kBufferUpdateBarrierBit = 0x00000200;
    constexpr GLbitfield kAllBarrierBits = 0xFFFFFFFF;
    constexpr GLenum kR32UI = 0x8236;
    constexpr GLenum kRedInteger = 0x8D94;
    constexpr GLenum kUnsignedInt = 0x1405;
    constexpr GLenum kVendor = 0x1F00;
    constexpr GLenum kRenderer = 0x1F01;
    constexpr GLenum kVersion = 0x1F02;
    constexpr GLenum kSyncGpuCommandsComplete = 0x9117;
    constexpr GLbitfield kSyncFlushCommandsBit = 0x00000001;
    constexpr GLenum kTimeoutExpired = 0x911B;
    constexpr GLenum kAlreadySignaled = 0x911A;
    constexpr GLenum kConditionSatisfied = 0x911C;
    constexpr GLenum kCopyReadBuffer = 0x8F36;
    constexpr GLenum kCopyWriteBuffer = 0x8F37;
    constexpr GLenum kStreamRead = 0x88E1;
    constexpr GLbitfield kMapReadBit = 0x0001;
    constexpr GLbitfield kMapWriteBit = 0x0002;
    constexpr GLbitfield kMapPersistentBit = 0x0040;
    constexpr GLbitfield kMapCoherentBit = 0x0080;
    constexpr GLbitfield kClientStorageBit = 0x0200;
    constexpr GLenum kTimeElapsed = 0x88BF;
    constexpr GLenum kQueryResult = 0x8866;
    constexpr GLenum kTimestamp = 0x8E28;
    constexpr GLenum kTexture2D = 0x0DE1;
    constexpr GLenum kRgba8 = 0x8058;
    constexpr GLenum kRgba = 0x1908;
    constexpr GLenum kUnsignedByte = 0x1401;
    constexpr GLenum kPixelUnpackBuffer = 0x88EC;
    constexpr GLenum kTextureMinFilter = 0x2801;
    constexpr GLenum kTextureMagFilter = 0x2800;
    constexpr GLenum kTextureWrapS = 0x2802;
    constexpr GLenum kTextureWrapT = 0x2803;
    constexpr GLint kLinear = 0x2601;
    constexpr GLint kClampToEdge = 0x812F;

    struct Api
    {
        void (*GenBuffers)(GLsizei, GLuint *) = nullptr;
        void (*DeleteBuffers)(GLsizei, const GLuint *) = nullptr;
        void (*BindBuffer)(GLenum, GLuint) = nullptr;
        void (*BufferData)(GLenum, GLsizeiptr, const void *, GLenum) = nullptr;
        void (*BufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *) = nullptr;
        void (*GetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *) = nullptr;
        void (*BindBufferBase)(GLenum, GLuint, GLuint) = nullptr;
        void (*BindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr) = nullptr;
        void (*ClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *) = nullptr;
        void (*CopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) = nullptr;
        void (*BufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield) = nullptr;
        void *(*MapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield) = nullptr;
        GLboolean (*UnmapBuffer)(GLenum) = nullptr;
        void (*GenQueries)(GLsizei, GLuint *) = nullptr;
        void (*DeleteQueries)(GLsizei, const GLuint *) = nullptr;
        void (*BeginQuery)(GLenum, GLuint) = nullptr;
        void (*EndQuery)(GLenum) = nullptr;
        void (*GetQueryObjectui64v)(GLuint, GLenum, GLuint64 *) = nullptr;
        void (*QueryCounter)(GLuint, GLenum) = nullptr;
        GLuint (*CreateShader)(GLenum) = nullptr;
        void (*ShaderSource)(GLuint, GLsizei, const GLchar *const *, const GLint *) = nullptr;
        void (*CompileShader)(GLuint) = nullptr;
        void (*GetShaderiv)(GLuint, GLenum, GLint *) = nullptr;
        void (*GetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
        void (*DeleteShader)(GLuint) = nullptr;
        GLuint (*CreateProgram)() = nullptr;
        void (*AttachShader)(GLuint, GLuint) = nullptr;
        void (*LinkProgram)(GLuint) = nullptr;
        void (*GetProgramiv)(GLuint, GLenum, GLint *) = nullptr;
        void (*GetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
        void (*ProgramParameteri)(GLuint, GLenum, GLint) = nullptr;
        void (*GetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *) = nullptr;
        void (*ProgramBinary)(GLuint, GLenum, const void *, GLsizei) = nullptr;
        void (*DeleteProgram)(GLuint) = nullptr;
        void (*UseProgram)(GLuint) = nullptr;
        GLint (*GetUniformLocation)(GLuint, const GLchar *) = nullptr;
        void (*Uniform1ui)(GLint, GLuint) = nullptr;
        void (*Uniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint) = nullptr;
        void (*Uniform1uiv)(GLint, GLsizei, const GLuint *) = nullptr;
        void (*DispatchCompute)(GLuint, GLuint, GLuint) = nullptr;
        void (*MemBarrier)(GLbitfield) = nullptr;
        GLsync (*FenceSync)(GLenum, GLbitfield) = nullptr;
        GLenum (*ClientWaitSync)(GLsync, GLbitfield, GLuint64) = nullptr;
        void (*DeleteSync)(GLsync) = nullptr;
        void (*Finish)() = nullptr;
        void (*Flush)() = nullptr;
        GLenum (*GetError)() = nullptr;
        const unsigned char *(*GetString)(GLenum) = nullptr;
        void (*GenTextures)(GLsizei, GLuint *) = nullptr;
        void (*DeleteTextures)(GLsizei, const GLuint *) = nullptr;
        void (*BindTexture)(GLenum, GLuint) = nullptr;
        void (*TexParameteri)(GLenum, GLenum, GLint) = nullptr;
        void (*TexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = nullptr;
        void (*TexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
        void (*GenFramebuffers)(GLsizei, GLuint *) = nullptr;
        void (*DeleteFramebuffers)(GLsizei, const GLuint *) = nullptr;
        void (*BindFramebuffer)(GLenum, GLuint) = nullptr;
        void (*FramebufferParameteri)(GLenum, GLenum, GLint) = nullptr;
        void (*Viewport)(GLint, GLint, GLsizei, GLsizei) = nullptr;
        void (*DrawArrays)(GLenum, GLint, GLsizei) = nullptr;
        void (*GenVertexArrays)(GLsizei, GLuint *) = nullptr;
        void (*DeleteVertexArrays)(GLsizei, const GLuint *) = nullptr;
        void (*BindVertexArray)(GLuint) = nullptr;
        void (*Enable)(GLenum) = nullptr;
        void (*Disable)(GLenum) = nullptr;
        void (*MaxShaderCompilerThreads)(GLuint) = nullptr;
        bool graphics = false;
    };

    class Context
    {
    public:
        Context() = default;
        ~Context();
        Context(const Context &) = delete;
        Context &operator=(const Context &) = delete;

        bool Create(std::string &error);
        void Destroy();
        bool Valid() const { return m_context != nullptr; }
        const Api &gl() const { return m_api; }
        bool Shared() const { return m_shared; }
        void *CreateWorker() const;
        bool MakeWorkerCurrent(void *worker) const;
        static void DestroyWorker(void *worker);

    private:
        void *m_window = nullptr;
        void *m_dc = nullptr;
        void *m_context = nullptr;
        Api m_api;
        bool m_shared = false;
    };

    bool PublishShared(const Api &gl, GLuint buffer, uint32_t width, uint32_t height, uint64_t renderSequence,
                       GLuint hashProgram, GLint hashLocation);
    bool SharedAvailable(const Api &gl);
    void DestroyShared(const Api &gl);
}
