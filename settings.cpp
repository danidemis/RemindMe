#include "settings.h"
#include "config.h"
#include <Preferences.h>

Preferences preferences;

void settings_init() {
    // Open Preferences with my-app namespace.
    // False means read/write mode
    preferences.begin(NVS_NAMESPACE, false);
}

String get_wifi_ssid() {
    return preferences.getString(NVS_KEY_WIFI_SSID, WIFI_SSID);
}

void set_wifi_ssid(const String& ssid) {
    preferences.putString(NVS_KEY_WIFI_SSID, ssid);
}

String get_wifi_pass() {
    return preferences.getString(NVS_KEY_WIFI_PASS, WIFI_PASSWORD);
}

void set_wifi_pass(const String& pass) {
    preferences.putString(NVS_KEY_WIFI_PASS, pass);
}

unsigned long get_sync_interval_ms() {
    return preferences.getULong(NVS_KEY_SYNC_INT, DEFAULT_FETCH_INTERVAL_MS);
}

void set_sync_interval_ms(unsigned long ms) {
    preferences.putULong(NVS_KEY_SYNC_INT, ms);
}

int get_alarm_mode() {
    return preferences.getInt(NVS_KEY_ALARM_MODE, 0);
}

void set_alarm_mode(int mode) {
    preferences.putInt(NVS_KEY_ALARM_MODE, mode);
}
