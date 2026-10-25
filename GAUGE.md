# Asurada / Cyber Formula 240x240 HUD

The simulator now starts the new gauge instead of the old `SF_Sniper_UI()` demo.

## Screens

| Boot | Main |
| --- | --- |
| ![boot](screenshots/boot.png) | ![main](screenshots/main.png) |

| Boost | Spiral |
| --- | --- |
| ![boost](screenshots/boost_start.png) | ![spiral](screenshots/spiral.png) |

The boost dial keeps 24 faint unlit spokes and a small central hub.  The
countdown cut-out, its yellow border and the digit positions are fixed; the
red fan, the green recovery wedge, the five lower recovery bars and the red
leading marker near the end of the countdown change:

| Boost mid | Boost late |
| --- | --- |
| ![boost mid](screenshots/boost_mid.png) | ![boost late](screenshots/boost_late.png) |

## Demo sequence and timing

```
BOOT -> MAIN -> BOOST -> MAIN -> SPIRAL -> MAIN -> BOOST ...
```

| Mode | Duration | Notes |
| --- | --- | --- |
| Boot | 6.2 s | Ring self-check, title band, system checks, `READY FOR START` |
| Main | 8.5 s | Non-linear 5..17 scale, speed sweep 0 -> 576, then hold |
| Boost | 20.0 s | 24-spoke red fan, 20.0 -> 00.0 countdown, five recovery bars |
| Spiral | 7.0 s | Two rotating orange quadrants, 18 nodes, 6 -> 0 countdown |

Timing constants are at the top of `Src/Gauge.c`:

```c
#define BOOT_MS            6200u
#define MAIN_MS            8500u
#define BOOST_MS          20000u
#define SPIRAL_MS          7000u
#define BOOST_DISPLAY_SEC  20.0f
```

## Source layout

- `Src/Gauge.c` - full HUD rendering, demo state machine, raster helpers. The
  Main numerals, Boost countdown and Spiral countdown are drawn by a compact
  seven-segment raster routine, so they can be sized for the 240px hub.
- `Src/Gauge.h` - `Gauge_Init()`, `Gauge_TriggerBoost()`, `Gauge_TriggerSpiral()`.
- `LVGL_UI.c` - startup now calls `Gauge_Init()`.
- `LittlevGL.cbp` - includes `Src/Gauge.c` and `Src/Gauge.h`.
- `UI/fonts/ui_font_Seg40.c`, `ui_font_Seg48.c` - legacy assets retained in
  the project, but no longer referenced by the current canvas renderer.

## Build / run

Open `LVGL-PC/LittlevGL.cbp` in Code::Blocks (MinGW) and build the `Debug` target, or use:

```powershell
& 'D:\CodeBlocks\codeblocks.exe' --build --target=Debug '.\LVGL-PC\LittlevGL.cbp'
```

The executable is `LVGL-PC/bin/Debug/LittlevGL.exe`.

## ESP32 integration

The rendering source has been copied into the firmware:

- `main/ui/gauge_ui.c` - same HUD state machine and raster code.
- `main/ui/gauge_ui.h` - public `Gauge_Init()` / trigger API.
- `main/ui/fonts/ui_font_Seg40.c`, `ui_font_Seg48.c` - seven-segment fonts.
- `main/main.c` - `ui_init()` now calls `Gauge_Init()`.
- `main/CMakeLists.txt` - includes the gauge and font sources.
- `sdkconfig` / `sdkconfig.defaults` - Montserrat 8/10/12/14/16/18/20/28
  enabled (the labels use 14 and 18, the boot readout uses 14).

Two firmware builds were verified:

| Build | Flash / PSRAM | Partition table | Result |
| --- | --- | --- | --- |
| `build` | 8MB / 2MB quad (N8R2) | `partitions.csv` | OK, 0x168fc0 app, 57% free |
| `build_n16r8` | 16MB / 8MB octal (N16R8) | `partitions_16mb.csv` | OK, 0x169e60 app, 76% free |

The N16R8 build was produced with:

```powershell
idf.py -B build_n16r8 -D SDKCONFIG=build_n16r8/sdkconfig `
  -D SDKCONFIG_DEFAULTS="sdkconfig.defaults;boards/n16r8.defaults" build
```

`partitions_16mb.csv` uses two 6MB OTA slots plus a 3968KB FAT storage
partition. The workspace root `sdkconfig` is still the N8R2 test
configuration; use the N16R8 command above (or switch the board defaults and
regenerate `sdkconfig`) when flashing the final N16R8 board.

### N16R8 HUD bring-up image (camera off)

The current camera pin table uses GPIO35/36/37, which are reserved for octal
PSRAM on the N16R8. For a display-only bring-up, use the extra defaults file:

```powershell
idf.py -B build_n16r8_ui -D SDKCONFIG=build_n16r8_ui/sdkconfig `
  -D SDKCONFIG_DEFAULTS="sdkconfig.defaults;boards/n16r8.defaults;boards/n16r8_ui.defaults" build
idf.py -B build_n16r8_ui -p COM5 flash
```

This keeps flash size, octal PSRAM and the 16MB partition table, but leaves the
camera off. WiFi/SD/web/OTA are unchanged. Re-enable the camera only after
moving its pins away from GPIO33-37 (and checking the LCD/I2S pins).

## Portability notes

- Rendering is plain LVGL 8.x C: one 240x240 `lv_canvas`, a static main background,
  and overlay labels.  Arcs, lines, circles (r >= 3), solid annular sectors, pie
  slices and polygons use LVGL's `lv_canvas_draw_*()` rasterizers for their
  anti-aliased edges.  Axis-aligned rectangles/digits and the patterned Main
  bands remain custom raster code.
- The Main scale uses a per-label angle/radius table matching the reference
  composition: 5..7 sit inward near the hub, 13..17 move out to the rim, and
  the coloured sectors/ticks follow the same angle table.
- On ESP32 the three buffers use `heap_caps_malloc(..., MALLOC_CAP_SPIRAM)`:
  framebuffer, static main background, and a 240x240 angle map
  (about 345 KB total).
- The gauge assumes a 240x240 display (GC9A01). The current `sdkconfig` and the
  N16R8 defaults both select GC9A01 240x240.
- Both firmware targets compile, but no display / camera / audio / SD hardware
  validation has been performed yet. Final N16R8 camera / LCD / SD / I2S pin
  assignments still need the hardware confirmation described in the main README.
