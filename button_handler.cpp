#include "button_handler.h"
#include "config.h"
#include "power_manager.h"
#include "settings.h"
#include <OneButton.h>

// Setup a new OneButton on BOOT_BTN_PIN
OneButton button(BOOT_BTN_PIN, true, true);

void handleClick() {
    Serial.println("Button Clicked - Wake up");
    power_wake_screen();
}

void handleDoubleClick() {
    Serial.println("Button Double Clicked - Toggle Alarm Mode");
    power_wake_screen();
    int mode = get_alarm_mode();
    mode = (mode == 0) ? 1 : 0; // Toggle 0 and 1
    set_alarm_mode(mode);
    Serial.printf("Alarm mode changed to: %d\n", mode);
}

void handleLongPress() {
    Serial.println("Button Long Pressed - Power Off Request");
    power_wake_screen();
    
    // In a real scenario, this could invoke an LVGL modal.
    // For now, we simulate asking for confirmation by doing a beep.
    power_play_beep();
    
    // Then call power off (if AXP2101 supports it)
    // power_off_device();
}

void button_init() {
    // Attach the callback functions to the button
    button.attachClick(handleClick);
    button.attachDoubleClick(handleDoubleClick);
    button.attachLongPressStart(handleLongPress);
}

void button_loop() {
    // Keep watching the push button
    button.tick();
}
