# Post a key chord (optional Shift) to every window of a process (incl. child windows), no focus needed.
param([string]$proc, [int]$vk, [int]$scan, [switch]$shift)
Add-Type @"
using System; using System.Collections.Generic; using System.Runtime.InteropServices;
public class K {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc f, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr p, EnumProc f, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  public static List<IntPtr> Windows(uint pid) {
    var list = new List<IntPtr>();
    EnumWindows((h, l) => { uint p; GetWindowThreadProcessId(h, out p); if (p == pid) { list.Add(h); EnumChildWindows(h, (c, l2) => { list.Add(c); return true; }, IntPtr.Zero); } return true; }, IntPtr.Zero);
    return list;
  }
}
"@
$p = Get-Process $proc | Select-Object -First 1
$wins = [K]::Windows([uint32]$p.Id)
foreach ($h in $wins) {
  if ($shift) { [void][K]::PostMessage($h, 0x100, [IntPtr]0x10, [IntPtr](1 -bor (0x2A -shl 16))) }
  [void][K]::PostMessage($h, 0x100, [IntPtr]$vk, [IntPtr](1 -bor ($scan -shl 16)))
}
Start-Sleep -Milliseconds 200
foreach ($h in $wins) {
  [void][K]::PostMessage($h, 0x101, [IntPtr]$vk, [IntPtr]([int64](1 -bor ($scan -shl 16)) -bor 0xC0000000))
  if ($shift) { [void][K]::PostMessage($h, 0x101, [IntPtr]0x10, [IntPtr]([int64](1 -bor (0x2A -shl 16)) -bor 0xC0000000)) }
}
"posted to $($wins.Count) windows"
