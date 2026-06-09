#ifndef EVENT_MODEL_H
#define EVENT_MODEL_H

#include <Arduino.h>

// Represents a single calendar event or Google Task
struct Event {
    String title;
    unsigned long time; // Unix timestamp
    String type;        // "event" or "task"
};

#endif // EVENT_MODEL_H
