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
// Adjust the offset for your timezone (e.g. 3600 for GMT+1, 7200 for GMT+2
// during DST)
#define TIMEZONE_OFFSET_SEC 7200

// --- Display Configuration ---
// The ESP32-S3 AMOLED 1.8 has a resolution of 368x448
#define DISPLAY_WIDTH 368
#define DISPLAY_HEIGHT 448

// (Optional) Pin definitions if not using default Waveshare library pins.
// Commonly these are already handled by Arduino_DriveBus and
// GFX_Library_for_Arduino.

#endif // CONFIG_H
