# Send a held key to a window without needing focus (WM_KEYDOWN ... WM_KEYUP).
# usage: key.ps1 <process> <delaySeconds> <holdMs> <vk> <scancode> [repeat]
param([string]$proc, [int]$delay, [int]$hold, [int]$vk, [int]$scan, [int]$repeat = 1)
Add-Type @"
using System; using System.Runtime.InteropServices;
public class W { [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l); }
"@
Start-Sleep -Seconds $delay
for ($r = 0; $r -lt $repeat; $r++) {
  $p = Get-Process $proc -ErrorAction SilentlyContinue | Select-Object -First 1
  if (-not $p) { exit 1 }
  $h = $p.MainWindowHandle
  $down = [IntPtr](1 -bor ($scan -shl 16))
  $up = [IntPtr]([int64](1 -bor ($scan -shl 16)) -bor 0xC0000000)
  [void][W]::PostMessage($h, 0x100, [IntPtr]$vk, $down)
  Start-Sleep -Milliseconds $hold
  [void][W]::PostMessage($h, 0x101, [IntPtr]$vk, $up)
  Start-Sleep -Milliseconds 500
}
