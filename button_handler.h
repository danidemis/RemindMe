#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

// Call this from setup()
void button_init();

// Call this frequently from loop() or a dedicated task
void button_loop();

#endif // BUTTON_HANDLER_H
