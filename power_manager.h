#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

void power_init();
void power_loop();
void power_wake_screen();
void power_sleep_screen();
void power_play_beep(); // Plays audio beep or blinks screen based on alarm mode

#endif // POWER_MANAGER_H
