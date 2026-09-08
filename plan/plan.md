# cub3D — 15-Day Work Plan for 2 People

Roles referenced below: **Partner A** and **Partner B** — assign these however fits your strengths (e.g. one more comfortable with math/graphics, the other with parsing/C structure), but both must understand the whole project by the end.

General rules for working as a pair:
- Agree on shared data structures (the `t_game`/`t_map` struct, etc.) on Day 1 before splitting work — this prevents painful merge conflicts.
- Use a shared Git repo with feature branches, and review each other's code via pull requests/merges — you both need to be able to explain any part during defense.
- Do a quick 15-minute daily sync (even by text) to unblock each other.

---

## Phase 1 — Setup & Study (Days 1–2)

**Day 1 — Both together**
- Read the whole subject carefully as a pair, list every mandatory requirement
- Study session together: vectors, trig basics, raycasting concept overview
- Set up the Git repo, Makefile skeleton (`all`, `clean`, `fclean`, `re`, `bonus`), norm-compliant folder structure
- Agree on core data structures (map struct, player struct, ray struct, image/texture struct)
- Get MiniLibX installed and a basic window opening ("hello window") as a shared test

**Day 2 — Both together (or split by strength)**
- Partner A: deep dive into raycasting math (DDA, perpendicular distance, wall side detection) — study Lode's tutorial in detail
- Partner B: deep dive into MiniLibX specifics (image buffer, hooks, key events) and file parsing strategy
- End of day: swap notes, make sure you both understand both halves at a basic level

---

## Phase 2 — Parsing & Core Structures (Days 3–5)

**Partner A — Raycasting engine skeleton**
- Day 3: Set up the basic window + game loop (`mlx_loop_hook`), hardcode a test map, draw a static top-down 2D representation of it (sanity check before going 3D)
- Day 4: Implement DDA raycasting for one column, get a single vertical wall slice rendering correctly
- Day 5: Loop over all screen columns, get a full "flat color" 3D wall view working (no textures yet), fix fisheye distortion

**Partner B — Parser & scene loader**
- Day 3: `.cub` file reading, tokenizing lines, identifying element types (NO/SO/WE/EA/F/C/map)
- Day 4: Validate texture paths and F/C color values (RGB range checks), robust error handling ("Error\n" + message)
- Day 5: Map validation — check only valid characters, check map is closed/surrounded by walls, locate and validate player spawn (N/S/E/W), handle map lines of differing lengths (padding with spaces)

**End of Day 5 checkpoint (both together):** merge branches, connect parser output to the raycasting engine's map input, confirm hardcoded test map from Day 3 can now be swapped for a real parsed `.cub` file.

---

## Phase 3 — Integration: Textures & Movement (Days 6–9)

**Partner A — Textures**
- Day 6: Load textures with MiniLibX (`mlx_xpm_file_to_image` or equivalent), store texture buffers
- Day 7: Map wall-hit side (N/S/E/W) to correct texture, compute texture X-coordinate from wall hit position
- Day 8: Full textured wall rendering, floor and ceiling flat-color fill

**Partner B — Player movement & input**
- Day 6: Keyboard hooks for ESC (clean exit) and window close (red cross)
- Day 7: W/A/S/D movement (forward/back/strafe) updating player position
- Day 8: Left/right arrow keys to rotate the camera direction + camera plane vectors correctly

**Day 9 — Both together**
- Integrate movement + textures, playtest together, fix bugs
- Add delta-time based movement using `gettimeofday()` so speed is frame-rate independent
- Start basic wall-collision so you don't walk through walls (also useful groundwork for bonus)

---

## Phase 4 — Stabilize, Clean, Test (Days 10–12)

**Both — split by test focus**
- Day 10: Stress-test parser with malformed maps (unclosed maps, bad chars, missing elements, wrong order where relevant) — make sure every error case returns cleanly with "Error\n"
- Day 11: Memory leak checking (valgrind or equivalent), fix double frees / leaks, check window resize/minimize behavior stays smooth
- Day 12: Norm check on ALL files (mandatory is graded at 0 if norm fails), refactor long functions, clean up

---

## Phase 5 — Bonus (Days 13–14) — ONLY if mandatory is 100% solid

Remember: bonuses are only evaluated if the mandatory part is perfect. Don't start this early if mandatory isn't rock solid.

Split bonus features between you, e.g.:
- **Partner A:** Minimap system, animated sprites
- **Partner B:** Mouse-based camera rotation, doors that open/close

Day 13: implement individually. Day 14: integrate together, test combined bonus features don't break the mandatory part.

---

## Phase 6 — Final Polish & Defense Prep (Day 15)

- Full run-through of every subject requirement as a checklist, both of you testing independently
- Write/finalize the `README.md` (description, instructions, resources used, AI usage disclosure per Chapter VI)
- Mock defense: each partner explains the OTHER partner's code out loud to catch understanding gaps
- Prepare test maps covering edge cases (very small map, large map, weird valid spacing) for use during defense
- Final `git` cleanup: check Makefile compiles cleanly with `-Wall -Wextra -Werror`, confirm `bonus` rule works separately

---

## Quick Checklist Before Submission
- [ ] Norm-compliant (mandatory + bonus files)
- [ ] No crashes on any input, including garbage/malformed `.cub` files
- [ ] No memory leaks
- [ ] Makefile has `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`
- [ ] ESC and red-cross both quit cleanly
- [ ] Textures correctly mapped per wall side (N/S/E/W)
- [ ] Floor/ceiling colors configurable
- [ ] README.md meets all Chapter VI requirements, first line formatted exactly as required
- [ ] Both partners can explain every part of the code
