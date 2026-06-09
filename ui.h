#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

// Initialize the basic UI layout
void ui_init(void);

// Update the list of events shown on the screen
void ui_update_events(const char** titles, unsigned long* times, const char** types, int count);

// Show the Alarm Popup
void ui_show_alarm(const char* title);

// Hide the Alarm Popup
void ui_hide_alarm(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // UI_H
