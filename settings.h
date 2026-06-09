#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

void settings_init();

// WiFi credentials
String get_wifi_ssid();
void set_wifi_ssid(const String& ssid);

String get_wifi_pass();
void set_wifi_pass(const String& pass);

// Sync Interval
unsigned long get_sync_interval_ms();
void set_sync_interval_ms(unsigned long ms);

// Alarm mode (0 = Audio, 1 = Light)
int get_alarm_mode();
void set_alarm_mode(int mode);

#endif // SETTINGS_H
