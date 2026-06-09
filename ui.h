#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

// Initialize the basic UI layout
void ui_init(void);

// Update the list of events shown on the screen
// We pass arrays since this might be called from C++ but compiled as C
void ui_update_events(const char** titles, unsigned long* times, const char** types, int count);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // UI_H
