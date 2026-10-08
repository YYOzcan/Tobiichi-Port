#ifndef PS2_VU1_H
#define PS2_VU1_H

#include <array>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdint>

// GOW-Port: las funciones en línea de VU1 usan el mismo modo de coma flotante que ps2_vu1_*.cpp (sin
// contracción en FMA).
#if defined(_MSC_VER)
#pragma float_control(precise, on, push)
#pragma fp_contract(off)
#endif

// GOW-Port: funciones pequeñas que el código de VU1 generado debe expandir siempre (en funciones de bloque
// grandes MSVC agota su presupuesto de expansión y las llama).
#if defined(_MSC_VER)
#define VU1_HOT_INLINE __forceinline
#else
#define VU1_HOT_INLINE inline __attribute__((always_inline))
#endif

class GS;
class PS2Memory;

struct VU1State
{
    float vf[32][4];
    int32_t vi[16];
    float acc[4];
    float q;
    float p;
    float i;
    uint32_t r;
    uint32_t pc;
    uint32_t mac;
    uint32_t clip;
    uint32_t status;
    uint64_t cycles;
    bool ebit;
    bool haltAfterDelaySlot;
    bool dBitEnabled;
    bool tBitEnabled;
    bool stoppedByD;
    bool stoppedByT;
    uint32_t top;  // VIF TOP visible to XTOP
    uint32_t itop; // VIF ITOP visible to XITOP

    bool branchPending;
    uint32_t branchTarget;
    uint32_t branchDelay;
};

class VU1Interpreter
{
public:
    enum class Unit : uint8_t
    {
        VU0,
        VU1
    };

    explicit VU1Interpreter(Unit unit = Unit::VU1);

    void reset();

    void execute(uint8_t *vuCode, uint32_t codeSize,
                 uint8_t *vuData, uint32_t dataSize,
                 GS &gs, PS2Memory *memory = nullptr,
                 uint32_t startPC = 0, uint32_t top = 0, uint32_t itop = 0,
                 uint32_t maxCycles = 65536);

    void resume(uint8_t *vuCode, uint32_t codeSize,
                uint8_t *vuData, uint32_t dataSize,
                GS &gs, PS2Memory *memory = nullptr,
                uint32_t top = 0, uint32_t itop = 0, uint32_t maxCycles = 65536);

    // GOW-Port: escribir VF/VI/ACC al ejecutar en vez de encolarlos (ver m_directRegisterWrites). El
    // resultado del programa no cambia, pero el estado intermedio que ve quien corta la ejecución por
    // presupuesto sí; por eso las pruebas del modelo de latencias lo dejan desactivado.
    void setDirectRegisterWrites(bool enabled);

    // GOW-Port: última ejecución detenida por presupuesto, sin E ni D/T.
    bool lastRunHitBudget() const { return m_lastRunHitBudget; }

    // GOW-Port: microcódigo de VU1 compilado a C++ (tools/vu1/generar_vu1.cpp). El código generado
    // comprueba en cada par que las dos palabras de la micromemoria son las que compiló; si no, interpreta
    // ese par. Ejecuta los mismos pasos que el intérprete (stepPair), con cada par ya decodificado.
    struct StepContext
    {
        uint8_t *vuCode = nullptr;
        uint32_t codeSize = 0;
        uint8_t *vuData = nullptr;
        uint32_t dataSize = 0;
        GS *gs = nullptr;
        PS2Memory *memory = nullptr;
        uint64_t budgetEnd = 0;
        bool programEnded = false;
    };
    using CompiledProgramFn = void (*)(VU1Interpreter &, StepContext &);
    static void registerCompiledProgram(CompiledProgramFn program);
    static uint64_t hashMicrocode(const uint8_t *code, uint32_t size);
    void setCompiledProgramsEnabled(bool enabled) { m_compiledEnabled = enabled; }

    VU1State &state() { return m_state; }
    const VU1State &state() const { return m_state; }

private:
    template <int Id>
    friend struct VU1CompiledProgram;
    friend struct VU1CompiledGenerator;
    friend struct VU1CompiledAccess;

    enum Pipeline : uint8_t
    {
        PipelineNone = 0,
        PipelineFmac,
        PipelineLsu,
        PipelineFdiv,
        PipelineEfu,
        PipelineIalu,
        PipelineBranch,
        PipelineXgkick
    };

    struct VfAccess
    {
        uint8_t reg = 0;
        uint8_t lanes = 0;
    };

    struct InstructionUsage
    {
        std::array<VfAccess, 2> vfRead{};
        VfAccess vfWrite{};
        uint8_t vfReadCount = 0;
        uint16_t viRead = 0;
        uint16_t viWrite = 0;
        uint8_t accRead = 0;
        uint8_t accWrite = 0;
        uint8_t latency = 0;
        uint8_t vfLatency = 0;
        uint8_t viLatency = 0;
        Pipeline pipeline = PipelineNone;
        bool waitQ = false;
        bool waitP = false;
        bool readsClip = false;
        bool writesClip = false;
        bool delaysNextBranchRead = false;
        bool reserved = false;
    };

    struct DecodedInstructionPair
    {
        uint32_t lower = 0;
        uint32_t upper = 0;
        InstructionUsage lowerUsage{};
        InstructionUsage upperUsage{};
        bool iBit = false;
        bool eBit = false;
        bool mBit = false;
        bool dBit = false;
        bool tBit = false;
        uint8_t upperVfShadowReg = 0;
        uint8_t suppressedLowerVf = 0;
        bool upperNop = false; // GOW-Port: NOP superior (no hace falta llamar a execUpper)
    };

    struct FlagPipelineEntry
    {
        uint64_t readyCycle = 0;
        uint64_t issueCycle = 0;
        uint32_t mac = 0;
        uint32_t status = 0;
        uint32_t extraSticky = 0;
        uint32_t clip = 0;
        bool valid = false;
        bool writesMac = false;
        bool writesStatus = false;
        bool writesSticky = false;
        bool writesClip = false;
    };

    struct ScalarPipelineEntry
    {
        uint64_t readyCycle = 0;
        float value = 0.0f;
        uint32_t statusDi = 0;
        bool valid = false;
    };

    struct PendingStore
    {
        uint64_t readyCycle = 0;
        uint32_t address = 0;
        std::array<uint32_t, 4> words{};
        uint8_t laneMask = 0;
        bool valid = false;
    };

    struct PendingVfWrite
    {
        uint64_t readyCycle = 0;
        uint64_t sequence = 0;
        std::array<float, 4> value{};
        uint8_t reg = 0;
        uint8_t laneMask = 0;
        bool valid = false;
    };

    struct PendingViWrite
    {
        uint64_t readyCycle = 0;
        uint64_t sequence = 0;
        int32_t value = 0;
        uint8_t reg = 0;
        bool valid = false;
    };

    struct PendingAccWrite
    {
        uint64_t readyCycle = 0;
        uint64_t sequence = 0;
        std::array<float, 4> value{};
        uint8_t laneMask = 0;
        bool valid = false;
    };

    struct XgkickPipeline
    {
        static constexpr uint32_t kBufferSize = 0x10000u;
        std::array<uint8_t, kBufferSize> packet{};
        uint32_t sourceAddress = 0;
        uint32_t totalBytes = 0;
        uint32_t copiedBytes = 0;
        uint32_t currentTagEnd = 0;
        uint32_t cycleCredit = 0;
        uint64_t issueCycle = 0;
        bool active = false;
        bool currentTagEop = false;

        // GOW-Port: como *this = {} pero sin poner a cero los 64 KB de packet (solo se leen los bytes ya
        // copiados: los GIFtags en copiedBytes y el envío hasta totalBytes <= copiedBytes).
        void reset()
        {
            sourceAddress = totalBytes = copiedBytes = currentTagEnd = cycleCredit = 0u;
            issueCycle = 0u;
            active = currentTagEop = false;
        }
    };

    static constexpr uint32_t kFmacLatency = 4u;
    static constexpr uint32_t kAccForwardLatency = 1u;
    static constexpr uint32_t kMaxFlagEntries = 8u;
    static constexpr uint32_t kMaxPendingStores = 8u;
    static constexpr uint32_t kMaxPendingVfWrites = 16u;
    static constexpr uint32_t kMaxPendingViWrites = 8u;
    static constexpr uint32_t kMaxPendingAccWrites = 8u;
    static constexpr uint32_t kMaxDecodedPairs = 0x4000u / 8u;

    Unit m_unit;
    VU1State m_state;
    std::array<DecodedInstructionPair, kMaxDecodedPairs> m_decodedCodeCache{};
    const uint8_t *m_cachedVuCode = nullptr;
    const PS2Memory *m_cachedMemory = nullptr;
    uint32_t m_cachedCodeSize = 0;
    uint64_t m_cachedCodeGeneration = 0;
    bool m_decodedCodeCacheValid = false;
    DecodedInstructionPair m_decodedScratch{}; // GOW-Port: pares fuera de la caché (se devuelven por referencia)
    // GOW-Port: VU1 escribe VF/VI/ACC al ejecutar en vez de encolarlos con su latencia. Equivale al modelo
    // con colas porque los lectores se detienen hasta que el registro está listo (m_vfReady...) y solo se
    // confirma la última escritura emitida. GOW_VU1_COLAS=1 vuelve al modelo con colas.
    bool m_directRegisterWrites = false;
    bool m_compiledEnabled = true;
    uint64_t m_compiledGeneration = ~0ull;
    // GOW-Port: ciclo de la próxima entrada de las colas que vence; commitReadyPipelines no hace nada antes.
    uint64_t m_nextCommitCycle = ~0ull;
    // GOW-Port: el microcódigo cargado no lee el registro de estado (FSAND/FSEQ/FSOR); no hace falta
    // calcular los bits pegajosos de los productos (calculateFmacProductSticky).
    bool m_statusUnread = false;
    // GOW-Port: además, nadie escribe el estado con FSSET; el código compilado puede omitir los flags de
    // una FMAC que nadie llega a ver (solo acumula sus bits pegajosos).
    bool m_statusQuiet = false;
    bool m_lastRunHitBudget = false; // GOW-Port: PR #12

    std::array<FlagPipelineEntry, kMaxFlagEntries> m_flagPipeline{};
    ScalarPipelineEntry m_fdiv{};
    std::array<ScalarPipelineEntry, 2> m_efu{};
    std::array<PendingStore, kMaxPendingStores> m_storePipeline{};
    std::array<PendingVfWrite, kMaxPendingVfWrites> m_vfWritePipeline{};
    std::array<PendingViWrite, kMaxPendingViWrites> m_viWritePipeline{};
    std::array<PendingAccWrite, kMaxPendingAccWrites> m_accWritePipeline{};
    uint32_t m_storePending = 0u, m_vfPending = 0u, m_viPending = 0u, m_accPending = 0u;
    // GOW-Port: los flags (MAC/estado/clip) tienen todos la misma latencia, así que se confirman en el orden
    // en que se emiten: una cola circular (cabeza y número de entradas) en lugar de buscar huecos.
    uint32_t m_flagHead = 0u, m_flagCount = 0u;
    XgkickPipeline m_xgkick{};
    std::array<std::array<uint64_t, 4>, 32> m_vfReady{};
    std::array<uint64_t, 16> m_viReady{};
    std::array<uint64_t, 4> m_accReady{};
    std::array<std::array<uint64_t, 4>, 32> m_vfLatestWrite{};
    std::array<uint64_t, 16> m_viLatestWrite{};
    std::array<uint64_t, 4> m_accLatestWrite{};

    uint64_t m_cycle = 0;
    uint64_t m_nextWriteSequence = 0;
    uint64_t m_efuResourceReady = 0;
    uint32_t m_workingClip = 0;
    uint32_t m_currentUpperInstruction = 0;
    int32_t m_viBranchBackupValue = 0;
    uint8_t m_viBranchBackupReg = 0;
    bool m_viBranchBackupValid = false;
    uint8_t *m_activeVuData = nullptr;
    uint32_t m_activeVuDataSize = 0;
    GS *m_activeGs = nullptr;
    PS2Memory *m_activeMemory = nullptr;
    bool m_stopRequested = false;
    bool m_pendingHaltD = false;
    bool m_pendingHaltT = false;

    void run(uint8_t *vuCode, uint32_t codeSize,
             uint8_t *vuData, uint32_t dataSize,
             GS &gs, PS2Memory *memory, uint32_t maxCycles);

    InstructionUsage decodeUpperUsage(uint32_t upper) const;
    InstructionUsage decodeLowerUsage(uint32_t lower) const;
    static void addVfRead(InstructionUsage &usage, uint8_t reg, uint8_t lanes);
    static void addVfWrite(InstructionUsage &usage, uint8_t reg, uint8_t lanes);
    static uint8_t vfReadLanes(const InstructionUsage &usage, uint8_t reg);
    DecodedInstructionPair decodeInstructionPair(const uint8_t *vuCode, uint32_t pc) const;
    const DecodedInstructionPair &getDecodedInstructionPairForPc(const uint8_t *vuCode, uint32_t codeSize, PS2Memory *memory, uint32_t pc);
    void rebuildDecodedCodeCache(const uint8_t *vuCode, uint32_t codeSize, const PS2Memory *memory, uint64_t generation);

    void execUpper(uint32_t instr);
    void execLower(uint32_t instr, uint8_t *vuData, uint32_t dataSize, GS &gs, PS2Memory *memory, uint32_t upperInstr);

    void applyDest(float *dst, const float *result, uint8_t dest);
    void applyDestAcc(const float *result, uint8_t dest);
    void applyFmacDest(float *dst, float *result, uint8_t dest);
    void applyFmacDestAcc(float *result, uint8_t dest);
    void normalizeFmacResult(float *result, uint8_t dest, uint8_t laneFlags[4]);
    bool calculateFmacExactResult(uint32_t component, long double &result) const;
    uint8_t normalizeFmacExactResult(float &value, long double exactResult) const;
    uint32_t calculateFmacProductSticky(uint8_t dest) const;
    void updateFmacFlags(const uint8_t laneFlags[4], uint8_t dest, uint32_t extraSticky);
    FlagPipelineEntry *pushFlagEntry();
    void queueFsset(uint16_t immediate);
    void queueClip(uint32_t clip);
    void queueFcset(uint32_t clip);
    void queueQ(float value, uint32_t latency, uint32_t statusDi);
    void queueP(float value, uint32_t latency);
    void queueStore(uint32_t address, const uint32_t words[4], uint8_t laneMask);
    void queueVfWrite(uint8_t reg, uint8_t laneMask, const float value[4], uint32_t latency);
    void queueViWrite(uint8_t reg, int32_t value, uint32_t latency);
    void queueAccWrite(uint8_t laneMask, const float value[4], uint32_t latency);
    void startXgkick(uint32_t qwordAddress);

    void resetScheduler();
    void commitReadyPipelines();
    // GOW-Port: los flags MAC/estado/clip se confirman cuando alguien los lee (FS*/FM*/FC*), al final de una
    // ejecución o cuando lo hace commitReadyPipelines por otra cola, aplicando las entradas ya listas en este
    // ciclo en orden: el resultado es el mismo que confirmándolas en su ciclo, sin llamar a
    // commitReadyPipelines en cada ciclo de código FMAC.
    void commitReadyFlags();
    void advanceOneCycle();
    void advanceTo(uint64_t targetCycle);
    void flushPipelines();
    void progressXgkick();
    void finishXgkick();
    uint64_t calculatePairReadyCycle(const DecodedInstructionPair &decoded) const;
    void markPairWrites(const DecodedInstructionPair &decoded);
    bool stepPair(const DecodedInstructionPair &decoded, StepContext &context);
    // GOW-Port: versiones especializadas para el microcódigo compilado (ps2_vu1_compiled.inl).
    template <uint32_t Upper, uint32_t C>
    void fmacLaneT(float &result, uint8_t &laneFlags, uint8_t &productFlags);
    template <uint32_t Upper, bool DeadFlags>
    void upperT();
    template <uint32_t Lower>
    void lowerT(StepContext &context, uint32_t upperInstr);
    template <class T>
    uint64_t readyCycleT() const;
    template <class T, bool DeadFlags, bool Plain = false>
    bool stepPairT(StepContext &context);
    bool blockPreconditions(StepContext &context, uint32_t pc, const uint32_t *words, size_t bytes) const;
    bool stepInterpreted(StepContext &context);
    bool compiledPrologue(StepContext &context);
    CompiledProgramFn compiledProgramFor(uint8_t *vuCode, uint32_t codeSize, PS2Memory *memory);
    bool pipelinesPending() const;

    // GOW-Port: en línea; se llama varias veces por instrucción (~9 % del tiempo de VU1 como llamada).
    VU1_HOT_INLINE float normalizeOperand(float value) const
    {
        uint32_t bits = 0;
        std::memcpy(&bits, &value, sizeof(bits));
        const uint32_t exponent = (bits >> 23) & 0xFFu;
        if (exponent == 0u)
            bits &= 0x80000000u;
        else if (exponent == 0xFFu)
            bits = (bits & 0x80000000u) | 0x7F7FFFFFu;
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    }

    // por separado, |exacto - resultado| < 2^-23 (|producto| + |resultado|). Si el resultado es normal,
    // no está cerca de los extremos (exponente 2..0xFD) y no es mucho menor que el producto (2^-20), el
    // exacto tiene su mismo signo, no es cero y no desborda: el valor no cambia y los flags son el signo.
    static VU1_HOT_INLINE bool productSumFlagsFast(float result, float product, uint8_t &laneFlags)
    {
        uint32_t r = 0u, p = 0u;
        std::memcpy(&r, &result, sizeof(r));
        std::memcpy(&p, &product, sizeof(p));
        const uint32_t re = (r >> 23) & 0xFFu;
        const uint32_t pe = (p >> 23) & 0xFFu;
        if (re < 2u || re > 0xFDu || (pe > re && (pe - re) > 20u))
            return false;
        laneFlags = (r & 0x80000000u) != 0u ? 0x2u : 0u;
        return true;
    }
    // GOW-Port: flags Z/S/U/O del producto exacto a*b (lo mismo que normalizeFmacExactResult sobre
    // a*b en long double). El producto de dos float cabe exacto en un double. Si el producto ya
    // redondeado es normal y lejos de los extremos (exponente 2..0xFD), el exacto no es cero, no desborda
    // ni subdesborda y tiene su signo: los flags son solo el signo.
    static VU1_HOT_INLINE uint8_t productStickyFlags(float a, float b, float rounded)
    {
        uint32_t bits = 0u;
        std::memcpy(&bits, &rounded, sizeof(bits));
        const uint32_t exponent = (bits >> 23) & 0xFFu;
        if (exponent >= 2u && exponent <= 0xFDu)
            return (bits & 0x80000000u) != 0u ? 0x2u : 0u;
        return productStickyFlagsExact(a, b);
    }
    static uint8_t productStickyFlagsExact(float a, float b)
    {
        const double exact = static_cast<double>(a) * static_cast<double>(b);
        const double magnitude = std::fabs(exact);
        uint8_t flags = std::signbit(exact) ? 0x2u : 0u;
        if (magnitude == 0.0)
            flags |= 0x1u;
        else if (magnitude > static_cast<double>(std::numeric_limits<float>::max()))
            flags |= 0x8u;
        else if (magnitude < static_cast<double>(std::numeric_limits<float>::min()))
            flags |= 0x5u;
        return flags;
    }
    float normalizeResult(float value, uint32_t &laneFlags) const;
    uint32_t microAddressMask() const { return m_unit == Unit::VU1 ? 0x3FFFu : 0x0FFFu; }
    int32_t readBranchVi(uint8_t reg) const;
    void recordViWriteForBranch(uint8_t reg, int32_t oldValue);
    void reportReservedInstruction(bool upper, uint32_t instruction);
    float broadcast(const float *vf, uint8_t bc);
};

#endif
