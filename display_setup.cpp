#include "display_setup.h"
#include "config.h"

// Note: Exact pinout and initialization depends on the Waveshare library.
// We are adding placeholders for the standard Arduino_GFX setup for SH8601.

#define GFX_BL DF_GFX_BL // backlight pin, adjust as needed

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32QSPI(
    45 /* cs */, 47 /* sck */, 21 /* d0 */, 48 /* d1 */, 40 /* d2 */, 39 /* d3 */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_SH8601(
    bus, -1 /* RST */, 0 /* rotation */, false /* IPS */,
    DISPLAY_WIDTH, DISPLAY_HEIGHT);

/* Change to your screen resolution */
static const uint32_t screenWidth  = DISPLAY_WIDTH;
static const uint32_t screenHeight = DISPLAY_HEIGHT;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

/* Touchpad reading */
void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    // Placeholder for FT3168 touch logic.
    // E.g., if (touch_pressed) { data->state = LV_INDEV_STATE_PR; data->point.x = x; data->point.y = y; }
    // else { data->state = LV_INDEV_STATE_REL; }
    data->state = LV_INDEV_STATE_REL;
}

void display_setup()
{
    // Init Display
    gfx->begin();
    gfx->fillScreen(0x0000); // 0x0000 is Black in RGB565

#ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
#endif

    // Init LVGL
    lv_init();

    // Allocate draw buffer
    disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10);
    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        return;
    }
    
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    Serial.println("Display and LVGL setup completed");
}

void display_loop()
{
    lv_timer_handler(); // let the GUI do its work
}
