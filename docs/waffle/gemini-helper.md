# Helper agent (Antigravity `agy` / Gemini) — offload heavy reading

A second AI (Antigravity CLI, Gemini models, user's Google AI Pro account) can do **read-only analysis** so the main
session keeps its context small. It never edits project code or docs. Folder: `gemini-work/` (see its README.md).

## When to use it
- Summarize/extract from big files: run logs (`port/*.log`), disassembly dumps, `analysis_sections.txt`, trace output.
- Search for how other projects solved something (PS2 GS/VU1, shaders, SPU2, Switch limits) and report links + findings.
- Review a patch or a hypothesis for a bug (second opinion).
- Write standalone helper scripts into `gemini-work/` (never into `tools/` directly; copy after review).

Do NOT use it for: editing runtime/recompiler code, builds, running the game, anything needing this session's context.

## How to call it (from Bash, cwd = `God Of War/gemini-work`)
1. Write the task to `gemini-work/requests/<name>.md`: goal, exact files/paths to read, the wanted output format,
   and "mark anything unverified". Be specific; the helper has no project context beyond `docs/` and what you name.
2. Run:

       cd "C:/Users/lovas/Claude/God Of War/gemini-work"
       "$LOCALAPPDATA/agy/bin/agy.exe" --add-dir .. -p "Read ../docs/README.md and ../docs/status.md, then do the task in requests/<name>.md. Print only the answer." --print-timeout 300s > results/<name>.md

   Run it in the background (`run_in_background`) for long jobs and keep working meanwhile.
3. Read `results/<name>.md`. **Verify** claims against the real files before trusting them (addresses, line numbers).
   Move confirmed facts into the proper doc here; delete or correct the rest.

## Constraints
- Headless mode cannot ask permission. `~/.gemini/antigravity-cli/settings.json` allows read on `God Of War/` and write
  only to `gemini-work/results`. Never use `--dangerously-skip-permissions`.
- If it prints "no output produced ... permission", check the `--log-file <path>` output for "malformed" (the settings
  JSON must use forward slashes, no backslashes).
- Gemini CLI (`gemini`) is dead for personal accounts since 2026-06-18; only `agy` works.
- Quota on the Pro plan is unmeasured: prefer a few big, well-scoped tasks over many tiny ones.
- Models: `agy models`. Default is fine; `--model gemini-3.1-pro-high` for harder analysis (**unverified** cost/quota).

## Verified 2026-10-09
- Smoke test ok: `agy` read `docs/status.md` and answered. A prompt that lets it reach for a shell command fails headless
  with "tool required the command permission ... auto-denied": tell it explicitly "use read_file only (no shell commands)".
- Launcher setup: desktop `Avvia Claude.exe` runs `claude` in PowerShell; `$PROFILE` defines `claude` = `caveman wrap claude`.
  rtk hook is global in `~/.claude/settings.json`. `caveman mcp/hooks install gemini` targets the dead Gemini CLI (harmless, unused);
  the real helper here is `agy`.

## Launcher / proxy chain (2026-10-09, evening)
- Gemini CLI (`@google/gemini-cli`) uninstalled, with its caveman hook/MCP. Only `agy` is used.
- Chain: Claude -> headroom proxy :8788 -> caveman proxy :8787/w/claude -> Anthropic. `~/.claude/settings.json` env
  `ANTHROPIC_BASE_URL` = `http://127.0.0.1:8788` (backup `settings.json.bak-headroom`). rtk is a Bash PreToolUse hook.
- `$PROFILE` function `claude` starts headroom (hidden) if :8788 is down, then `caveman wrap claude`.
- headroom: `pip install --user "headroom-ai[proxy,code]"` (0.40.0), exe in `%APPDATA%\Python\Python311\Scripts` (added to user PATH).
- Desktop `Avvia Claude.exe` rebuilt from `C:\Users\lovas\Claude\launcher\AvviaClaude.cs` (csc, .NET Framework 4); original kept as
  `AvviaClaude.original.exe`. Bottom bar = start folder with "Cambia..." (saved in `%APPDATA%\AvviaClaude\folder.txt`).
- 2026-10-09 late: three code-review tasks (fog-packed-regs, widescreen-ecode-review, gs-shuffle-review) returned
  **empty** output: "print timeout after 10m0s with turn in progress; returning partial output". Multi-file
  cross-repo code comparisons are too big for one headless turn: give one file + one function per task.
