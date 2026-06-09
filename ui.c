#include "ui.h"
#include <stdio.h>

static lv_obj_t * main_screen;
static lv_obj_t * event_list;

void ui_init(void)
{
    main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0x000000), 0); // Dark theme

    // Create a title label
    lv_obj_t * title_label = lv_label_create(main_screen);
    lv_label_set_text(title_label, "RemindMe Agenda");
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_20, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    // Create a list to hold events
    event_list = lv_list_create(main_screen);
    lv_obj_set_size(event_list, lv_pct(100), lv_pct(85));
    lv_obj_align(event_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(event_list, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(event_list, 0, 0);

    // Load the main screen
    lv_scr_load(main_screen);
}

void ui_update_events(const char** titles, unsigned long* times, const char** types, int count)
{
    if (event_list == NULL) return;

    // Clear existing items
    lv_obj_clean(event_list);

    if (count == 0) {
        lv_obj_t * empty_label = lv_label_create(event_list);
        lv_label_set_text(empty_label, "No upcoming events!");
        lv_obj_set_style_text_color(empty_label, lv_color_hex(0x888888), 0);
        return;
    }

    for (int i = 0; i < count; i++) {
        char buf[128];
        // Format time dynamically or keep it simple for now (timestamp)
        // In a real app, convert Unix time to a human readable format
        snprintf(buf, sizeof(buf), "[%s] %s", types[i], titles[i]);
        
        lv_obj_t * btn = lv_list_add_btn(event_list, 
            (types[i][0] == 't') ? LV_SYMBOL_LIST : LV_SYMBOL_BELL, 
            buf);
            
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x2a2a2a), 0);
        lv_obj_set_style_text_color(btn, lv_color_hex(0xFFFFFF), 0);
    }
}
