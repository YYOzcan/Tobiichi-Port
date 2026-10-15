# Visual audit of the zone captures

This is a list of suspected rendering defects. It was made by looking at every zone capture in the latest gate,
`port/merged17/20261012_161100/zone_slot0..4`, and at earlier `port/merged*` runs, and comparing them with the
PCSX2 snapshots in `ref/pcsx2/snaps`. Each entry needs checking against PCSX2 at the same game state before it is
fixed.

Captures are 1024x894 crops of the 1920x1080 window. "Frame N" means `gow_pad_test_N.png`.

Defects already being handled elsewhere are left out:
- torch ember "4-petal stars", the ship's water splash stars and souls (fixed by the PACKED ST Q latch);
- Kratos's floor shadow rectangle in Olympus: FIXED 2026-10-13 (VU1 flag latency across native blocks, docs/vu1-native-flags.md);
- the Kratos tint and the save-room dust.

## Suspected defects

| # | Zone (slot) | Captures | Region | What is wrong | Likely cause | Confidence |
|---|---|---|---|---|---|---|
| 1 | all (0-4) | every frame | top 4 rows, left 3 columns | **Edge band.** On PCSX2 the top row is black, the next is half bright and the rest is uniform, and the left edge is uniform (`20261012113302.png`: 0/57/99/99...; left 52/52/52). Ours: rows 0-1 are dark but not black, rows 2-3 are *brighter* than the image below (slot 0: 106/106/160/148/97), column 0 is black and columns 1-2 are bright (slot 3: 0/240/240/142). The thin coloured or white line along the top is visible in every sheet (red-orange in Cliffs, grey on the ship). | Edge handling at 2x internal resolution in the game's full-screen post passes: the 8-pixel column strip copies (draws 24-47 of the PCSX2 Desert dump, tbp 0/0x2800, x=8-64) and the bloom/fog sprites sample outside the frame or are offset by one PS2 pixel when scaled. The row-0 black line (a GS line primitive) covers only half the scaled rows. | high (measured) |
| 2 | Cliffs (3), Desert (2), slot 4 | slot 4 frame 4 (beside Kratos at the pillar); slot 4 frames 2, 3, 5; slot 3 frame 2 (dark brown silhouette on the near pole) | Kratos's shadow on vertical or near surfaces | The shadow falls onto walls and pillars as an **opaque black wedge** from Kratos's head height to the floor. On the ground it is a hard black blob with stair-stepped edges, not a soft dark area. | Probably the same root cause as the Olympus floor rectangle: shadow pass alpha/Z handling (Z-inversion shadow tracking, ext ff3cf11). **Pass these captures to the shadows fork.** | FIXED 2026-10-13: the cause was the VU1 culling flags (docs/vu1-native-flags.md); port/merged22 shows soft shadows, no wedges |
| 3 | Desert (2), Cliffs (3) | frame 0 vs frame 1, in **every** run since merged_present | chest next to the save point (slot 2: x 880-1000, y 380-460; slot 3: left) | The chest glow is **blue in frame 0 and green in frame 1**, always the same way. The PCSX2 snapshot near frame 0's moment shows blue. | Either the game's real behaviour (the glow cycles), or a palette lookup problem: the palette cache key (`paletteFor`: clutHash + cpsm/csm/csa, **no cbp**) could return a cached palette of another CLUT with the same hash. Check with a PCSX2 dump at the frame-1 moment before changing anything. **Resolved 2026-10-12: not a bug, the user confirms the colour change is the game's normal behaviour.** | none |
| 4 | Cliffs (3) | frame 2 | right half | Near-camera geometry (a large pole and a bone-like column) fills the view, and a dark brown silhouette sits on the pole. | Probably the camera passing through scenery (it may be like that on PS2 too). The silhouette is #2. Check in PCSX2 at the same spot. | low |
| 5 | new game, ship (user) | second hydra fight, when the boss grabs Kratos | the screen | "Bugged fog" for a moment (user report 2026-10-13). | Not reproduced: the scripted new-game runs (port/newgame2) do not reach the hydra fights (they stop before the trap door), and no save is near them. Next: a save made right before the fight, then compare with PCSX2 at the grab. | FIXED: user confirmed 2026-10-13 on the build with the edge and strip-seam fixes (agent/edge2, agent/text); no separate fix needed |

## Checked and fine

The following matched PCSX2 or looked plausible:
- **Desert (slot 2):** flames (texture 0x39f0), the sandstorm fog, distant torches.
- **Olympus (slot 1):** torches, the throne hall, the reflective floor, apart from the known shadow rectangle.
- **Ship (slot 0):** rain streaks, the ripple rings on the deck, the HUD (health and magic bars, orb counter, hit counter).
- **All zones:** the right and bottom edges are uniform.

- Vertical bars / notched text over the whole screen (user, 2026-10-13): FIXED (agent/text). The per-sprite UV clamp from agent/visual3 clamped every 32-pixel strip of full-screen passes, the logo and fonts to its own texels; it now stays open on sides shared with the previous strip. Title menu A/B: port/text/menu_old vs port/text/menu_fix.
