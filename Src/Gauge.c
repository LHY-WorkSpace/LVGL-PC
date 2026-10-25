/*
 * Cyber Formula / Asurada style 240x240 HUD.
 *
 * One full-screen LVGL canvas is used for the mechanical parts, with a few
 * LVGL labels on top for text.  The rendering code is plain LVGL 8.x C and is
 * shared by the LVGL-PC simulator and the ESP32-S3 GC9A01 firmware.
 *
 * Demo sequence:
 *   BOOT -> MAIN -> BOOST -> MAIN -> SPIRAL -> MAIN -> BOOST ...
 */

#include "Gauge.h"

#if defined(ESP_PLATFORM)
#include "lvgl.h"
#include "esp_heap_caps.h"
#define GAUGE_MALLOC(sz) heap_caps_malloc((sz), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT)
#else
#include "lvgl/lvgl.h"
#define GAUGE_MALLOC(sz) malloc(sz)
#endif

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

LV_FONT_DECLARE(ui_font_Seg40)
LV_FONT_DECLARE(ui_font_Seg48)

#define GAUGE_W       240
#define GAUGE_H       240
#define GAUGE_CX      120
#define GAUGE_CY      120
#define GAUGE_PI      3.14159265358979323846f

#define MAIN_R_OUT    108
#define MAIN_R_IN     61
#define MAIN_LABEL_R  86

/* Demo timing.  BOOST_MS is a full 20 second countdown. */
// #define BOOT_MS            6200u
// #define MAIN_MS            8500u
#define BOOT_MS            2200u
#define MAIN_MS            2500u
#define BOOST_MS          20000u
#define SPIRAL_MS          7000u
#define BOOST_DISPLAY_SEC  20.0f

/* The boost countdown frame is fixed.  Only the red fan and the green
 * recovery wedge change while the timer runs; the black cut-out, its yellow
 * border and the digit positions must not move.  All positions are derived
 * from the gauge centre (GAUGE_CX / GAUGE_CY). */
#define BOOST_HUB_R        18

typedef enum {
    MODE_BOOT = 0,
    MODE_MAIN,
    MODE_BOOST,
    MODE_SPIRAL
} gauge_mode_t;

static lv_obj_t *s_canvas;
static lv_color_t *s_fb;
static lv_color_t *s_main_bg;
static uint16_t *s_angle_map;

static lv_obj_t *s_main_layer;
static lv_obj_t *s_boot_layer;
static lv_obj_t *s_boost_layer;
static lv_obj_t *s_spiral_layer;

static lv_obj_t *s_outer_label[13];
static lv_obj_t *s_oil_label;
static lv_obj_t *s_stack_label;
static lv_obj_t *s_acr_label[3];
static lv_obj_t *s_gear_label[8];

static lv_obj_t *s_boot_title;
static lv_obj_t *s_boot_title_b;
static lv_obj_t *s_boot_title_c;
static lv_obj_t *s_boot_sub;
static lv_obj_t *s_boot_left[5];
static lv_obj_t *s_boot_right[5];
static lv_obj_t *s_boot_driver;
static lv_obj_t *s_boot_driver_b;
static lv_obj_t *s_boot_master;
static lv_obj_t *s_boot_ready;
static lv_obj_t *s_boot_ready_b;

static lv_obj_t *s_boost_frac;
static lv_obj_t *s_boost_sec;

static lv_obj_t *s_stop_label;

static gauge_mode_t s_mode;
static gauge_mode_t s_main_next = MODE_BOOST;
static uint32_t s_mode_start;

static int16_t s_sin[720];
static int16_t s_cos[720];

static lv_color_t c_black;
static lv_color_t c_white;
static lv_color_t c_blue;
static lv_color_t c_cyan;
static lv_color_t c_orange;
static lv_color_t c_red;
static lv_color_t c_yellow;
static lv_color_t c_green;
static lv_color_t c_dark_green;
static lv_color_t c_magenta;
static lv_color_t c_gray;
static lv_color_t c_dark;
static lv_color_t c_grid;
static lv_color_t c_teal;
static lv_color_t c_band_blue;
static lv_color_t c_band_yellow;
static lv_color_t c_band_red;
static lv_color_t c_band_magenta;
static lv_color_t c_red_deep;
static lv_color_t c_boost_yellow;
static lv_color_t c_boost_green;
static lv_color_t c_boost_red;
static lv_color_t c_spoke;

/* ------------------------------------------------------------------------- */
/* Raster helpers                                                             */
/* ------------------------------------------------------------------------- */

static inline void put_px(int x, int y, lv_color_t c)
{
    if((unsigned)x < GAUGE_W && (unsigned)y < GAUGE_H) {
        s_fb[y * GAUGE_W + x] = c;
    }
}

static void clear_fb(lv_color_t c)
{
    int i;
    for(i = 0; i < GAUGE_W * GAUGE_H; i++) s_fb[i] = c;
}

static void fill_rect(int x, int y, int w, int h, lv_color_t c)
{
    int x0 = x;
    int y0 = y;
    int x1 = x + w;
    int y1 = y + h;
    int xx;
    int yy;

    if(x0 < 0) x0 = 0;
    if(y0 < 0) y0 = 0;
    if(x1 > GAUGE_W) x1 = GAUGE_W;
    if(y1 > GAUGE_H) y1 = GAUGE_H;
    if(x0 >= x1 || y0 >= y1) return;

    for(yy = y0; yy < y1; yy++) {
        for(xx = x0; xx < x1; xx++) {
            s_fb[yy * GAUGE_W + xx] = c;
        }
    }
}

static void fill_circle(int cx, int cy, int r, lv_color_t c)
{
    if(r <= 0) return;

    if(r >= 3) {
        lv_draw_rect_dsc_t dsc;
        lv_draw_rect_dsc_init(&dsc);
        dsc.bg_color = c;
        dsc.bg_opa = LV_OPA_COVER;
        dsc.border_width = 0;
        dsc.radius = r;
        lv_canvas_draw_rect(s_canvas, cx - r, cy - r, r * 2, r * 2, &dsc);
    }
    else {
        int y;
        int x;
        int r2 = r * r;
        for(y = -r; y <= r; y++) {
            int yy = cy + y;
            if((unsigned)yy >= GAUGE_H) continue;
            for(x = -r; x <= r; x++) {
                int xx = cx + x;
                if((unsigned)xx >= GAUGE_W) continue;
                if(x * x + y * y <= r2) s_fb[yy * GAUGE_W + xx] = c;
            }
        }
    }
}

static void fill_round_rect(int x, int y, int w, int h, int r, lv_color_t c)
{
    if(w <= 0 || h <= 0) return;
    if(r < 1) {
        fill_rect(x, y, w, h, c);
        return;
    }
    if(r * 2 > w) r = w / 2;
    if(r * 2 > h) r = h / 2;
    fill_rect(x + r, y, w - 2 * r, h, c);
    fill_rect(x, y + r, w, h - 2 * r, c);
    fill_circle(x + r, y + r, r, c);
    fill_circle(x + w - r - 1, y + r, r, c);
    fill_circle(x + r, y + h - r - 1, r, c);
    fill_circle(x + w - r - 1, y + h - r - 1, r, c);
}

static void round_rect_outline(int x, int y, int w, int h, int r, int t, lv_color_t c)
{
    fill_round_rect(x, y, w, h, r, c);
    fill_round_rect(x + t, y + t, w - 2 * t, h - 2 * t, r - t, c_black);
}

static void thick_line(int x0, int y0, int x1, int y1, int t, lv_color_t c)
{
    lv_draw_line_dsc_t dsc;
    lv_point_t pts[2];

    if(t < 1) t = 1;
    pts[0].x = x0;
    pts[0].y = y0;
    pts[1].x = x1;
    pts[1].y = y1;

    lv_draw_line_dsc_init(&dsc);
    dsc.color = c;
    dsc.width = t;
    dsc.opa = LV_OPA_COVER;
    dsc.round_start = 0;
    dsc.round_end = 0;
    dsc.raw_end = 1;
    lv_canvas_draw_line(s_canvas, pts, 2, &dsc);
}

static void rect_outline(int x, int y, int w, int h, int t, lv_color_t c)
{
    fill_rect(x, y, w, t, c);
    fill_rect(x, y + h - t, w, t, c);
    fill_rect(x, y, t, h, c);
    fill_rect(x + w - t, y, t, h, c);
}

static void fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, lv_color_t c)
{
    lv_draw_rect_dsc_t dsc;
    lv_point_t pts[3];

    pts[0].x = x0; pts[0].y = y0;
    pts[1].x = x1; pts[1].y = y1;
    pts[2].x = x2; pts[2].y = y2;

    lv_draw_rect_dsc_init(&dsc);
    dsc.bg_color = c;
    dsc.bg_opa = LV_OPA_COVER;
    dsc.border_width = 0;
    dsc.radius = 0;
    lv_canvas_draw_polygon(s_canvas, pts, 3, &dsc);
}

/* Generic convex/concave polygon fill, used for the cut-out panels. */
static void fill_polygon(const int *px, const int *py, int n, lv_color_t c)
{
    lv_draw_rect_dsc_t dsc;
    lv_point_t pts[16];
    int i;

    if(n < 3 || n > (int)(sizeof(pts) / sizeof(pts[0]))) return;
    for(i = 0; i < n; i++) {
        pts[i].x = px[i];
        pts[i].y = py[i];
    }

    lv_draw_rect_dsc_init(&dsc);
    dsc.bg_color = c;
    dsc.bg_opa = LV_OPA_COVER;
    dsc.border_width = 0;
    dsc.radius = 0;
    lv_canvas_draw_polygon(s_canvas, pts, n, &dsc);
}

static int angle_index(float deg)
{
    int i = (int)floorf(deg * 2.0f + 0.5f);
    i %= 720;
    if(i < 0) i += 720;
    return i;
}

static int angle_in_range(float a, float a0, float a1)
{
    while(a0 < 0.0f) {
        a0 += 360.0f;
        a1 += 360.0f;
    }
    while(a0 >= 360.0f) {
        a0 -= 360.0f;
        a1 -= 360.0f;
    }
    while(a < 0.0f) a += 360.0f;
    while(a >= 360.0f) a -= 360.0f;

    if(a1 >= 360.0f) return (a >= a0 || a <= (a1 - 360.0f));
    return (a >= a0 && a <= a1);
}

static int angle_in_range_i(int a, int a0, int a1)
{
    while(a0 < 0) {
        a0 += 3600;
        a1 += 3600;
    }
    while(a0 >= 3600) {
        a0 -= 3600;
        a1 -= 3600;
    }
    if(a1 >= 3600) return (a >= a0 || a <= (a1 - 3600));
    return (a >= a0 && a <= a1);
}

static void hud_arc_angles(float a0, float a1, int *start, int *end)
{
    float span = a1 - a0;
    if(span < 0.0f) {
        float tmp = a0;
        a0 = a1;
        a1 = tmp;
        span = -span;
    }
    if(span >= 359.9f) {
        *start = 0;
        *end = 360;
        return;
    }
    *start = (int)floorf(a0 + 0.5f);
    *end = (int)floorf(a1 + 0.5f);
    while(*start < 0) *start += 360;
    while(*start >= 360) *start -= 360;
    while(*end < 0) *end += 360;
    while(*end >= 360) *end -= 360;
    if(*end < *start) *end += 360;
}

static void draw_arc(int cx, int cy, int r, int t, float a0, float a1, lv_color_t c)
{
    lv_draw_arc_dsc_t dsc;
    float span = a1 - a0;
    int start;
    int end;

    if(span < 0.0f) {
        float tmp = a0;
        a0 = a1;
        a1 = tmp;
        span = -span;
    }
    if(span <= 0.0f) return;
    if(t < 1) t = 1;

    if(span >= 359.9f) {
        start = 0;
        end = 360;
    }
    else {
        /* Keep the HUD angle convention: 0 = right, 90 = down. */
        start = (int)floorf(a0 + 0.5f);
        end = (int)floorf(a1 + 0.5f);
        while(start < 0) start += 360;
        while(start >= 360) start -= 360;
        while(end < 0) end += 360;
        while(end >= 360) end -= 360;
        if(end < start) end += 360;
    }

    lv_draw_arc_dsc_init(&dsc);
    dsc.color = c;
    dsc.width = t;
    dsc.opa = LV_OPA_COVER;
    dsc.rounded = 0;
    /* LVGL draws the arc inward from the radius; shift it so the stroke
     * centre stays on the requested radius. */
    lv_canvas_draw_arc(s_canvas, cx, cy, r + t / 2,
                       start, end, &dsc);
}

static void draw_sector(int cx, int cy, int r, float a0, float a1, lv_color_t c)
{
    lv_draw_arc_dsc_t dsc;
    int start_angle;
    int end_angle;
    float span = a1 - a0;

    if(span < 0.0f) span = -span;
    if(span <= 0.0f || r <= 0) return;

    hud_arc_angles(a0, a1, &start_angle, &end_angle);
    lv_draw_arc_dsc_init(&dsc);
    dsc.color = c;
    dsc.width = r;
    dsc.opa = LV_OPA_COVER;
    dsc.rounded = 0;
    /* A full-width arc is a pie slice: inner radius 0, outer radius r. */
    lv_canvas_draw_arc(s_canvas, cx, cy, r,
                       start_angle, end_angle, &dsc);
}

static void fill_annular(int r_in, int r_out, float a0, float a1, int pattern, lv_color_t c)
{
    if(r_out <= r_in || r_out <= 0) return;

    if(pattern == 0) {
        lv_draw_arc_dsc_t dsc;
        int start_angle;
        int end_angle;
        float span = a1 - a0;

        if(span < 0.0f) span = -span;
        if(span <= 0.0f) return;

        hud_arc_angles(a0, a1, &start_angle, &end_angle);
        lv_draw_arc_dsc_init(&dsc);
        dsc.color = c;
        dsc.width = r_out - r_in;
        dsc.opa = LV_OPA_COVER;
        dsc.rounded = 0;
        lv_canvas_draw_arc(s_canvas, GAUGE_CX, GAUGE_CY, r_out,
                           start_angle, end_angle, &dsc);
        return;
    }

    /* Patterned bands are still custom because LVGL arcs have no hatch
     * pattern support. */
    {
        int y;
        int x;
        int r_in2 = r_in * r_in;
        int r_out2 = r_out * r_out;

        if(a1 < a0) {
            float tmp = a0;
            a0 = a1;
            a1 = tmp;
        }
        if(a1 - a0 <= 0.0f) return;

        for(y = GAUGE_CY - r_out; y <= GAUGE_CY + r_out; y++) {
            int dy = y - GAUGE_CY;
            if((unsigned)y >= GAUGE_H) continue;
            for(x = GAUGE_CX - r_out; x <= GAUGE_CX + r_out; x++) {
                int dx = x - GAUGE_CX;
                int d2;
                int on = -1;
                if((unsigned)x >= GAUGE_W) continue;
                d2 = dx * dx + dy * dy;
                if(d2 < r_in2 || d2 > r_out2) continue;
                if(!angle_in_range_i((int)s_angle_map[y * GAUGE_W + x],
                                     (int)(a0 * 10.0f + 0.5f),
                                     (int)(a1 * 10.0f + 0.5f))) continue;
                if(pattern == 1) on = (y % 2) == 0;
                else if(pattern == 2) on = ((x + y) % 3) == 0;
                else if(pattern == 3) on = ((x - y) % 3) == 0;
                else if(pattern == 4) on = (x % 3) == 0;
                if(on > 0) s_fb[y * GAUGE_W + x] = c;
            }
        }
    }
}

static void draw_outer_rings(void)
{
    draw_arc(GAUGE_CX, GAUGE_CY, 117, 2, 0, 360, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 114, 1, 0, 360, c_blue);
    draw_arc(GAUGE_CX, GAUGE_CY, 111, 1, 0, 360, c_white);
}

static void draw_radial(float angle, int r0, int r1, int t, lv_color_t c)
{
    int id = angle_index(angle);
    int x0 = GAUGE_CX + (r0 * s_cos[id]) / 4096;
    int y0 = GAUGE_CY + (r0 * s_sin[id]) / 4096;
    int x1 = GAUGE_CX + (r1 * s_cos[id]) / 4096;
    int y1 = GAUGE_CY + (r1 * s_sin[id]) / 4096;
    thick_line(x0, y0, x1, y1, t, c);
}

/* ------------------------------------------------------------------------- */
/* Label helpers                                                              */
/* ------------------------------------------------------------------------- */

static lv_obj_t *make_label(lv_obj_t *parent, const char *txt, const lv_font_t *font,
                            uint32_t color, int x, int y, int w, int h, lv_text_align_t align)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, w, h);
    lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
    lv_label_set_text(label, txt ? txt : "");
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(color), 0);
    lv_obj_set_style_text_align(label, align, 0);
    lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(label, 0, 0);
    lv_obj_set_style_pad_all(label, 0, 0);
    lv_obj_clear_flag(label, LV_OBJ_FLAG_SCROLLABLE);
    return label;
}

static void set_hidden(lv_obj_t *obj, int hidden)
{
    if(hidden) lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    else lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

/* Small seven-segment digits for the main speed readout.  The bundled segment
 * fonts are 40/48 px and are too large for the compact hub at 240x240. */
static void draw_seg_digit_sized(int x, int y, int w, int h, int t, int digit, lv_color_t c)
{
    static const uint8_t seg[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };
    uint8_t m;

    if(digit < 0 || digit > 9) return;
    if(w < 8 || h < 12 || t < 1) return;
    m = seg[digit];

    if(m & 0x01) fill_rect(x + t, y, w - 2 * t, t, c);                       /* a */
    if(m & 0x02) fill_rect(x + w - t, y + t, t, h / 2 - t - 1, c);           /* b */
    if(m & 0x04) fill_rect(x + w - t, y + h / 2 + 2, t, h / 2 - t - 2, c);   /* c */
    if(m & 0x08) fill_rect(x + t, y + h - t, w - 2 * t, t, c);               /* d */
    if(m & 0x10) fill_rect(x, y + h / 2 + 2, t, h / 2 - t - 2, c);           /* e */
    if(m & 0x20) fill_rect(x, y + t, t, h / 2 - t - 1, c);                   /* f */
    if(m & 0x40) fill_rect(x + t, y + h / 2 - t / 2, w - 2 * t, t, c);       /* g */
}

static void draw_speed_digits(int value)
{
    int d0;
    int d1;
    int d2;
    int x = 82;
    int y = 77;

    if(value < 0) value = 0;
    if(value > 999) value = 999;
    d0 = value / 100;
    d1 = (value / 10) % 10;
    d2 = value % 10;

    draw_seg_digit_sized(x, y, 18, 27, 3, d0, c_white);
    draw_seg_digit_sized(x + 26, y, 18, 27, 3, d1, c_white);
    draw_seg_digit_sized(x + 52, y, 18, 27, 3, d2, c_white);

    fill_rect(x - 12, y + 12, 9, 3, c_white);
    fill_rect(x + 74, y + 12, 9, 3, c_white);
}

static lv_obj_t *make_layer(void)
{
    lv_obj_t *layer = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(layer, 0, 0);
    lv_obj_set_size(layer, GAUGE_W, GAUGE_H);
    lv_obj_set_style_bg_opa(layer, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(layer, 0, 0);
    lv_obj_set_style_pad_all(layer, 0, 0);
    lv_obj_set_style_radius(layer, 0, 0);
    lv_obj_clear_flag(layer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(layer, LV_OBJ_FLAG_HIDDEN);
    return layer;
}

/* ------------------------------------------------------------------------- */
/* Boot screen                                                                */
/* ------------------------------------------------------------------------- */

static void draw_boot_grid(void)
{
    int i;
    int r2 = 109 * 109;

    for(i = 20; i < GAUGE_W; i += 20) {
        int y;
        int x;
        for(y = 0; y < GAUGE_H; y++) {
            int dy = y - GAUGE_CY;
            int dx = i - GAUGE_CX;
            if(dx * dx + dy * dy <= r2) put_px(i, y, c_grid);
        }
        for(x = 0; x < GAUGE_W; x++) {
            int dx = x - GAUGE_CX;
            int dy = i - GAUGE_CY;
            if(dx * dx + dy * dy <= r2) put_px(x, i, c_grid);
        }
    }
}

static void draw_boot_frame(uint32_t elapsed)
{
    float progress = (float)elapsed / 1200.0f;
    uint32_t t = elapsed;

    if(progress > 1.0f) progress = 1.0f;

    clear_fb(c_black);
    draw_boot_grid();

    draw_arc(GAUGE_CX, GAUGE_CY, 117, 2, 0, 360, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 114, 1, 0, 360, c_blue);
    draw_arc(GAUGE_CX, GAUGE_CY, 111, 1, 0, 360, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 116, 2, -90.0f, -90.0f + 360.0f * progress, c_white);

    if(t >= 500u) {
        int px[4] = {30, 210, 202, 38};
        int py[4] = {38, 38, 74, 74};
        fill_polygon(px, py, 4, c_white);
    }

    if(t >= 600u) {
        thick_line(26, 90, 214, 90, 1, c_blue);
    }

    if(t >= 2800u) {
        thick_line(48, 144, 192, 144, 1, c_white);
    }

    lv_obj_invalidate(s_canvas);
}

static void create_boot_layer(void)
{
    int i;
    static const char *left_text[5] = {
        "SYSTEM CHECK", "MACHINE CONDITION", "RETINA-CODE", "VOICE PRINT-CODE", "PHYSICAL CONDITION"
    };
    static const char *right_text[5] = {
        "...OK", "...GREEN", "...OK", "...OK", "...GREEN"
    };
    static const int rows[5] = { 92, 106, 160, 173, 186 };

    s_boot_layer = make_layer();

    s_boot_title = make_label(s_boot_layer, "ASURADA", &lv_font_montserrat_28,
                              0x000000, 30, 41, 180, 30, LV_TEXT_ALIGN_CENTER);
    s_boot_title_b = make_label(s_boot_layer, "ASURADA", &lv_font_montserrat_28,
                                0x000000, 31, 41, 180, 30, LV_TEXT_ALIGN_CENTER);
    s_boot_title_c = make_label(s_boot_layer, "ASURADA", &lv_font_montserrat_28,
                                0x000000, 30, 42, 180, 30, LV_TEXT_ALIGN_CENTER);
    s_boot_sub = make_label(s_boot_layer, "NAVIGATION-CYBERSYSTEM", &lv_font_montserrat_10,
                            0xFFD400, 18, 78, 204, 12, LV_TEXT_ALIGN_CENTER);

    for(i = 0; i < 5; i++) {
        s_boot_left[i] = make_label(s_boot_layer, left_text[i], &lv_font_montserrat_10,
                                    0xFFFFFF, 42, rows[i], 112, 12, LV_TEXT_ALIGN_LEFT);
        s_boot_right[i] = make_label(s_boot_layer, right_text[i], &lv_font_montserrat_10,
                                     0xFFFFFF, 128, rows[i], 80, 12, LV_TEXT_ALIGN_RIGHT);
        set_hidden(s_boot_left[i], 1);
        set_hidden(s_boot_right[i], 1);
    }

    s_boot_driver = make_label(s_boot_layer, "DRIVER-CHECK", &lv_font_montserrat_20,
                               0xFFFFFF, 28, 118, 184, 24, LV_TEXT_ALIGN_CENTER);
    s_boot_driver_b = make_label(s_boot_layer, "DRIVER-CHECK", &lv_font_montserrat_20,
                                 0xFFFFFF, 29, 118, 184, 24, LV_TEXT_ALIGN_CENTER);
    s_boot_master = make_label(s_boot_layer, "MASTER", &lv_font_montserrat_10,
                               0xFFFFFF, 50, 146, 140, 12, LV_TEXT_ALIGN_CENTER);
    s_boot_ready = make_label(s_boot_layer, "READY FOR START", &lv_font_montserrat_14,
                              0xFFFFFF, 18, 200, 204, 26, LV_TEXT_ALIGN_CENTER);
    s_boot_ready_b = make_label(s_boot_layer, "READY FOR START", &lv_font_montserrat_14,
                                0xFFFFFF, 19, 200, 204, 26, LV_TEXT_ALIGN_CENTER);

    set_hidden(s_boot_title, 1);
    set_hidden(s_boot_title_b, 1);
    set_hidden(s_boot_title_c, 1);
    set_hidden(s_boot_sub, 1);
    set_hidden(s_boot_driver, 1);
    set_hidden(s_boot_driver_b, 1);
    set_hidden(s_boot_master, 1);
    set_hidden(s_boot_ready, 1);
    set_hidden(s_boot_ready_b, 1);
}

static void render_boot(uint32_t elapsed)
{
    uint32_t t = elapsed;

    draw_boot_frame(elapsed);

    set_hidden(s_boot_title, t < 600u);
    set_hidden(s_boot_title_b, t < 600u);
    set_hidden(s_boot_title_c, t < 600u);
    set_hidden(s_boot_sub, t < 600u);
    set_hidden(s_boot_left[0], t < 1700u);
    set_hidden(s_boot_right[0], t < 1700u);
    set_hidden(s_boot_left[1], t < 1700u);
    set_hidden(s_boot_right[1], t < 1700u);
    set_hidden(s_boot_driver, t < 2800u);
    set_hidden(s_boot_driver_b, t < 2800u);
    set_hidden(s_boot_master, t < 2800u);
    set_hidden(s_boot_left[2], t < 3900u);
    set_hidden(s_boot_right[2], t < 3900u);
    set_hidden(s_boot_left[3], t < 3900u);
    set_hidden(s_boot_right[3], t < 3900u);
    set_hidden(s_boot_left[4], t < 3900u);
    set_hidden(s_boot_right[4], t < 3900u);
    set_hidden(s_boot_ready, t < 5100u);
    set_hidden(s_boot_ready_b, t < 5100u);
}

/* ------------------------------------------------------------------------- */
/* Main screen                                                                */
/* ------------------------------------------------------------------------- */

/* The outer scale is a compact dial on the left/top/right, not a full ring.
 * The reference spacing widens toward the top of the dial, hence the table. */
static const float main_scale_deg[13] = {
    153.0f, 173.0f, 186.0f, 198.0f, 208.0f, 220.0f, 232.0f,
    244.0f, 258.0f, 271.0f, 283.0f, 297.0f, 312.0f
};

static float main_scale_angle(float value)
{
    int i;
    float frac;

    if(value <= 5.0f) return main_scale_deg[0] + (value - 5.0f) * 7.0f;
    if(value >= 17.0f) return main_scale_deg[12] + (value - 17.0f) * 15.0f;
    i = (int)floorf(value) - 5;
    frac = value - floorf(value);
    return main_scale_deg[i] + frac * (main_scale_deg[i + 1] - main_scale_deg[i]);
}

/* The reference dial does not keep its numerals on one radius.  Pulling the
 * low numbers inward and pushing 13..17 to the rim gives the same compact,
 * tightly-packed composition as the video. */
static const int main_label_r[13] = {
    69, 79, 76, 86, 93, 89, 93, 97, 102, 103, 105, 108, 103
};

static float main_label_radius(float value)
{
    int i = (int)(value + 0.5f);
    if(i < 5) i = 5;
    if(i > 17) i = 17;
    return (float)main_label_r[i - 5];
}

static void gear_pos(int i, int *x, int *y)
{
    *x = 172 - i * 2;
    *y = 145 + i * 9;
}

static void draw_main_bands(void)
{
    fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(5.0f),  main_scale_angle(10.5f), 1, c_band_blue);
    fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(10.5f), main_scale_angle(12.5f), 2, c_band_yellow);
    fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(12.5f), main_scale_angle(15.5f), 3, c_band_red);
    fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(15.5f), main_scale_angle(17.5f), 4, c_band_magenta);

    /* brighter cyan on the low end, as in the reference */
    fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(5.0f), main_scale_angle(6.2f), 0, c_cyan);
}

static void draw_main_ticks(void)
{
    int v;
    for(v = 5; v <= 17; v++) {
        float a = main_scale_angle((float)v);
        draw_radial(a, 104, 111, 1, c_white);

        if(v < 17) {
            float am = main_scale_angle((float)v + 0.5f);
            draw_radial(am, 107, 111, 1, c_white);
        }
    }
}

static void draw_main_separators(void)
{
    draw_radial(main_scale_angle(15.0f), MAIN_R_IN, 110, 1, c_white);
    draw_radial(main_scale_angle(16.0f), MAIN_R_IN, 110, 1, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 109, 1,
             main_scale_angle(15.0f), main_scale_angle(17.0f), c_white);
}

static void draw_main_capsule(void)
{
    fill_round_rect(104, 106, 32, 28, 6, c_dark);
    fill_round_rect(106, 108, 28, 24, 5, c_orange);
    fill_rect(117, 108, 6, 24, c_green);
    fill_circle(105, 120, 3, c_red);
    fill_circle(135, 120, 3, c_red);
    fill_circle(105, 120, 1, c_white);
    fill_circle(135, 120, 1, c_white);
}

static void draw_main_hub(void)
{
    int i;

    fill_circle(GAUGE_CX, GAUGE_CY, 57, c_black);
    draw_sector(GAUGE_CX, GAUGE_CY, 56, 90.0f, 180.0f, c_green);
    draw_arc(GAUGE_CX, GAUGE_CY, 57, 3, 0, 360, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 50, 1, 105.0f, 168.0f, c_orange);
    for(i = 0; i < 4; i++) {
        draw_radial(112.0f + (float)i * 16.0f, 36, 47, 1, c_orange);
    }

    /* Quadrant dividers. */
    thick_line(64, 120, 176, 120, 1, c_white);
    thick_line(120, 120, 120, 176, 1, c_white);

    /* Speed side dashes. */
    fill_rect(74, 91, 8, 1, c_white);
    fill_rect(158, 91, 8, 1, c_white);
    fill_rect(70, 105, 6, 1, c_white);
    fill_rect(164, 105, 6, 1, c_white);

    /* Radial fan lines on the right side of the hub. */
    for(i = 0; i < 5; i++) {
        float a = -18.0f - (float)i * 11.0f;
        int id = angle_index(a);
        int x1 = GAUGE_CX + (24 * s_cos[id]) / 4096;
        int y1 = GAUGE_CY + (24 * s_sin[id]) / 4096;
        int x2 = GAUGE_CX + (52 * s_cos[id]) / 4096;
        int y2 = GAUGE_CY + (52 * s_sin[id]) / 4096;
        thick_line(x1, y1, x2, y2, 1, c_white);
    }

    /* White segment marks around the lower-right of the hub. */
    draw_arc(GAUGE_CX, GAUGE_CY, 48, 3, 18.0f, 34.0f, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 48, 3, 45.0f, 61.0f, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 48, 3, 72.0f, 86.0f, c_white);

    draw_main_capsule();
}

static void draw_main_icons(void)
{
    int i;

    /* Three-bar flag on the upper right. */
    thick_line(149, 105, 205, 90, 6, c_orange);
    thick_line(149, 96, 205, 81, 6, c_green);
    thick_line(149, 87, 205, 72, 5, c_orange);
    fill_circle(180, 66, 4, c_green);

    /* Oil/service gauge, lower left. */
    fill_circle(68, 183, 17, c_dark_green);
    draw_arc(68, 183, 17, 2, 0, 360, c_white);
    draw_arc(68, 183, 14, 4, 96, 264, c_green);
    fill_round_rect(56, 177, 24, 12, 2, c_black);
    fill_round_rect(58, 179, 20, 8, 1, c_green);
    fill_rect(54, 177, 2, 12, c_white);
    fill_rect(81, 177, 2, 12, c_white);
    thick_line(63, 172, 63, 176, 1, c_white);
    thick_line(73, 172, 73, 176, 1, c_white);

    /* Orange service lights. */
    for(i = 0; i < 4; i++) {
        int x = (i < 2) ? (86 + i * 20) : 87;
        int y = (i < 2) ? 169 : (191 + (i - 2) * 16);
        fill_circle(x, y, 7, c_orange);
        draw_arc(x, y, 7, 1, 0, 360, c_white);
        thick_line(x - 6, y, x + 6, y, 1, c_black);
    }
    thick_line(91, 160, 101, 160, 1, c_green);
    thick_line(91, 178, 101, 178, 1, c_green);
    thick_line(94, 169, 98, 169, 2, c_green);
    thick_line(93, 184, 93, 197, 1, c_green);
    thick_line(91, 199, 91, 213, 1, c_green);

    /* A/C/R warning cluster: three inset red facets separated by black seams. */
    {
        int ax[4] = {100, 119, 115, 103};
        int ay[4] = {174, 174, 190, 190};
        int cx[4] = {123, 148, 143, 127};
        int cy[4] = {174, 174, 190, 190};
        int rx[5] = {104, 141, 132, 121, 110};
        int ry[5] = {194, 194, 207, 212, 207};

        fill_polygon(ax, ay, 4, c_red_deep);
        fill_polygon(cx, cy, 4, c_red_deep);
        fill_polygon(rx, ry, 5, c_red_deep);

        thick_line(100, 174, 119, 174, 1, c_red);
        thick_line(123, 174, 148, 174, 1, c_red);
        thick_line(104, 194, 141, 194, 1, c_red);
    }
    thick_line(120, 188, 120, 205, 1, c_black);

    /* Gear ladder, lower right. */
    for(i = 0; i < 8; i++) {
        int x;
        int y;
        gear_pos(i, &x, &y);
        fill_round_rect(x - 7, y - 5, 15, 11, 2, c_gray);
        fill_round_rect(x - 6, y - 4, 13, 9, 1, c_dark);
    }

    /* Green direction indicator and yellow baseline. */
    fill_triangle(141, 198, 151, 198, 146, 191, c_green);
    fill_triangle(141, 207, 151, 207, 146, 214, c_green);
    thick_line(136, 202, 156, 202, 1, c_green);
    thick_line(132, 216, 162, 216, 2, c_yellow);

    /* Bottom battery / stack bar. */
    fill_round_rect(95, 215, 50, 12, 2, c_white);
    fill_round_rect(96, 216, 48, 10, 2, c_teal);
    for(i = 0; i < 5; i++) {
        thick_line(101 + i * 8, 217, 101 + i * 8, 224, 1, c_white);
    }
    fill_rect(116, 227, 8, 2, c_white);

    /* Small warning marks near the lower-right hub. */
    draw_arc(GAUGE_CX, GAUGE_CY, 51, 2, 10, 16, c_white);
    draw_arc(GAUGE_CX, GAUGE_CY, 51, 2, 24, 30, c_white);
}

static void build_main_bg(void)
{
    clear_fb(c_black);

    draw_main_bands();
    draw_main_ticks();
    draw_main_separators();
    draw_main_hub();
    draw_main_icons();
    draw_outer_rings();

    memcpy(s_main_bg, s_fb, GAUGE_W * GAUGE_H * sizeof(lv_color_t));
}

static void create_main_layer(void)
{
    int i;

    s_main_layer = make_layer();

    for(i = 0; i < 13; i++) {
        int v = 5 + i;
        float a = main_scale_angle((float)v);
        int id = angle_index(a);
        int rr = (int)(main_label_radius((float)v) + 0.5f);
        int x = GAUGE_CX + (rr * s_cos[id]) / 4096;
        int y = GAUGE_CY + (rr * s_sin[id]) / 4096;
        s_outer_label[i] = make_label(s_main_layer, "", &lv_font_montserrat_18,
                                      0xFFFFFF, x - 13, y - 10, 26, 20, LV_TEXT_ALIGN_CENTER);
        lv_obj_set_style_text_letter_space(s_outer_label[i], -1, 0);
        lv_label_set_text_fmt(s_outer_label[i], "%d", v);
    }

    s_oil_label = make_label(s_main_layer, "OIL", &lv_font_montserrat_8,
                             0x001400, 82, 142, 28, 10, LV_TEXT_ALIGN_CENTER);
    s_stack_label = make_label(s_main_layer, "STACK", &lv_font_montserrat_8,
                               0xFF3B30, 126, 145, 38, 10, LV_TEXT_ALIGN_CENTER);

    s_acr_label[0] = make_label(s_main_layer, "A", &lv_font_montserrat_12,
                                0x300000, 101, 176, 14, 14, LV_TEXT_ALIGN_CENTER);
    s_acr_label[1] = make_label(s_main_layer, "C", &lv_font_montserrat_12,
                                0x300000, 125, 176, 14, 14, LV_TEXT_ALIGN_CENTER);
    s_acr_label[2] = make_label(s_main_layer, "R", &lv_font_montserrat_12,
                                0x300000, 114, 193, 14, 14, LV_TEXT_ALIGN_CENTER);

    for(i = 0; i < 8; i++) {
        static const char *gear_txt[8] = { "6", "5", "4", "3", "2", "1", "N", "R" };
        int x;
        int y;
        gear_pos(i, &x, &y);
        s_gear_label[i] = make_label(s_main_layer, gear_txt[i], &lv_font_montserrat_8,
                                     0xFFFFFF, x - 7, y - 5, 14, 10, LV_TEXT_ALIGN_CENTER);
    }
}

static void mask_main_bands(float speed)
{
    if(speed < 20.0f) {
        fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(6.0f),
                     main_scale_angle(17.5f), 0, c_black);
    }
    else if(speed < 100.0f) {
        fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(10.5f),
                     main_scale_angle(17.5f), 0, c_black);
    }
    else if(speed < 330.0f) {
        fill_annular(MAIN_R_IN, MAIN_R_OUT, main_scale_angle(15.5f),
                     main_scale_angle(17.5f), 0, c_black);
    }
}

static float ease_out_cubic(float t)
{
    float u = 1.0f - t;
    return 1.0f - u * u * u;
}

static void render_main(uint32_t elapsed)
{
    float t = (float)elapsed / 1000.0f;
    float speed;
    float px;
    float a_end;
    int gear;
    int active;

    memcpy(s_fb, s_main_bg, GAUGE_W * GAUGE_H * sizeof(lv_color_t));

    if(t < 6.0f) speed = 576.0f * ease_out_cubic(t / 6.0f);
    else speed = 576.0f;

    mask_main_bands(speed);

    px = speed / 576.0f;
    if(px > 1.0f) px = 1.0f;
    if(speed > 1.0f) {
        a_end = main_scale_angle(5.0f + 12.0f * powf(px, 0.70f));
        draw_arc(GAUGE_CX, GAUGE_CY, 62, 2,
                 main_scale_angle(5.0f), a_end, c_orange);
    }

    /* Active gear cell. */
    gear = 1 + (int)(speed / 100.0f);
    if(gear > 6) gear = 6;
    active = 6 - gear;
    if(speed < 15.0f) active = 6;
    {
        int x;
        int y;
        gear_pos(active, &x, &y);
        fill_round_rect(x - 6, y - 4, 13, 9, 2, c_red);
    }

    draw_speed_digits((int)(speed + 0.5f));
    lv_obj_invalidate(s_canvas);
}

/* ------------------------------------------------------------------------- */
/* Boost screen                                                               */
/* ------------------------------------------------------------------------- */

static void draw_boost_panel(void)
{
    int px[8];
    int py[8];

    /* All cut-out coordinates are expressed directly from the gauge centre. */
    px[0] = GAUGE_CX + 21; py[0] = GAUGE_CY - 40;
    px[1] = GAUGE_CX + 94; py[1] = GAUGE_CY - 40;
    px[2] = GAUGE_CX + 106; py[2] = GAUGE_CY - 27;
    px[3] = GAUGE_CX + 106; py[3] = GAUGE_CY + 20;
    px[4] = GAUGE_CX + 94; py[4] = GAUGE_CY + 30;
    px[5] = GAUGE_CX + 11; py[5] = GAUGE_CY + 30;
    px[6] = GAUGE_CX + 6;  py[6] = GAUGE_CY + 13;
    px[7] = GAUGE_CX + 5;  py[7] = GAUGE_CY - 22;
    fill_polygon(px, py, 8, c_black);
}

static void draw_boost_bracket(void)
{
    // Boost 倒计时数字上方横线
    thick_line(GAUGE_CX + 18, GAUGE_CY - 40,GAUGE_CX + 69, GAUGE_CY - 40, 3, c_boost_yellow);
    thick_line(GAUGE_CX + 17, GAUGE_CY - 38,GAUGE_CX + 25, GAUGE_CY - 38, 3, c_boost_yellow);
    thick_line(GAUGE_CX + 16, GAUGE_CY - 36,GAUGE_CX + 24, GAUGE_CY - 36, 3, c_boost_yellow);

    // Boost 倒计时下方横线
    thick_line(GAUGE_CX + 6, GAUGE_CY + 13,GAUGE_CX + 35, GAUGE_CY + 13, 4, c_boost_yellow);
    thick_line(GAUGE_CX + 22, GAUGE_CY + 17,GAUGE_CX + 35, GAUGE_CY + 17, 3, c_boost_yellow);
    thick_line(GAUGE_CX + 20, GAUGE_CY + 15,GAUGE_CX + 35, GAUGE_CY + 15, 3, c_boost_yellow);


    // 长斜线
    thick_line(GAUGE_CX + 6, GAUGE_CY + 13,GAUGE_CX + 29, GAUGE_CY + 101, 4, c_boost_yellow);
    //SEC 右侧长横线
    thick_line(GAUGE_CX + 72, GAUGE_CY + 15,GAUGE_CX + 106, GAUGE_CY + 15, 4, c_boost_yellow);

    //SEC 右侧扇形
    {
        int px[6];
        int py[6];
        px[0] = GAUGE_CX + 68;  py[0] = GAUGE_CY + 19;
        px[1] = GAUGE_CX + 106; py[1] = GAUGE_CY + 19;
        px[2] = GAUGE_CX + 106; py[2] = GAUGE_CY + 25;
        px[3] = GAUGE_CX + 103; py[3] = GAUGE_CY + 37;
        px[4] = GAUGE_CX + 100; py[4] = GAUGE_CY + 37;
        px[5] = GAUGE_CX + 70;  py[5] = GAUGE_CY + 25;
        fill_polygon(px, py, 6, c_boost_yellow);
    }

    /* Small yellow lip with a black slit at the lower end. */
    {
        int tx[5];
        int ty[5];
        tx[0] = GAUGE_CX + 94;  ty[0] = GAUGE_CY + 39;
        tx[1] = GAUGE_CX + 101; ty[1] = GAUGE_CY + 39;
        tx[2] = GAUGE_CX + 101; ty[2] = GAUGE_CY + 42;
        tx[3] = GAUGE_CX + 99;  ty[3] = GAUGE_CY + 43;
        tx[4] = GAUGE_CX + 94;  ty[4] = GAUGE_CY + 42;
        fill_polygon(tx, ty, 5, c_boost_yellow);
        fill_rect(GAUGE_CX + 96, GAUGE_CY + 39, 3, 1, c_black);
    }

    // 外侧圆弧
    draw_arc(GAUGE_CX, GAUGE_CY, 108, 6, -45.0f, 75.0f, c_boost_yellow);

}

static void draw_boost_recovery(void)
{
    static const float a0s[5] = {25.0f, 31.5f, 41.0f, 51.0f, 60.5f};
    static const float a1s[5] = {29.5f, 39.0f, 49.0f, 58.5f, 70.5f};
    int i;

    /* Five recovery bars matching the reference angular spacing. */
    for(i = 0; i < 5; i++) {
        fill_annular(74, 104, a0s[i], a1s[i], 0, c_boost_red);
    }
}

static void render_boost(uint32_t elapsed)
{
    float remain = 1.0f - (float)elapsed / (float)BOOST_MS;
    float progress;
    float red_start;
    float red_end;
    float green_span;
    float center_a0;
    float center_a1;
    int centis;
    int secs;
    int hundredths;
    int i;

    if(remain < 0.0f) remain = 0.0f;
    if(remain > 1.0f) remain = 1.0f;
    progress = 1.0f - remain;

    clear_fb(c_black);

    /* Faint unlit spokes remain visible through the whole dial, as in the
     * video.  The red fan only covers the sector that is still active. */
    for(i = 0; i < 24; i++) {
        draw_radial(-90.0f + (float)i * 15.0f, BOOST_HUB_R, 111, 1, c_spoke);
    }

    /* The lit fan grows from the fixed 72 degree edge towards the top-right.
     * Its angular extent follows the remaining seconds, not a straight
     * remain-to-angle interpolation. */
    red_start = 75.5f;
    red_end = 4.0f + 288.0f * remain;
    if(red_end > red_start) {
        fill_annular(BOOST_HUB_R, 111, red_start, red_end, 0, c_boost_red);
        for(i = 0; i < 24; i++) {
            float a = -90.0f + (float)i * 15.0f;
            while(a < 0.0f) a += 360.0f;
            while(a >= 360.0f) a -= 360.0f;
            if(a > red_start && a < red_end) {
                draw_radial(a, BOOST_HUB_R, 111, 2, c_black);
            }
        }
    }

    draw_boost_recovery();
    draw_boost_panel();

    /* Green recovery wedge grows from the right side and overlays the black
     * countdown cut-out.  Keep the integer readout on the black part of the
     * cut-out, as in the reference; the hundredths sit over the green. */
    green_span = 60.0f * progress - 1.0f;
    if(green_span < 0.0f) green_span = 0.0f;
    if(green_span > 34.0f) green_span = 34.0f;
    draw_sector(GAUGE_CX, GAUGE_CY, 104, 6.0f - green_span,
                6.0f, c_boost_green);
    /* The digit block keeps a black backing, while the green sector stays
     * visible above it, below it and beside the fraction, as in the video. */
    fill_rect(GAUGE_CX + 19, GAUGE_CY - 29, 48, 36, c_black);
    /* The green wedge is clipped at the lower panel edge.  Restore the
     * black lower cut-out and its lower recovery bars underneath it. */
    fill_rect(GAUGE_CX + 21, GAUGE_CY + 10, 85, 20, c_black);
    draw_boost_recovery();
    fill_circle(GAUGE_CX, GAUGE_CY, BOOST_HUB_R, c_black);

    /* The green core is a pie chart: it starts at 45 degrees and sweeps
     * counter-clockwise with elapsed boost time, as in the video. */
    center_a0 = 45.0f + 45.0f * progress;
    center_a1 = 45.0f + 360.0f * progress;
    if(center_a1 > center_a0 + 0.1f) {
        draw_sector(GAUGE_CX, GAUGE_CY, 14, center_a0, center_a1,
                    c_boost_green);
    }

    /* A short red leading segment sits just above the green wedge near the
     * end of the countdown, as in the video. */
    if(progress > 0.55f) {
        fill_annular(71, 100, -33.0f, -29.3f, 0, c_boost_red);
    }

    /* One continuous outer yellow band: from the upper-right tip, down the
     * right side, and around to the bottom of the recovery cut-out. */
    draw_boost_bracket();


    draw_outer_rings();

    centis = (int)(remain * BOOST_DISPLAY_SEC * 100.0f + 0.5f);
    secs = centis / 100;
    hundredths = centis % 100;

    lv_label_set_text_fmt(s_boost_frac, ".%02d", hundredths);

    draw_seg_digit_sized(GAUGE_CX + 21, GAUGE_CY - 27, 20, 34, 4, secs / 10, c_white);
    draw_seg_digit_sized(GAUGE_CX + 45, GAUGE_CY - 27, 20, 34, 4, secs % 10, c_white);
    lv_obj_set_pos(s_boost_frac, GAUGE_CX + 66, GAUGE_CY - 8);
    lv_obj_set_pos(s_boost_sec, GAUGE_CX + 28, GAUGE_CY + 11);

    lv_obj_invalidate(s_canvas);
}

static void create_boost_layer(void)
{
    s_boost_layer = make_layer();
    s_boost_frac = make_label(s_boost_layer, ".00", &lv_font_montserrat_14,
                              0xFFFFFF, GAUGE_CX + 30, GAUGE_CY - 16,
                              34, 16, LV_TEXT_ALIGN_LEFT);
    s_boost_sec = make_label(s_boost_layer, "SEC.", &lv_font_montserrat_14,
                             0xFFFFFF, GAUGE_CX, GAUGE_CY + 11,
                             46, 16, LV_TEXT_ALIGN_CENTER);
}

/* ------------------------------------------------------------------------- */
/* Spiral screen                                                              */
/* ------------------------------------------------------------------------- */

static void draw_spiral_holes(void)
{
    int i;
    for(i = 0; i < 18; i++) {
        float a = -90.0f + (float)i * 20.0f;
        int id = angle_index(a);
        int x = GAUGE_CX + (90 * s_cos[id]) / 4096;
        int y = GAUGE_CY + (90 * s_sin[id]) / 4096;
        fill_circle(x, y, 11, c_black);
        draw_arc(x, y, 11, 1, 0, 360, c_blue);
        fill_circle(x, y, 8, c_black);
    }
}

static void draw_spiral_small_triangles(void)
{
    int i;
    for(i = 0; i < 18; i++) {
        float a = -90.0f + (float)i * 20.0f + 10.0f;
        int id = angle_index(a);
        int id1 = angle_index(a - 2.5f);
        int id2 = angle_index(a + 2.5f);
        int x0 = GAUGE_CX + (102 * s_cos[id]) / 4096;
        int y0 = GAUGE_CY + (102 * s_sin[id]) / 4096;
        int x1 = GAUGE_CX + (96 * s_cos[id1]) / 4096;
        int y1 = GAUGE_CY + (96 * s_sin[id1]) / 4096;
        int x2 = GAUGE_CX + (96 * s_cos[id2]) / 4096;
        int y2 = GAUGE_CY + (96 * s_sin[id2]) / 4096;
        fill_triangle(x0, y0, x1, y1, x2, y2, c_blue);
    }
}

static void draw_spiral_big_triangles(void)
{
    int i;
    for(i = 0; i < 4; i++) {
        float a = (float)i * 90.0f;
        int id = angle_index(a);
        int id1 = angle_index(a - 10.0f);
        int id2 = angle_index(a + 10.0f);
        int x0 = GAUGE_CX + (102 * s_cos[id]) / 4096;
        int y0 = GAUGE_CY + (102 * s_sin[id]) / 4096;
        int x1 = GAUGE_CX + (82 * s_cos[id1]) / 4096;
        int y1 = GAUGE_CY + (82 * s_sin[id1]) / 4096;
        int x2 = GAUGE_CX + (82 * s_cos[id2]) / 4096;
        int y2 = GAUGE_CY + (82 * s_sin[id2]) / 4096;
        fill_triangle(x0, y0, x1, y1, x2, y2, c_blue);
    }
}

static void draw_spiral_inner(void)
{
    int i;

    draw_arc(GAUGE_CX, GAUGE_CY, 66, 3, 0, 360, c_yellow);
    draw_arc(GAUGE_CX, GAUGE_CY, 57, 11, 0, 360, c_green);

    for(i = 0; i < 16; i++) {
        draw_radial(-90.0f + (float)i * 22.5f, 51, 63, 2, c_black);
    }

    /* Blue STOP wedge on the lower-right of the segmented ring. */
    draw_arc(GAUGE_CX, GAUGE_CY, 57, 11, 12.0f, 82.0f, c_blue);

    fill_circle(GAUGE_CX, GAUGE_CY, 36, c_black);
    draw_arc(GAUGE_CX, GAUGE_CY, 36, 1, 0, 360, c_gray);
}

static void render_spiral(uint32_t elapsed)
{
    float rot = fmodf(270.0f + (float)elapsed * 45.0f / 1000.0f, 360.0f);
    int count = 6 - (int)(elapsed / 1000u);
    if(count < 0) count = 0;

    clear_fb(c_black);

    draw_sector(GAUGE_CX, GAUGE_CY, 101, rot, rot + 90.0f, c_orange);
    draw_sector(GAUGE_CX, GAUGE_CY, 101, rot + 180.0f, rot + 270.0f, c_orange);

    draw_spiral_holes();
    draw_arc(GAUGE_CX, GAUGE_CY, 102, 3, 0, 360, c_black);
    draw_arc(GAUGE_CX, GAUGE_CY, 106, 7, 0, 360, c_yellow);
    draw_spiral_small_triangles();
    draw_spiral_big_triangles();

    draw_outer_rings();

    draw_spiral_inner();

    draw_seg_digit_sized(111, 104, 18, 32, 3, count, c_white);
    lv_obj_invalidate(s_canvas);
}

static void create_spiral_layer(void)
{
    s_spiral_layer = make_layer();
    s_stop_label = make_label(s_spiral_layer, "STOP", &lv_font_montserrat_8,
                              0xFFFFFF, 138, 148, 38, 10, LV_TEXT_ALIGN_CENTER);
}

/* ------------------------------------------------------------------------- */
/* State machine                                                              */
/* ------------------------------------------------------------------------- */

static void set_mode(gauge_mode_t mode)
{
    int i;
    s_mode = mode;
    s_mode_start = lv_tick_get();

    set_hidden(s_main_layer, 1);
    set_hidden(s_boot_layer, 1);
    set_hidden(s_boost_layer, 1);
    set_hidden(s_spiral_layer, 1);

    if(mode == MODE_BOOT) 
    {
        set_hidden(s_boot_layer, 0);
        set_hidden(s_boot_title, 1);
        set_hidden(s_boot_title_b, 1);
        set_hidden(s_boot_title_c, 1);
        set_hidden(s_boot_sub, 1);
        set_hidden(s_boot_driver, 1);
        set_hidden(s_boot_driver_b, 1);
        set_hidden(s_boot_master, 1);
        set_hidden(s_boot_ready, 1);
        set_hidden(s_boot_ready_b, 1);
        for(i = 0; i < 5; i++) 
        {
            set_hidden(s_boot_left[i], 1);
            set_hidden(s_boot_right[i], 1);
        }
    }
    else if(mode == MODE_MAIN) 
    {
        set_hidden(s_main_layer, 0);
    }
    else if(mode == MODE_BOOST) 
    {
        set_hidden(s_boost_layer, 0);
    }
    else if(mode == MODE_SPIRAL) 
    {
        set_hidden(s_spiral_layer, 0);
    }
}

static void gauge_timer_cb(lv_timer_t *timer)
{
    uint32_t elapsed;
    (void)timer;

    elapsed = lv_tick_elaps(s_mode_start);

    switch(s_mode) {
        case MODE_BOOT:
            render_boot(elapsed);
            if(elapsed >= BOOT_MS) {
                s_main_next = MODE_BOOST;
                set_mode(MODE_MAIN);
            }
            break;

        case MODE_MAIN:
            render_main(elapsed);
            if(elapsed >= MAIN_MS) {
                set_mode(s_main_next);
            }
            break;

        case MODE_BOOST:
            render_boost(elapsed);
            if(elapsed >= BOOST_MS) {
                s_main_next = MODE_SPIRAL;
                set_mode(MODE_MAIN);
            }
            break;

        case MODE_SPIRAL:
            render_spiral(elapsed);
            if(elapsed >= SPIRAL_MS) {
                s_main_next = MODE_BOOST;
                set_mode(MODE_MAIN);
            }
            break;

        default:
            break;
    }
}

void Gauge_TriggerBoost(void)
{
    s_main_next = MODE_SPIRAL;
    set_mode(MODE_BOOST);
}

void Gauge_TriggerSpiral(void)
{
    s_main_next = MODE_BOOST;
    set_mode(MODE_SPIRAL);
}

/* ------------------------------------------------------------------------- */
/* Initialization                                                             */
/* ------------------------------------------------------------------------- */

void Gauge_Init(void)
{
    int i;
    lv_obj_t *screen;

    for(i = 0; i < 720; i++) 
    {
        float a = (float)i * 0.5f * GAUGE_PI / 180.0f;
        s_sin[i] = (int16_t)(sinf(a) * 4096.0f);
        s_cos[i] = (int16_t)(cosf(a) * 4096.0f);
    }

    c_black      = lv_color_hex(0x000000);
    c_white      = lv_color_hex(0xFFFFFF);
    c_blue       = lv_color_hex(0x1038F0);
    c_cyan       = lv_color_hex(0x00A8E0);
    c_orange     = lv_color_hex(0xFF5A00);
    c_red        = lv_color_hex(0xF00000);
    c_yellow     = lv_color_hex(0xFFD400);
    c_green      = lv_color_hex(0x00B050);
    c_dark_green = lv_color_hex(0x007038);
    c_magenta    = lv_color_hex(0xC00060);
    c_gray       = lv_color_hex(0x8A8A8A);
    c_dark       = lv_color_hex(0x202020);
    c_grid       = lv_color_hex(0x242424);
    c_teal       = lv_color_hex(0x00B8B0);
    c_band_blue    = lv_color_hex(0x007FB8);
    c_band_yellow  = lv_color_hex(0xC8A000);
    c_band_red     = lv_color_hex(0xB00000);
    c_band_magenta = lv_color_hex(0x900048);
    c_red_deep     = lv_color_hex(0x9E0000);
    c_boost_yellow = lv_color_hex(0xFFF800);
    c_boost_green  = lv_color_hex(0x00E838);
    c_boost_red    = lv_color_hex(0xE80000);
    c_spoke        = lv_color_hex(0x1F1F1F);

    s_fb = (lv_color_t *)GAUGE_MALLOC(GAUGE_W * GAUGE_H * sizeof(lv_color_t));
    s_main_bg = (lv_color_t *)GAUGE_MALLOC(GAUGE_W * GAUGE_H * sizeof(lv_color_t));
    s_angle_map = (uint16_t *)GAUGE_MALLOC(GAUGE_W * GAUGE_H * sizeof(uint16_t));
    if(s_fb == NULL || s_main_bg == NULL || s_angle_map == NULL) 
    {
        LV_LOG_ERROR("Gauge: framebuffer allocation failed");
        return;
    }

    for(i = 0; i < GAUGE_H; i++) 
    {
        int x;
        for(x = 0; x < GAUGE_W; x++) 
        {
            float a = atan2f((float)(i - GAUGE_CY), (float)(x - GAUGE_CX)) * 57.29577951308232f;
            int ai;
            if(a < 0.0f) a += 360.0f;
            ai = (int)(a * 10.0f + 0.5f) % 3600;
            s_angle_map[i * GAUGE_W + x] = (uint16_t)ai;
        }
    }

    screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, c_black, 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(screen, 0, 0);

    s_canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(s_canvas, s_fb, GAUGE_W, GAUGE_H, LV_IMG_CF_TRUE_COLOR);
    lv_obj_set_pos(s_canvas, 0, 0);
    lv_obj_set_size(s_canvas, GAUGE_W, GAUGE_H);
    lv_obj_set_style_bg_opa(s_canvas, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(s_canvas, 0, 0);
    lv_obj_set_style_pad_all(s_canvas, 0, 0);
    lv_obj_set_style_radius(s_canvas, 0, 0);
    lv_obj_clear_flag(s_canvas, LV_OBJ_FLAG_SCROLLABLE);

    create_main_layer();
    create_boot_layer();
    create_boost_layer();
    create_spiral_layer();

    build_main_bg();
    clear_fb(c_black);
    set_mode(MODE_BOOT);

    lv_timer_create(gauge_timer_cb, 30, NULL);
}
