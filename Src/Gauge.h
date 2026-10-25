#ifndef GAUGE_H
#define GAUGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Cyber Formula / Asurada style round HUD for the LVGL-PC simulator.
 *
 * The UI is drawn into a 240x240 LVGL canvas so the same source can later be
 * moved to the ESP32-S3 + GC9A01 project.  Only LVGL 8.x APIs are used.
 */
void Gauge_Init(void);

/* Optional manual triggers; the demo loop calls these internally. */
void Gauge_TriggerBoost(void);
void Gauge_TriggerSpiral(void);

#ifdef __cplusplus
}
#endif

#endif /* GAUGE_H */
