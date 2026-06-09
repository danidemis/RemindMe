#include "power_manager.h"
#include "config.h"
#include "settings.h"
#include <Arduino.h>
#include <Wire.h>

#ifdef XPOWERS_CHIP_AXP2101
#include <XPowersLib.h>
XPowersPMU power;
#endif

bool screen_is_on = true;
unsigned long last_activity_time = 0;
const unsigned long SLEEP_TIMEOUT_MS = 30000; // 30 seconds

void power_init() {
    Wire.begin(IIC_SDA, IIC_SCL);
    
#ifdef XPOWERS_CHIP_AXP2101
    if (!power.begin(Wire, AXP2101_SLAVE_ADDRESS, IIC_SDA, IIC_SCL)) {
        Serial.println("AXP2101 initialization failed!");
    } else {
        Serial.println("AXP2101 init success!");
        power.setChargeTargetVoltage(XPOWERS_AXP2101_CHG_VOL_4V2);
        power.enableSystemVoltageMeasure();
        power.enableVbusVoltageMeasure();
        power.enableBattVoltageMeasure();
    }
#endif
    
    // PWM init for speaker (basic approach for beep)
    pinMode(PA_PIN, OUTPUT);
    digitalWrite(PA_PIN, LOW);
    
    power_wake_screen();
}

void power_loop() {
    if (screen_is_on && (millis() - last_activity_time > SLEEP_TIMEOUT_MS)) {
        power_sleep_screen();
    }
}

void power_wake_screen() {
    last_activity_time = millis();
    if (!screen_is_on) {
        Serial.println("Waking up screen");
        // On Waveshare board, usually ALDO3 or similar is used for display
#ifdef XPOWERS_CHIP_AXP2101
        power.enableALDO3();
#endif
        screen_is_on = true;
    }
}

void power_sleep_screen() {
    if (screen_is_on) {
        Serial.println("Screen sleeping");
#ifdef XPOWERS_CHIP_AXP2101
        power.disableALDO3();
#endif
        screen_is_on = false;
    }
}

void power_play_beep() {
    int mode = get_alarm_mode();
    if (mode == 0) {
        // Audio mode
        Serial.println("Beep!");
        // A simple square wave block
        digitalWrite(PA_PIN, HIGH);
        for(int i = 0; i < 500; i++) {
            digitalWrite(I2S_DOUT, HIGH);
            delayMicroseconds(500);
            digitalWrite(I2S_DOUT, LOW);
            delayMicroseconds(500);
        }
        digitalWrite(PA_PIN, LOW);
    } else {
        // Light mode (Blink screen)
        Serial.println("Blink!");
        for (int i=0; i<3; i++) {
            power_sleep_screen();
            delay(200);
            power_wake_screen();
            delay(200);
        }
    }
}
