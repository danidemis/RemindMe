#ifndef CONFIG_H
#define CONFIG_H

// --- Wi-Fi Configuration ---
#define WIFI_SSID "prova1"
#define WIFI_PASSWORD "Prova1234!"

// --- Google App Script Configuration ---
// The URL deployed from Google App Scripts (the one returning JSON)
#define GOOGLE_SCRIPT_URL                                                      \
  "https://script.google.com/macros/s/"                                        \
  "AKfycXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXMoM4ffHgs_xEv/"               \
  "exec"

// --- Fetch Interval ---
// How often to fetch events (in milliseconds). Default: 10 minutes
#define FETCH_INTERVAL_MS (10 * 60 * 1000)

// --- Timezone Configuration ---
// Adjust the offset for your timezone (e.g. 3600 for GMT+1, 7200 for GMT+2 during DST)
#define TIMEZONE_OFFSET_SEC 7200

// --- Default Settings (Overridden by NVS) ---
#define DEFAULT_FETCH_INTERVAL_MS (10 * 60 * 1000)
#define SNOOZE_DURATION_MS (5 * 60 * 1000) // 5 minutes snooze

// --- Hardware Pin Definitions (Waveshare ESP32-S3-Touch-AMOLED-1.8) ---
#define IIC_SDA 15
#define IIC_SCL 14
#define TP_INT 21

// Display Pins (SH8601 QSPI)
#define LCD_CS 12
#define LCD_SCLK 11
#define LCD_SDIO0 4
#define LCD_SDIO1 5
#define LCD_SDIO2 6
#define LCD_SDIO3 7
#define DISPLAY_WIDTH 368
#define DISPLAY_HEIGHT 448

// Audio Pins (ES8311 / Speaker PA)
#define I2S_BCLK 9
#define I2S_LRCK 45
#define I2S_DOUT 8
#define I2S_DIN 10
#define I2S_MCLK 16
#define PA_PIN 46

// Buttons
#define BOOT_BTN_PIN 0

// NVS Storage Keys
#define NVS_NAMESPACE "remindme"
#define NVS_KEY_WIFI_SSID "wifi_ssid"
#define NVS_KEY_WIFI_PASS "wifi_pass"
#define NVS_KEY_SYNC_INT "sync_int"
#define NVS_KEY_ALARM_MODE "alarm_mode" // 0: Audio, 1: Light

#endif // CONFIG_H
