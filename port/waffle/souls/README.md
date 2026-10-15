# Souls / particles: junk-Q draws (fork F5, 2026-10-12 20:3x, investigation only, no build)

`junkq_scan.py <pcsx2 dump.gs>` lists the draws whose PACKED vertices are ST-only and whose ST word 2 (Q latch) differs
from the RGBAQ.Q in effect, i.e. the draws that rendered with junk Q before ext c25562c.

All 9 USA PCSX2 dumps in ref/pcsx2/snaps (Desert spots): the only such draws are `tbp=0 prim=0x5d` (TRIFAN, gouraud,
textured from the frame buffer at TBP 0, TCC=0, alpha from vertex): the heat-haze/refraction fans. 518-5264 vertices per
frame, 93 % of their vertices carry junk Q (1.0 only on the fan centre that follows the ST,RGBAQ,XYZF2,RGBAQ head tag;
then 14-loop ST,XYZF2 tags with Q words like 8.4e6, 0.0067, 1.2e-38, -7.3). No other draw in those dumps is affected.

Souls (red orbs) are not in any reference dump (no ship / no kill in the PCSX2 snaps), and the scripted slot-0 runs never
collect an orb (HUD orb counter stays 0 in port/newgame/ng1, ng2, merged13-17 zone_slot0), so their draws could not be
identified offline. The ship's water splash shows the same 4-point star artefact as the torch heat haze, so it is very
likely the same refraction fan (covered by c25562c). Whether the souls use the refraction fan is open: check with the
c25562c build, slot 0 with kills, `PS2X_GS_TRACE_TBP=-3` (textured fans) and a capture of an orb pickup.
