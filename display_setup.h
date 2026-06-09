#ifndef DISPLAY_SETUP_H
#define DISPLAY_SETUP_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>

// Initializes the SH8601 display and FT3168 touch controller.
// Also initializes LVGL and sets up the rendering buffers.
void display_setup();

// Must be called repeatedly in the loop or via an LVGL timer task
// to handle touch input and render the UI.
void display_loop();

#endif // DISPLAY_SETUP_H
