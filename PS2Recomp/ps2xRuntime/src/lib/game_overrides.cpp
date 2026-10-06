#include "game_overrides.h"
#include "ps2_runtime.h"
#include "runtime/ee_scheduler.h"
#include "ps2_runtime_calls.h"
#include "ps2_stubs.h"
#include "ps2_syscalls.h"
#include "ps2_runtime_macros.h"
#include "ps2_log.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
    std::mutex &registryMutex()
    {
        static std::mutex mutex;
        return mutex;
    }

    std::vector<ps2_game_overrides::Descriptor> &descriptorRegistry()
    {
        static std::vector<ps2_game_overrides::Descriptor> registry;
        return registry;
    }

    bool equalsIgnoreCaseAscii(std::string_view lhs, std::string_view rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }

        for (size_t i = 0; i < lhs.size(); ++i)
        {
            const auto l = static_cast<unsigned char>(lhs[i]);
            const auto r = static_cast<unsigned char>(rhs[i]);
            if (std::tolower(l) != std::tolower(r))
            {
                return false;
            }
        }

        return true;
    }

    std::string basenameFromPath(const std::string &path)
    {
        std::error_code ec;
        const std::filesystem::path fsPath(path);
        const std::filesystem::path leaf = fsPath.filename();
        if (leaf.empty())
        {
            return path;
        }
        return leaf.string();
    }

    std::optional<PS2Runtime::RecompiledFunction> resolveHandlerByName(std::string_view handlerName)
    {
        const std::string_view resolvedSyscall = ps2_runtime_calls::resolveSyscallName(handlerName);
        if (!resolvedSyscall.empty())
        {
#define PS2_RESOLVE_SYSCALL(name)                   \
    if (resolvedSyscall == std::string_view{#name}) \
    {                                               \
        return &ps2_syscalls::name;                 \
    }
            PS2_SYSCALL_LIST(PS2_RESOLVE_SYSCALL)
#undef PS2_RESOLVE_SYSCALL
        }

        const std::string_view resolvedStub = ps2_runtime_calls::resolveStubName(handlerName);
        if (!resolvedStub.empty())
        {
#define PS2_RESOLVE_STUB(name)                   \
    if (resolvedStub == std::string_view{#name}) \
    {                                            \
        return &ps2_stubs::name;                 \
    }
            PS2_STUB_LIST(PS2_RESOLVE_STUB)
#undef PS2_RESOLVE_STUB
        }

        return std::nullopt;
    }
}
namespace ps2_game_overrides
{
    AutoRegister::AutoRegister(const Descriptor &descriptor)
    {
        registerDescriptor(descriptor);
    }

    void registerDescriptor(const Descriptor &descriptor)
    {
        if (!descriptor.apply)
        {
            std::cerr << "[game_overrides] ignoring descriptor with null apply callback." << std::endl;
            return;
        }

        std::lock_guard<std::mutex> lock(registryMutex());
        descriptorRegistry().push_back(descriptor);
    }

    bool bindAddressHandler(PS2Runtime &runtime, uint32_t address, std::string_view handlerName)
    {
        const auto resolved = resolveHandlerByName(handlerName);
        if (!resolved.has_value())
        {
            std::cerr << "[game_overrides] unresolved handler '" << handlerName
                      << "' for address 0x" << std::hex << address << std::dec << std::endl;
            return false;
        }

        return runtime.replaceFunction(address, resolved.value());
    }

    void applyMatching(PS2Runtime &runtime,
                       const std::string &elfPath,
                       uint32_t entry,
                       uint32_t fileCrc32,
                       bool fileCrcValid)
    {

        std::vector<Descriptor> descriptors;
        {
            std::lock_guard<std::mutex> lock(registryMutex());
            descriptors = descriptorRegistry();
        }

        if (descriptors.empty())
        {
            return;
        }

        const std::string elfName = basenameFromPath(elfPath);
        size_t appliedCount = 0;
        for (const Descriptor &descriptor : descriptors)
        {
            if (!descriptor.apply)
            {
                continue;
            }

            if (descriptor.elfName && descriptor.elfName[0] != '\0')
            {
                if (!equalsIgnoreCaseAscii(descriptor.elfName, elfName))
                {
                    continue;
                }
            }

            if (descriptor.entry != 0u && descriptor.entry != entry)
            {
                continue;
            }

            if (descriptor.crc32 != 0u)
            {
                if (!fileCrcValid || fileCrc32 != descriptor.crc32)
                {
                    continue;
                }
            }

            const char *name = (descriptor.name && descriptor.name[0] != '\0')
                                   ? descriptor.name
                                   : "unnamed";
            std::cout << "[game_overrides] applying '" << name << "'" << std::endl;
            RUNTIME_LOG("[game_overrides] applying '" << name << "'");
            descriptor.apply(runtime);
            ++appliedCount;
        }

        if (appliedCount > 0)
        {
            std::cout << "[game_overrides] applied " << appliedCount << " matching override(s)." << std::endl;
            RUNTIME_LOG("[game_overrides] applied " << appliedCount << " matching override(s).");
        }
        else
        {
            std::cout << "[game_overrides] WARNING: 0 matching overrides applied for elfName=" << elfName << " entry=0x" << std::hex << entry << std::dec << std::endl;
        }
    }

    namespace
    {
        void gow_constructor_29bb78(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            ctx->pc = 0x29BB78u;
            SET_GPR_S32(ctx, 4, 0x002A618C);
            SET_GPR_S32(ctx, 5, 0x0032E830);
            ctx->pc = 0x286F88u;
            PS2Runtime::RecompiledFunction target = runtime->lookupFunction(0x286F88u);
            if (target)
            {
                target(rdram, ctx, runtime);
            }
        }

        void gow_constructor_26b6b0(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            ctx->pc = 0x26B6B0u;
            SET_GPR_S32(ctx, 29, (int32_t)ADD32(GPR_U32(ctx, 29), 4294967280));
            SET_GPR_S32(ctx, 4, 1);
            WRITE64(ADD32(GPR_U32(ctx, 29), 0), GPR_U64(ctx, 31));
            SET_GPR_U64(ctx, 5, 0xFFFF);
            ctx->pc = 0x2345E0u;
            PS2Runtime::RecompiledFunction target = runtime->lookupFunction(0x2345E0u);
            if (target)
            {
                target(rdram, ctx, runtime);
            }
            SET_GPR_U64(ctx, 31, READ64(ADD32(GPR_U32(ctx, 29), 0)));
            SET_GPR_S32(ctx, 29, (int32_t)ADD32(GPR_U32(ctx, 29), 16));
            ctx->pc = GPR_U32(ctx, 31);
        }

        static PS2Runtime::RecompiledFunction s_orig_memalloc = nullptr;

        void gow_memalloc_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t a0 = GPR_U32(ctx, 4);
            const uint32_t a1 = GPR_U32(ctx, 5);
            const uint32_t a2 = GPR_U32(ctx, 6);
            const uint32_t ra = GPR_U32(ctx, 31);
            const uint32_t sp = GPR_U32(ctx, 29);
            uint32_t outer_ra = 0;
            if (sp >= 8 && sp < 0x2000000 - 8)
            {
                const uint32_t candidate = *reinterpret_cast<const uint32_t *>(rdram + sp);
                if (candidate >= 0x100000 && candidate < 0x2D0000)
                {
                    outer_ra = candidate;
                }
            }
            const uint32_t curr_dc = *reinterpret_cast<const uint32_t *>(rdram + 0x29C4DCu);
            const uint32_t curr_e0 = *reinterpret_cast<const uint32_t *>(rdram + 0x29C4E0u);
            if (curr_dc == 0xffffffffu)
            {
                std::cerr << "[GoW MemAlloc] WARNING: 0x29C4DC is 0xFFFFFFFF at caller_ra=0x" << std::hex << ra << std::dec << std::endl;
            }
            std::cerr << "[GoW MemAlloc] heap=0x" << std::hex << a0 << " size=0x" << a1
                      << " align=0x" << a2 << " caller_ra=0x" << ra
                      << " dc=0x" << curr_dc << " e0=0x" << curr_e0;
            *reinterpret_cast<uint32_t *>(rdram + 0x29C4E0u) = 0u;
            *reinterpret_cast<uint32_t *>(rdram + 0x30463Cu) = 0x2735df21u;
            *reinterpret_cast<uint32_t *>(rdram + 0x304640u) = 0x67ab3901u;

            if (outer_ra) std::cerr << " (malloc caller: 0x" << outer_ra << ")";
            std::cerr << std::dec << std::endl;

            // Fail fast on bogus heap handles instead of letting the real
            // allocator scan garbage free-lists forever (e.g. heap=0x1200034
            // from an unfilled record: t0=0 walk over low RAM never meets s2).
            // Game heaps carry magic 0xC0DE1111 at +0. Heap 0 keeps legacy
            // behavior (some boot callers rely on it).
            if (a0 != 0)
            {
                bool bogus = false;
                if (a0 < 0x100000 || a0 >= 0x2000000)
                {
                    bogus = true;
                }
                else if (*reinterpret_cast<const uint32_t *>(rdram + a0) != 0xC0DE1111u)
                {
                    bogus = true;
                }
                if (bogus)
                {
                    static int s_bogus_heap_logs = 0;
                    if (s_bogus_heap_logs < 10)
                    {
                        std::cerr << "[GoW MemAlloc] BOGUS HEAP 0x" << std::hex << a0 << " size=0x" << a1
                                  << " caller_ra=0x" << ra << " -> returning 0" << std::dec << std::endl;
                        ++s_bogus_heap_logs;
                    }
                    SET_GPR_U64(ctx, 2, 0);
                    ctx->pc = ra;
                    return;
                }
            }

            if (a1 >= 0x10000)
            {
                std::cerr << "--- [Heap State Dump for 0x" << std::hex << a0 << "] ---" << std::endl;
                for (uint32_t i = 0; i < 16; ++i)
                {
                    uint32_t w = *reinterpret_cast<const uint32_t *>(rdram + a0 + i * 4);
                    std::cerr << "  +0x" << std::hex << (i * 4) << ": 0x" << w << std::dec << std::endl;
                }
                uint32_t head = *reinterpret_cast<const uint32_t *>(rdram + a0 + 4);
                std::cerr << "  Free list head: 0x" << std::hex << head << std::dec << std::endl;
                uint32_t curr = head;
                int count = 0;
                while (curr != a0 && curr >= 0x100000 && curr < 0x2000000 && count < 20)
                {
                    uint32_t hdr = *reinterpret_cast<const uint32_t *>(rdram + curr);
                    uint32_t nxt = *reinterpret_cast<const uint32_t *>(rdram + curr + 4);
                    uint32_t prv = *reinterpret_cast<const uint32_t *>(rdram + curr + 8);
                    std::cerr << "  Block #" << count << " @ 0x" << std::hex << curr
                              << " hdr=0x" << hdr << " (size=0x" << (hdr & 0x1ffffff) << ")"
                              << " next=0x" << nxt << " prev=0x" << prv << std::dec << std::endl;
                    if (nxt == curr) break;
                    curr = nxt;
                    count++;
                }
                std::cerr << "--- [End Heap Dump] ---" << std::endl;
            }

            if (s_orig_memalloc)
            {
                s_orig_memalloc(rdram, ctx, runtime);
            }
            std::cerr << "[GoW MemAlloc Return] v0=0x" << std::hex << GPR_U32(ctx, 2) << " pc=0x" << ctx->pc << std::dec << std::endl;
        }

        static PS2Runtime::RecompiledFunction s_orig_resourcepool_create = nullptr;

        void gow_resourcepool_create_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            uint32_t v_dc = *reinterpret_cast<uint32_t *>(rdram + 0x29C4DCu);
            uint32_t v_e0 = *reinterpret_cast<uint32_t *>(rdram + 0x29C4E0u);
            std::cerr << "[GoW ResourcePool_Create] enter: 0x29C4DC=0x" << std::hex << v_dc
                      << " 0x29C4E0=0x" << v_e0 << std::dec << std::endl;
            *reinterpret_cast<uint32_t *>(rdram + 0x29C4DCu) = 0x2735df21u;
            *reinterpret_cast<uint32_t *>(rdram + 0x29C4E0u) = 0u;
            *reinterpret_cast<uint32_t *>(rdram + 0x30463Cu) = 0x2735df21u;
            *reinterpret_cast<uint32_t *>(rdram + 0x304640u) = 0x67ab3901u;
            if (s_orig_resourcepool_create)
            {
                s_orig_resourcepool_create(rdram, ctx, runtime);
            }
            std::cerr << "[GoW ResourcePool_Create] exit: pc=0x" << std::hex << ctx->pc << std::dec << std::endl;
        }

        static const uint32_t GOW_DUMMY_OBJ = 0x01F80000u;
        static const uint32_t GOW_DUMMY_VTABLE_PTR = 0x01F90000u;
        static const uint32_t GOW_DUMMY_VTABLE_FUNCS = 0x01FA0000u;
        static const uint32_t GOW_NOOP_FUNC_ADDR = 0x002B0000u;
        static int s_noop_calls = 0;

        static PS2Runtime::RecompiledFunction s_orig_tree_lookup = nullptr;
        static int s_tree_lookup_calls = 0;

        void gow_tree_lookup_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            uint32_t root_ptr_addr = GPR_U32(ctx, 4);
            uint32_t search_key = GPR_U32(ctx, 5);
            uint32_t ra = GPR_U32(ctx, 31);
            int call_id = s_tree_lookup_calls++;

            if (root_ptr_addr < 0x10000u || 
                (root_ptr_addr >= GOW_DUMMY_OBJ && root_ptr_addr < GOW_DUMMY_OBJ + 0x80000u))
            {
                std::cerr << "[GoW TreeLookup #" << call_id << "] dummy/NULL root_ptr=0x" << std::hex << root_ptr_addr
                          << " key=0x" << search_key << " -> returning dummy" << std::dec << std::endl;
                SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
                ctx->pc = ra;
                return;
            }

            uint32_t sentinel = *reinterpret_cast<uint32_t *>(rdram + 0x29C4B4u);
            uint32_t tree_base = *reinterpret_cast<uint32_t *>(rdram + 0x29C4BCu);

            // Read root node from *root_ptr_addr
            uint32_t curr_node = (root_ptr_addr >= 0x100000 && root_ptr_addr < 0x2000000) ?
                                 *reinterpret_cast<uint32_t *>(rdram + root_ptr_addr) : 0;

            if (curr_node >= GOW_DUMMY_OBJ && curr_node < GOW_DUMMY_OBJ + 0x80000u)
            {
                std::cerr << "[GoW TreeLookup #" << call_id << "] dummy root_node=0x" << std::hex << curr_node
                          << " key=0x" << search_key << " -> returning dummy" << std::dec << std::endl;
                SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
                ctx->pc = ra;
                return;
            }

            if (call_id < 60)
            {
                std::cerr << "[GoW TreeLookup #" << call_id << "] ENTER: root_ptr=0x" << std::hex << root_ptr_addr
                          << " root_node=0x" << curr_node << " key=0x" << search_key
                          << " sentinel=0x" << sentinel << " tree_base=0x" << tree_base << std::dec << std::endl;
            }

            // Implement safe bounded tree traversal
            uint32_t result_node = 0;
            int depth = 0;
            while (curr_node != sentinel && curr_node != 0 && depth < 256)
            {
                if (curr_node < 0x100000 || curr_node >= 0x2000000)
                {
                    break;
                }
                uint32_t node_key = *reinterpret_cast<uint32_t *>(rdram + curr_node);
                if (search_key == node_key)
                {
                    result_node = curr_node;
                    break;
                }
                uint16_t child_idx = 0;
                if (search_key < node_key)
                {
                    child_idx = *reinterpret_cast<uint16_t *>(rdram + curr_node + 10); // left child index
                }
                else
                {
                    child_idx = *reinterpret_cast<uint16_t *>(rdram + curr_node + 12); // right child index
                }
                curr_node = tree_base + (static_cast<uint32_t>(child_idx) << 4);
                depth++;
            }

            if (call_id < 60)
            {
                std::cerr << "[GoW TreeLookup #" << call_id << "] EXIT: result=0x" << std::hex << result_node
                          << " depth=" << std::dec << depth << " ra=0x" << std::hex << ra << std::dec << std::endl;
            }

            SET_GPR_U64(ctx, 2, result_node ? result_node : GOW_DUMMY_OBJ);
            ctx->pc = ra;
        }

        void gow_vfs_vtable_noop(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t ra = GPR_U32(ctx, 31);
            if (s_noop_calls < 30)
            {
                std::cerr << "[GoW VFS Dummy Call #" << s_noop_calls++ << "] ra=0x" << std::hex << ra
                          << " a0=0x" << GPR_U32(ctx, 4) << " a1=0x" << GPR_U32(ctx, 5) << std::dec << std::endl;
            }
            // Return dummy object address (GOW_DUMMY_OBJ) so chained calls don't dereference NULL
            SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
            ctx->pc = ra;
        }

        void setup_gow_dummy_object(uint8_t *rdram, PS2Runtime *runtime)
        {
            for (uint32_t i = 0; i < 0x4000; i += 4) {
                *reinterpret_cast<uint32_t *>(rdram + GOW_DUMMY_OBJ + i) = GOW_DUMMY_VTABLE_PTR;
                *reinterpret_cast<uint32_t *>(rdram + GOW_DUMMY_VTABLE_PTR + i) = GOW_NOOP_FUNC_ADDR;
                *reinterpret_cast<uint32_t *>(rdram + GOW_DUMMY_VTABLE_FUNCS + i) = GOW_NOOP_FUNC_ADDR;
            }

            for (uint32_t i = 0x0032E848u; i < 0x0032EC48u; i += 4) {
                *reinterpret_cast<uint32_t *>(rdram + i) = GOW_DUMMY_OBJ;
            }

            runtime->replaceFunction(GOW_NOOP_FUNC_ADDR, &gow_vfs_vtable_noop);
        }

        void gow_skip_to_menu_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t ra = GPR_U32(ctx, 31);
            setup_gow_dummy_object(rdram, runtime);
            SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
            ctx->pc = ra;
        }

        static bool s_toc_loaded = false;

        static constexpr uint32_t kGoWTocRamAddr = 0x01E00000u;
        static constexpr uint32_t kGoWShellWadRamAddr = 0x01E10000u;
        static uint32_t s_shell_wad_size = 0;

        struct GoWTocEntry
        {
            std::string name;
            uint32_t offset = 0;
            uint32_t size = 0;
        };

        static std::vector<GoWTocEntry> s_toc_entries;
        static std::unordered_map<std::string, size_t> s_toc_by_name;

        static std::filesystem::path findGodOfWarFile(const char *fileName)
        {
            const char *envDir = std::getenv("PS2_GOW_DIR");
            std::vector<std::filesystem::path> candidates;
            if (envDir && envDir[0] != '\0')
            {
                candidates.emplace_back(std::filesystem::path(envDir) / fileName);
            }
            const PS2Runtime::IoPaths &paths = PS2Runtime::getIoPaths();
            if (!paths.elfDirectory.empty())
            {
                candidates.emplace_back(paths.elfDirectory / fileName);
                candidates.emplace_back(paths.elfDirectory / ".." / fileName);
            }
            if (!paths.cdImage.empty() && paths.cdImage.has_parent_path())
            {
                candidates.emplace_back(paths.cdImage.parent_path() / fileName);
            }
            candidates.emplace_back(std::filesystem::path("/home/yigit/Belgelerim/Origami Tobiichi") / fileName);
            candidates.emplace_back(std::filesystem::path("/home/yigit/Belgeler") / fileName);
            candidates.emplace_back(std::filesystem::path("/home/yigit/Belgelerim") / fileName);
            for (const auto &candidate : candidates)
            {
                std::error_code ec;
                if (!candidate.empty() && std::filesystem::exists(candidate, ec) && !ec)
                {
                    return candidate.lexically_normal();
                }
            }
            return {};
        }

        void loadGodOfWarTocFile(uint8_t *rdram)
        {
            if (s_toc_loaded) return;
            const std::filesystem::path toc_path = findGodOfWarFile("GODOFWAR.TOC");
            if (toc_path.empty())
            {
                std::cerr << "[GoW TOC Loader] WARNING: GODOFWAR.TOC not found" << std::endl;
                return;
            }
            FILE *f = fopen(toc_path.string().c_str(), "rb");
            if (f)
            {
                fseek(f, 0, SEEK_END);
                long sz = ftell(f);
                fseek(f, 0, SEEK_SET);
                const uint32_t target_ram_addr = kGoWTocRamAddr;
                size_t read_bytes = fread(rdram + target_ram_addr, 1, sz, f);
                // Build host-side name -> (offset, size) index. Layout is
                // 1669 x { char name[16]; u32 offsetLE; u32 sizeLE }.
                if (sz >= 24)
                {
                    const size_t count = static_cast<size_t>(sz) / 24u;
                    const uint8_t *base = rdram + target_ram_addr;
                    s_toc_entries.reserve(count);
                    for (size_t i = 0; i < count; ++i)
                    {
                        const uint8_t *e = base + i * 24u;
                        size_t nameLen = 0;
                        while (nameLen < 16 && e[nameLen] != '\0')
                        {
                            ++nameLen;
                        }
                        GoWTocEntry entry;
                        entry.name.assign(reinterpret_cast<const char *>(e), nameLen);
                        entry.offset = static_cast<uint32_t>(e[16]) | (static_cast<uint32_t>(e[17]) << 8) |
                                       (static_cast<uint32_t>(e[18]) << 16) | (static_cast<uint32_t>(e[19]) << 24);
                        entry.size = static_cast<uint32_t>(e[20]) | (static_cast<uint32_t>(e[21]) << 8) |
                                     (static_cast<uint32_t>(e[22]) << 16) | (static_cast<uint32_t>(e[23]) << 24);
                        if (!entry.name.empty() && entry.size != 0)
                        {
                            s_toc_by_name.emplace(entry.name, s_toc_entries.size());
                            s_toc_entries.push_back(std::move(entry));
                        }
                    }
                }
                fclose(f);
                std::cerr << "[GoW TOC Loader] loaded " << toc_path.string() << " (" << read_bytes
                          << " bytes, " << s_toc_entries.size() << " indexed entries) at 0x" << std::hex << target_ram_addr << std::dec << std::endl;
                const auto shellIt = s_toc_by_name.find("R_SHELL.WAD");
                if (shellIt != s_toc_by_name.end())
                {
                    const GoWTocEntry &shell = s_toc_entries[shellIt->second];
                    std::cerr << "[GoW TOC] R_SHELL.WAD off=" << shell.offset << " size=" << shell.size << std::endl;
                    // Step 2/5: stage the SHELL WAD bytes into EE RAM right away.
                    const std::filesystem::path pak_path = findGodOfWarFile("PART1.PAK");
                    if (!pak_path.empty())
                    {
                        FILE *pf = fopen(pak_path.string().c_str(), "rb");
                        if (pf)
                        {
                            fseek(pf, static_cast<long>(shell.offset), SEEK_SET);
                            size_t got = fread(rdram + kGoWShellWadRamAddr, 1, shell.size, pf);
                            fclose(pf);
                            if (got == shell.size)
                            {
                                s_shell_wad_size = shell.size;
                                std::cerr << "[GoW WAD] staged R_SHELL.WAD (" << got
                                          << " bytes) at 0x" << std::hex << kGoWShellWadRamAddr << std::dec << std::endl;
                            }
                            else
                            {
                                std::cerr << "[GoW WAD] WARNING: short read " << got << "/" << shell.size << std::endl;
                            }
                        }
                        else
                        {
                            std::cerr << "[GoW WAD] WARNING: Could not open " << pak_path.string() << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "[GoW WAD] WARNING: PART1.PAK not found" << std::endl;
                    }
                }
                s_toc_loaded = true;
            }
            else
            {
                std::cerr << "[GoW TOC Loader] WARNING: Could not open " << toc_path.string() << std::endl;
            }
        }

        void gow_vfs_lookup_resource_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            loadGodOfWarTocFile(rdram);
            setup_gow_dummy_object(rdram, runtime);
            const uint32_t ra = GPR_U32(ctx, 31);
            const uint32_t key = GPR_U32(ctx, 5);

            const uint32_t res_hdr = GOW_DUMMY_OBJ;
            *reinterpret_cast<uint32_t *>(rdram + res_hdr + 0x04) = 0x01E00000u; // TOC Base pointer
            *reinterpret_cast<uint32_t *>(rdram + res_hdr + 0x10) = key;        // Resource Key ID

            SET_GPR_U64(ctx, 2, res_hdr);
            ctx->pc = ra;
        }

        void gow_vfs_resource_handler_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            setup_gow_dummy_object(rdram, runtime);
            const uint32_t ra = GPR_U32(ctx, 31);
            SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
            ctx->pc = ra;
        }

        static PS2Runtime::RecompiledFunction s_orig_sub_1be550 = nullptr;

        void gow_sub_1be550_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            loadGodOfWarTocFile(rdram);
            setup_gow_dummy_object(rdram, runtime);
            const uint32_t a0 = GPR_U32(ctx, 4);
            const uint32_t ra = GPR_U32(ctx, 31);
            if (a0 == 0 || a0 < 0x100000 || a0 >= 0x2000000)
            {
                SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
                ctx->pc = ra;
                return;
            }
            uint16_t idx = *reinterpret_cast<const uint16_t *>(rdram + a0);
            uint32_t tbl_addr = 0x0032E848u + (idx * 4u);
            if (tbl_addr >= 0x100000 && tbl_addr < 0x2000000)
            {
                uint32_t val = *reinterpret_cast<uint32_t *>(rdram + tbl_addr);
                if (val == 0)
                {
                    *reinterpret_cast<uint32_t *>(rdram + tbl_addr) = GOW_DUMMY_OBJ;
                }
            }
            if (s_orig_sub_1be550)
            {
                s_orig_sub_1be550(rdram, ctx, runtime);
            }
            else
            {
                SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
                ctx->pc = ra;
            }
        }

        void gow_force_menu_init_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            setup_gow_dummy_object(rdram, runtime);
            std::cerr << "[GoW Menu Force] SCEA logo wait completed -> returning success\n";
            SET_GPR_U64(ctx, 2, GOW_DUMMY_OBJ);
            ctx->pc = GPR_U32(ctx, 31);
        }

        static PS2Runtime::RecompiledFunction s_orig_sub_17a910 = nullptr;

        void gow_sub_17a910_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t ra = GPR_U32(ctx, 31);
            if (s_orig_sub_17a910)
            {
                s_orig_sub_17a910(rdram, ctx, runtime);
            }
            setup_gow_dummy_object(rdram, runtime);
            ctx->pc = ra;
        }

        static PS2Runtime::RecompiledFunction s_orig_sub_17fd10 = nullptr;

        void gow_sub_17fd10_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            if (s_orig_sub_17fd10)
            {
                s_orig_sub_17fd10(rdram, ctx, runtime);
            }
            else
            {
                SET_GPR_U64(ctx, 2, 0);
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static int s_waitsema_log_count = 0;

        void gow_waitsema_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t semid = GPR_U32(ctx, 4);
            const uint32_t ra = GPR_U32(ctx, 31);
            if (s_waitsema_log_count < 30)
            {
                std::cerr << "[GoW WaitSemaDiag #" << s_waitsema_log_count << "] semid=" << semid
                          << " pc=0x" << std::hex << ctx->pc << " ra=0x" << ra << std::dec << std::endl;
            }
            ++s_waitsema_log_count;
            SET_GPR_S32(ctx, 3, 0x44);
            runtime->handleSyscall(rdram, ctx, 0x0u);
            if (s_waitsema_log_count <= 30)
            {
                std::cerr << "[GoW WaitSemaDiag result] semid=" << semid
                          << " v0=" << static_cast<int32_t>(GPR_U32(ctx, 2)) << std::endl;
            }
            ctx->pc = GPR_U32(ctx, 31);
        }

        static int s_createsema_log_count = 0;

        void gow_createsema_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t param = GPR_U32(ctx, 4);
            const uint32_t ra = GPR_U32(ctx, 31);
            SET_GPR_S32(ctx, 3, 0x40);
            runtime->handleSyscall(rdram, ctx, 0x0u);
            const int32_t v0 = static_cast<int32_t>(GPR_U32(ctx, 2));
            if (s_createsema_log_count < 30)
            {
                std::cerr << "[GoW CreateSemaDiag #" << s_createsema_log_count << "] param=0x"
                          << std::hex << param << " ra=0x" << ra << std::dec << " -> id=" << v0 << std::endl;
            }
            ++s_createsema_log_count;
            ctx->pc = GPR_U32(ctx, 31);
        }

        void gow_sub_171008_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            uint32_t a0 = GPR_U32(ctx, 4);
            uint32_t ra = GPR_U32(ctx, 31);
            if (a0 >= 0x100000 && a0 < 0x2000000)
            {
                uint16_t v0 = *reinterpret_cast<uint16_t *>(rdram + a0 + 194);
                *reinterpret_cast<uint16_t *>(rdram + a0 + 194) = v0 | 0x40;
                uint32_t a2 = a0 + 116;
                uint32_t curr = *reinterpret_cast<uint32_t *>(rdram + a0 + 116);
                int count = 0;
                while (curr != a2 && curr >= 0x100000 && curr < 0x2000000 && count < 256)
                {
                    uint32_t v1 = curr - 16;
                    uint16_t val = *reinterpret_cast<uint16_t *>(rdram + v1 + 26);
                    *reinterpret_cast<uint16_t *>(rdram + v1 + 26) = val | 0x800;
                    uint32_t next = *reinterpret_cast<uint32_t *>(rdram + curr);
                    if (next == curr) break;
                    curr = next;
                    count++;
                }
            }
            ctx->pc = ra;
        }

        void gow_sub_170b98_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            // Bounded variant of sub_170B98: walk the doubly-linked list at
            // a0+116, clearing bit 0x2000 in each node's +26 halfword.
            // Original spins forever when the list is corrupt (missing VFS/IOP
            // data); bound to 256 nodes with guest-range validation.
            (void)runtime;
            const uint32_t a0 = GPR_U32(ctx, 4);
            const uint32_t ra = GPR_U32(ctx, 31);
            if (a0 >= 0x100000 && a0 < 0x2000000)
            {
                const uint32_t list_head = a0 + 116;
                uint32_t curr = *reinterpret_cast<const uint32_t *>(rdram + a0 + 116);
                int count = 0;
                while (curr != list_head && curr >= 0x100000 && curr < 0x2000000 && count < 256)
                {
                    const uint32_t node = curr - 16;
                    if (node < 0x100000 || node + 28 > 0x2000000)
                    {
                        break;
                    }
                    const uint16_t val = *reinterpret_cast<const uint16_t *>(rdram + node + 26);
                    *reinterpret_cast<uint16_t *>(rdram + node + 26) = val & 0xDFFFu;
                    const uint32_t next = *reinterpret_cast<const uint32_t *>(rdram + curr);
                    if (next == curr)
                    {
                        break;
                    }
                    curr = next;
                    ++count;
                }
            }
            ctx->pc = ra;
        }

        void gow_sub_15f1e8_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            uint32_t a0 = GPR_U32(ctx, 4);
            uint32_t a1 = GPR_U32(ctx, 5);
            uint32_t a2 = GPR_U32(ctx, 6);
            uint32_t a3 = GPR_U32(ctx, 7);
            uint32_t t0 = GPR_U32(ctx, 8);
            uint32_t ra = GPR_U32(ctx, 31);

            a2 = a2 << 3;
            a1 = (a1 << 6) + a0;
            uint32_t v0 = a2 + a1;
            uint32_t list_head_ptr = v0 + 52;
            if (t0 >= 0x100000 && t0 < 0x2000000)
            {
                *reinterpret_cast<uint32_t *>(rdram + t0 + 16) = a3;
            }

            if (v0 < 0x100000 || v0 >= 0x2000000)
            {
                ctx->pc = ra;
                return;
            }

            uint32_t v1 = *reinterpret_cast<uint32_t *>(rdram + list_head_ptr);
            int count = 0;
            while (v1 != list_head_ptr && v1 >= 0x100000 && v1 < 0x2000000 && count < 256)
            {
                int32_t item_val = *reinterpret_cast<int32_t *>(rdram + v1 + 16);
                if (item_val >= static_cast<int32_t>(a3))
                {
                    break;
                }
                uint32_t next_v1 = *reinterpret_cast<uint32_t *>(rdram + v1);
                if (next_v1 == v1) break;
                v1 = next_v1;
                count++;
            }

            if (v1 >= 0x100000 && v1 < 0x2000000 && t0 >= 0x100000 && t0 < 0x2000000)
            {
                uint32_t prev = *reinterpret_cast<uint32_t *>(rdram + v1 + 4);
                *reinterpret_cast<uint32_t *>(rdram + v1 + 4) = t0;
                *reinterpret_cast<uint32_t *>(rdram + t0) = v1;
                *reinterpret_cast<uint32_t *>(rdram + t0 + 4) = prev;
                if (prev >= 0x100000 && prev < 0x2000000)
                {
                    *reinterpret_cast<uint32_t *>(rdram + prev) = t0;
                }
            }
            ctx->pc = ra;
        }

        void gow_sub_17aa18_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            // Return success without touching the global flag at 0x29C4D8.
            // Writing the flag changes other readers' behavior and cascades
            // to top-level exit; the caller only needs v0 != 0 to proceed.
            (void)rdram;
            (void)runtime;
            SET_GPR_U64(ctx, 2, 1);
            ctx->pc = GPR_U32(ctx, 31);
        }

        // Removed gow_sub_17bc80_hook

        void gow_sub_17a9b0_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            // Bypass audio/stream subsystem tick in sub_17A9B0
            SET_GPR_U64(ctx, 2, 0);
            ctx->pc = GPR_U32(ctx, 31);
        }

        void gow_sub_26bf28_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            // func_26BF28 is audio/stream packet handler; return success
            SET_GPR_U64(ctx, 2, 0);
            ctx->pc = GPR_U32(ctx, 31);
        }

        static PS2Runtime::RecompiledFunction s_orig_sub_180d08 = nullptr;

        void gow_sub_180d08_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t a1 = GPR_U32(ctx, 5);
            const uint32_t ra = GPR_U32(ctx, 31);
            if (a1 == 0 || a1 < 0x100000 || a1 >= 0x2000000)
            {
                SET_GPR_U64(ctx, 2, 0);
                ctx->pc = ra;
                return;
            }
            if (s_orig_sub_180d08)
            {
                s_orig_sub_180d08(rdram, ctx, runtime);
            }
            else
            {
                SET_GPR_U64(ctx, 2, 0);
                ctx->pc = ra;
            }
        }

        static int s_sifcallrpc_log_count = 0;
        static PS2Runtime::RecompiledFunction s_orig_sifcallrpc = nullptr;

        void gow_sifcallrpc_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t sid = GPR_U32(ctx, 5);
            const uint32_t ra = GPR_U32(ctx, 31);
            const bool isSmpd = (sid == 0x4Du || sid == 0x0Au || sid == 0x68u || sid == 0x00u);
            const bool wantPre = ((isSmpd && s_sifcallrpc_log_count < 12) || (!isSmpd && s_sifcallrpc_log_count < 30));
            int tid = -1;
            if (wantPre)
            {
                GuestThread *self = runtime->eeScheduler().currentThread();
                if (self)
                {
                    tid = self->id;
                }
            }
            uint32_t recvBuf = 0;
            uint32_t recvSize = 0;
            if (wantPre && isSmpd)
            {
                // Stack layout mirrors SifCallRpc: sp+0x14 recv buf, sp+0x18 recv size.
                recvBuf = *reinterpret_cast<const uint32_t *>(rdram + GPR_U32(ctx, 29) + 0x14);
                recvSize = *reinterpret_cast<const uint32_t *>(rdram + GPR_U32(ctx, 29) + 0x18);
                const uint32_t sendBuf = GPR_U32(ctx, 7);
                const uint32_t sendSize = GPR_U32(ctx, 8);
                std::cerr << "[GoW SifCallRpc] sid=0x" << std::hex << sid << " ra=0x" << ra << " th=" << std::dec << tid
                          << " send=0x" << std::hex << sendBuf << "+" << std::dec << std::min<uint32_t>(sendSize, 64)
                          << " recv=0x" << std::hex << recvBuf << "+" << std::dec << recvSize << std::dec << std::endl;
                ++s_sifcallrpc_log_count;
            }
            else if (wantPre)
            {
                const uint32_t sendBuf = GPR_U32(ctx, 7);
                const uint32_t sendSize = GPR_U32(ctx, 8);
                std::cerr << "[GoW SifCallRpc] sid=0x" << std::hex << sid << " ra=0x" << ra << " th=" << std::dec << tid
                          << " send=0x" << std::hex << sendBuf << "+" << std::dec << std::min<uint32_t>(sendSize, 64) << std::dec << std::endl;
                ++s_sifcallrpc_log_count;
            }
            if (s_orig_sifcallrpc)
            {
                s_orig_sifcallrpc(rdram, ctx, runtime);
            }
            else
            {
                SET_GPR_S32(ctx, 3, 0x4E);
                runtime->handleSyscall(rdram, ctx, 0x0u);
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_176fc8 = nullptr;
        static int s_tree_repair_total = 0;

        void gow_tree_repair_pass(uint8_t *rdram)
        {
            // DISABLED 2026-10-04: BFS without a visited set walks garbage
            // u16 links across the whole heap and rewrites innocent memory.
            // Kept as a no-op stub so call sites stay intact; real fix must
            // validate nodes (magic/range/visited) before touching links.
            (void)rdram;
        }
        static int s_176fc8_log_count = 0;
        static int s_176fc8_key_log_count = 0;
        static bool s_176fc8_pool_dumped = false;

        void gow_176fc8_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            gow_tree_repair_pass(rdram);
            if (s_176fc8_key_log_count < 200)
            {
                const uint32_t sent = *reinterpret_cast<const uint32_t *>(rdram + 0x29C4B4u);
                const uint32_t tb = *reinterpret_cast<const uint32_t *>(rdram + 0x29C4BCu);
                const uint32_t tb10 = *reinterpret_cast<const uint16_t *>(rdram + (tb + 10));
                const uint32_t tb12 = *reinterpret_cast<const uint16_t *>(rdram + (tb + 12));
                std::cerr << "[GoW 176FC8 key] #" << s_176fc8_key_log_count << " a2=0x" << std::hex << GPR_U32(ctx, 6)
                          << " ra=0x" << GPR_U32(ctx, 31) << " s3=0x" << GPR_U32(ctx, 19) << " s4=0x" << GPR_U32(ctx, 20)
                          << " sent=0x" << sent << " tb=0x" << tb << " tb10=" << std::dec
                          << tb10 << " tb12=" << tb12 << std::dec << std::endl;
                ++s_176fc8_key_log_count;
            }
            if (!s_176fc8_pool_dumped)
            {
                s_176fc8_pool_dumped = true;
                std::cerr << "[GoW pool]";
                for (uint32_t off = 0x29C4B0u; off <= 0x29C4E4u; off += 4)
                {
                    std::cerr << " [" << std::hex << off << "]=" << *reinterpret_cast<const uint32_t *>(rdram + off);
                }
                std::cerr << std::dec << std::endl;
            }
            if (s_176fc8_log_count < 20)
            {
                const uint32_t s5 = GPR_U32(ctx, 21);
                const uint32_t s1 = GPR_U32(ctx, 17);
                const uint32_t a0 = GPR_U32(ctx, 4);
                const uint32_t a1 = GPR_U32(ctx, 5);
                const uint32_t a2 = GPR_U32(ctx, 6);
                std::cerr << "[GoW 176FC8 #" << s_176fc8_log_count << "] a0=0x" << std::hex << a0
                          << " a1=0x" << a1 << " a2=0x" << a2
                          << " s1=0x" << s1 << " s5=0x" << s5 << std::dec << std::endl;
                auto dumpW = [&](uint32_t addr, const char *tag) {
                    const uint32_t phys = addr & 0x1FFFFFFFu;
                    if (phys + 32 <= 0x2000000)
                    {
                        std::cerr << "  " << tag << " @0x" << std::hex << addr << " (phys 0x" << phys << "):";
                        for (int i = 0; i < 8; ++i)
                        {
                            const uint32_t w = *reinterpret_cast<const uint32_t *>(rdram + phys + i * 4);
                            std::cerr << " " << w;
                        }
                        std::cerr << std::dec << std::endl;
                    }
                    else
                    {
                        std::cerr << "  " << tag << " @0x" << std::hex << addr << " OUT-OF-RANGE" << std::dec << std::endl;
                    }
                };
                dumpW(a0, "a0");
                dumpW(s1, "s1");
                // s1[1] is a pointee record built from stream data; dump it too.
                {
                    const uint32_t s1phys = s1 & 0x1FFFFFFFu;
                    if (s1phys + 8 <= 0x2000000)
                    {
                        const uint32_t pointee = *reinterpret_cast<const uint32_t *>(rdram + s1phys + 4);
                        dumpW(pointee, "s1[1]");
                    }
                }
                // Walk the s3 child chain host-side exactly like 0x177470 does,
                // to see whether the chain cycles or runs off.
                {
                    const uint32_t s3 = GPR_U32(ctx, 19);
                    const uint32_t treeBase = *reinterpret_cast<const uint32_t *>(rdram + 0x29C4BCu);
                    std::cerr << "  walk s3=0x" << std::hex << s3 << " treeBase=0x" << treeBase << std::dec << std::endl;
                    uint32_t cur = s3;
                    for (int i = 0; i < 12; ++i)
                    {
                        if (cur < 0x100000 || cur + 16 > 0x2000000)
                        {
                            std::cerr << "    #" << i << " cur=0x" << std::hex << cur << " OOR" << std::dec << std::endl;
                            break;
                        }
                        const uint16_t lo = *reinterpret_cast<const uint16_t *>(rdram + cur + 10);
                        const uint16_t hi = *reinterpret_cast<const uint16_t *>(rdram + cur + 12);
                        const uint32_t key = *reinterpret_cast<const uint32_t *>(rdram + cur);
                        std::cerr << "    #" << i << " node=0x" << std::hex << cur << " key=0x" << key << " lo=" << std::dec
                                  << lo << " hi=" << hi << std::endl;
                        // advance like the search would for target a2
                        const uint32_t want = a2;
                        const uint16_t child = (want < key) ? lo : hi;
                        cur = treeBase + (static_cast<uint32_t>(child) << 4);
                        if (cur == treeBase)
                        {
                            std::cerr << "    reached treeBase (end)" << std::endl;
                            break;
                        }
                    }
                }
                dumpW(s5, "s5?");
                ++s_176fc8_log_count;
            }
            if (s_orig_176fc8)
            {
                s_orig_176fc8(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_13da10 = nullptr;
        static int s_13da10_log_count = 0;

        void gow_13da10_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t s0 = GPR_U32(ctx, 4);
            const uint32_t a1 = GPR_U32(ctx, 5);
            // Log only suspicious records (huge implied sizes); normal traffic
            // is far too hot to print.
            if (s_13da10_log_count < 12 && s0 >= 0x100000 && s0 + 32 <= 0x2000000)
            {
                const uint32_t w4 = *reinterpret_cast<const uint32_t *>(rdram + s0 + 4);
                const uint32_t w8 = *reinterpret_cast<const uint32_t *>(rdram + s0 + 8);
                const uint32_t w12 = *reinterpret_cast<const uint16_t *>(rdram + s0 + 12);
                const uint32_t w14 = *reinterpret_cast<const uint16_t *>(rdram + s0 + 14);
                // Real size = [s0+8] * [s0+14] + [s0+12]; heap = [s0+4].
                const uint64_t implied = static_cast<uint64_t>(w8) * w14 + w12;
                if (s_13da10_log_count < 40 && (implied > 0x4000000u || (w4 < 0x300000u && w4 != 0u)))
                {
                    std::cerr << "[GoW 13DA10 #" << s_13da10_log_count << "] s0=0x" << std::hex << s0 << " a1=0x" << a1
                              << " ra=0x" << GPR_U32(ctx, 31)
                              << " heap=0x" << w4 << " unit=0x" << w8 << " extra=0x" << w12 << " count=0x" << w14
                              << " implied=0x" << implied << std::dec << std::endl;
                    ++s_13da10_log_count;
                }
            }
            if (s_orig_13da10)
            {
                s_orig_13da10(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_13dcd8 = nullptr;
        static int s_13dcd8_log_count = 0;

        void gow_13dcd8_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            if (s_13dcd8_log_count < 8)
            {
                const uint32_t t0 = GPR_U32(ctx, 8);
                const uint32_t s2 = GPR_U32(ctx, 18);
                const uint32_t a1 = GPR_U32(ctx, 5);
                const uint32_t heapArg = GPR_U32(ctx, 4);
                std::cerr << "[GoW 13DCD8 lap #" << s_13dcd8_log_count << "] t0=0x" << std::hex << t0 << " s2=0x" << s2
                          << " want=0x" << a1 << " heapArg=0x" << heapArg;
                if (t0 >= 0x100000 && t0 + 8 <= 0x2000000)
                {
                    const uint32_t blk0 = *reinterpret_cast<const uint32_t *>(rdram + t0);
                    const uint32_t blk4 = *reinterpret_cast<const uint32_t *>(rdram + t0 + 4);
                    std::cerr << " blk[0]=0x" << blk0 << " blk[4]=0x" << blk4;
                }
                else
                {
                    std::cerr << " t0-OOR";
                }
                std::cerr << std::dec << std::endl;
                ++s_13dcd8_log_count;
            }
            if (s_orig_13dcd8)
            {
                s_orig_13dcd8(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_17fde0 = nullptr;
        static int s_17fde0_log_count = 0;

        void gow_17fde0_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            if (s_17fde0_log_count < 12 && (GPR_U32(ctx, 19) != 0 || s_17fde0_log_count < 6))
            {
                const uint32_t s3 = GPR_U32(ctx, 19);
                const uint32_t v0 = (s3 >= 0x100000 && s3 + 16 <= 0x2000000)
                                        ? *reinterpret_cast<const uint32_t *>(rdram + s3 + 12)
                                        : 0;
                uint32_t tgt = 0;
                uint16_t off56 = 0;
                if (v0 >= 0x100000 && v0 + 62 <= 0x2000000)
                {
                    tgt = *reinterpret_cast<const uint32_t *>(rdram + v0 + 60);
                    off56 = *reinterpret_cast<const uint16_t *>(rdram + v0 + 56);
                }
                std::cerr << "[GoW 17FDE0 #" << s_17fde0_log_count << "] s3=0x" << std::hex << s3 << " v0=0x" << v0
                          << " tgt=0x" << tgt << " [v0+56]=0x" << off56 << std::dec << std::endl;
                ++s_17fde0_log_count;
            }
            if (s_orig_17fde0)
            {
                s_orig_17fde0(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_26c4b8 = nullptr;
        static int s_26c4b8_log_count = 0;

        void gow_26c4b8_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            if (s_26c4b8_log_count < 4)
            {
                const uint32_t s4 = GPR_U32(ctx, 20);
                const uint32_t s1 = GPR_U32(ctx, 17);
                const uint32_t s2 = GPR_U32(ctx, 18);
                const uint32_t s0 = GPR_U32(ctx, 16);
                std::cerr << "[GoW 26C4B8 #" << s_26c4b8_log_count << "] s0=0x" << std::hex << s0 << " s1=0x" << s1
                          << " s2=0x" << s2 << " s4=0x" << s4 << std::dec << std::endl;
                auto dumpTab = [&](uint32_t base, const char *tag) {
                    const uint32_t phys = base & 0x1FFFFFFFu;
                    if (phys + 64 <= 0x2000000 && phys >= 0x100000)
                    {
                        std::cerr << "  " << tag << " @0x" << std::hex << base << ":";
                        for (int i = 0; i < 16; ++i)
                        {
                            std::cerr << " " << *reinterpret_cast<const uint32_t *>(rdram + phys + i * 4);
                        }
                        std::cerr << std::dec << std::endl;
                    }
                };
                dumpTab(s4 + 0x1370, "s4+1370");
                dumpTab(s1 + 0x1358, "s1+1358");
                dumpTab(s0 + 0x1360, "s0+1360");
                ++s_26c4b8_log_count;
            }
            if (s_orig_26c4b8)
            {
                s_orig_26c4b8(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        static PS2Runtime::RecompiledFunction s_orig_27cbd0 = nullptr;
        static int s_27cbd0_tab_dumps = 0;

        void gow_27cbd0_diag_hook(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            // Thread 2 parks at its entry while main is parked: use its
            // checkpoint resumes (fired per dispatch) to dump the issuer
            // tables in the settled state. Throttle hard.
            if (s_27cbd0_tab_dumps < 2)
            {
                static int s_calls = 0;
                if (++s_calls >= 400)
                {
                    s_calls = 0;
                    ++s_27cbd0_tab_dumps;
                    for (int t = 0; t < 3; ++t)
                    {
                        const uint32_t base = 0x2A1358u + t * 8u;
                        std::cerr << "[GoW tab#" << s_27cbd0_tab_dumps << "] @0x" << std::hex << base << ":";
                        for (int i = 0; i < 24; ++i)
                        {
                            std::cerr << " " << *reinterpret_cast<const uint32_t *>(rdram + base + i * 4);
                        }
                        std::cerr << std::dec << std::endl;
                    }
                }
            }
            if (s_orig_27cbd0)
            {
                s_orig_27cbd0(rdram, ctx, runtime);
            }
            else
            {
                ctx->pc = GPR_U32(ctx, 31);
            }
        }

        void applyGodOfWarOverrides(PS2Runtime &runtime)
        {
            std::cout << "[applyGodOfWarOverrides] Installing God of War hooks..." << std::endl;
            // Point CD LBN reads at the real disc image. Without this,
            // sceCdRead has no image and no LBN mapping, returns zeros, and
            // every resource list in the game stays corrupt (spins at
            // 0x170B98/0x17AA40 forever).
            {
                PS2Runtime::IoPaths paths = PS2Runtime::getIoPaths();
                if (paths.cdImage.empty())
                {
                    const char *envImage = std::getenv("PS2_CD_IMAGE");
                    std::vector<std::filesystem::path> candidates;
                    if (envImage && envImage[0] != '\0')
                    {
                        candidates.emplace_back(envImage);
                    }
                    if (!paths.elfDirectory.empty())
                    {
                        candidates.emplace_back(paths.elfDirectory / "God of War (USA).iso");
                        candidates.emplace_back(paths.elfDirectory / ".." / "God of War (USA).iso");
                        candidates.emplace_back(paths.elfDirectory / ".." / "Belgelerim" / "God of War (USA).iso");
                    }
                    candidates.emplace_back("/home/yigit/Belgelerim/God of War (USA).iso");
                    candidates.emplace_back("/home/yigit/Belgeler/God of War (USA).iso");
                    for (const auto &candidate : candidates)
                    {
                        std::error_code ec;
                        const std::filesystem::path normalized = std::filesystem::absolute(candidate, ec);
                        const std::filesystem::path test = ec ? candidate : normalized;
                        if (!test.empty() && std::filesystem::exists(test, ec) && !ec)
                        {
                            paths.cdImage = test.lexically_normal();
                            PS2Runtime::setIoPaths(paths);
                            std::cout << "[GoW CD] using image: " << paths.cdImage.string() << std::endl;
                            break;
                        }
                    }
                    if (PS2Runtime::getIoPaths().cdImage.empty())
                    {
                        std::cout << "[GoW CD] WARNING: no disc image found; LBN reads will fail" << std::endl;
                    }
                }
            }
            runtime.replaceFunction(0x0029BB78u, &gow_constructor_29bb78);
            runtime.replaceFunction(0x0026B6B0u, &gow_constructor_26b6b0);
            s_orig_memalloc = runtime.lookupFunction(0x0013DC78u);
            runtime.replaceFunction(0x0013DC78u, &gow_memalloc_hook);
            s_orig_resourcepool_create = runtime.lookupFunction(0x00185F28u);
            runtime.replaceFunction(0x00185F28u, &gow_resourcepool_create_hook);
            // Keep source-level real resource pool/tree paths visible for diagnosis.
            s_orig_tree_lookup = runtime.lookupFunction(0x001769F8u);
            runtime.replaceFunction(0x001769F8u, &gow_tree_lookup_hook);
            runtime.replaceFunction(0x002396B0u, &gow_skip_to_menu_hook);
            // VFS hooks remain disabled; dummy vtable functions are installed by the skip/menu hooks.
            s_orig_sub_1be550 = runtime.lookupFunction(0x001BE550u);
            runtime.replaceFunction(0x001BE550u, &gow_sub_1be550_hook);
            runtime.replaceFunction(0x0017A8B8u, &gow_force_menu_init_hook);
            s_orig_sub_17a910 = runtime.lookupFunction(0x0017A910u);
            // runtime.replaceFunction(0x0017A910u, &gow_sub_17a910_hook);
            s_orig_sub_180d08 = runtime.lookupFunction(0x00180D08u);
            // runtime.replaceFunction(0x00180D08u, &gow_sub_180d08_hook);
            s_orig_27cbd0 = runtime.lookupFunction(0x0027CBD0u);
            runtime.replaceFunction(0x0027CBD0u, &gow_27cbd0_diag_hook);
            s_orig_26c4b8 = runtime.lookupFunction(0x0026C4B8u);
            runtime.replaceFunction(0x0026C4B8u, &gow_26c4b8_diag_hook);
            s_orig_17fde0 = runtime.lookupFunction(0x0017FDE0u);
            runtime.replaceFunction(0x0017FDE0u, &gow_17fde0_diag_hook);
            s_orig_13dcd8 = runtime.lookupFunction(0x0013DCD8u);
            runtime.replaceFunction(0x0013DCD8u, &gow_13dcd8_diag_hook);
            s_orig_13da10 = runtime.lookupFunction(0x0013DA10u);
            runtime.replaceFunction(0x0013DA10u, &gow_13da10_diag_hook);
            s_orig_176fc8 = runtime.lookupFunction(0x00176FC8u);
            runtime.replaceFunction(0x00176FC8u, &gow_176fc8_diag_hook);
            s_orig_sifcallrpc = runtime.lookupFunction(0x00297470u);
            runtime.replaceFunction(0x00297470u, &gow_sifcallrpc_diag_hook);
            runtime.replaceFunction(0x00171008u, &gow_sub_171008_hook);
            s_orig_sub_17fd10 = runtime.lookupFunction(0x0017FD10u);
            // runtime.replaceFunction(0x0017FD10u, &gow_sub_17fd10_hook);
            runtime.replaceFunction(0x0015F1E8u, &gow_sub_15f1e8_hook);
            runtime.replaceFunction(0x00293A20u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                printf("[CreateThread Hook] ee_thread_t addr=0x%08x\n", GPR_U32(ctx, 4));
                SET_GPR_S32(ctx, 3, 0x20); // v1 = 0x20
                runtime->handleSyscall(rdram, ctx, 0x0u);
                ctx->pc = GPR_U32(ctx, 31);
                printf("[CreateThread Hook] returned thid=%d\n", GPR_S32(ctx, 2));
            });
            runtime.replaceFunction(0x00282148u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                // Original returns v0=1 on success; v0=0 triggers init-failure
                // cleanup at 0x27C248 which deletes semaphores 3/4/5.
                SET_GPR_U64(ctx, 2, 1); // v0 = 1 (success)
                ctx->pc = GPR_U32(ctx, 31);
            });
            // runtime.replaceFunction(0x0017AA18u, &gow_sub_17aa18_hook);
            runtime.replaceFunction(0x00293A30u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                uint32_t thid = GPR_U32(ctx, 4);
                uint32_t arg = GPR_U32(ctx, 5);
                printf("[StartThread Hook] thid=%d arg=0x%08x\n", thid, arg);
                // Call original StartThread syscall 0x22
                SET_GPR_S32(ctx, 3, 0x22); // v1 = 0x22
                runtime->handleSyscall(rdram, ctx, 0x0u);
                ctx->pc = GPR_U32(ctx, 31);
            });
            runtime.replaceFunction(0x00299120u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                SET_GPR_U64(ctx, 2, 1);
                ctx->pc = GPR_U32(ctx, 31);
            });
            runtime.replaceFunction(0x002990D0u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                SET_GPR_U64(ctx, 2, 1);
                ctx->pc = GPR_U32(ctx, 31);
            });
            runtime.replaceFunction(0x0027AB00u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                SET_GPR_U64(ctx, 2, 1);
                ctx->pc = GPR_U32(ctx, 31);
            });
            runtime.replaceFunction(0x0017BBC8u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
                SET_GPR_U64(ctx, 2, 1);
                ctx->pc = GPR_U32(ctx, 31);
            });
            // runtime.replaceFunction(0x293AB0u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
            //     SET_GPR_S32(ctx, 2, 0);
            //     ctx->pc = GPR_U32(ctx, 31);
            // });
            // runtime.replaceFunction(0x0027CBD0u, [](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
            //     std::cerr << "[Thread2 WaitStub] 0x27CBD0 -> SleepThread" << std::endl;
            //     SET_GPR_S32(ctx, 3, 0x32);
            //     uint32_t ra = GPR_U32(ctx, 31);
            //     ctx->pc = ra;
            //     runtime->handleSyscall(rdram, ctx, 0x0u);
            //     SET_GPR_S32(ctx, 2, 0);
            //     ctx->pc = ra;
            // });
            // runtime.replaceFunction(0x0017A9B0u, &gow_sub_17a9b0_hook);
            // runtime.replaceFunction(0x0026BF28u, &gow_sub_26bf28_hook);
            runtime.setMissingFunctionPolicy(PS2Runtime::MissingFunctionPolicy::SkipCallDebug);
        }
    }

    PS2_REGISTER_GAME_OVERRIDE("GodOfWar_Overrides", "SCUS_973.99", 0x100008u, 0u, applyGodOfWarOverrides);
}

// Gradius III & IV (gradius.elf, entry 0x100008): statically linked libsifcmd
// boot. Raw SIFCMD BIND packets bypass the HLE SifBindRpc stub, so the IOP
// reply never arrives and the boot thread parks in WaitSema forever (purple
// placeholder screen). Arm the synchronous BIND completion assist: BINDs for
// HLE-bindable sids complete inline (client server-word + waiter release).
namespace
{
    void ApplyGradiusRawSifAssist(PS2Runtime &runtime)
    {
        runtime.setRawSifCompletionAssist(true);
        std::cout << "[game_overrides] gradius: raw-SIFCMD completion assist armed" << std::endl;
    }

    PS2_REGISTER_GAME_OVERRIDE("gradius-raw-sif-assist",
                               "gradius.elf",
                               0x100008u,
                               0u,
                               &ApplyGradiusRawSifAssist);
}
