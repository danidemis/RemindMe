#include <Arduino.h>
#include "config.h"
#include "event_model.h"
#include "api_client.h"
#include "display_setup.h"
#include "ui.h"
#include <vector>

// Task handles if using FreeRTOS
TaskHandle_t fetchTaskHandle = NULL;

std::vector<Event> current_events;
unsigned long last_fetch_time = 0;
bool force_fetch = true;

// A FreeRTOS task to fetch JSON in the background
void fetch_task(void *pvParameters) {
  while (true) {
    if (force_fetch || (millis() - last_fetch_time >= FETCH_INTERVAL_MS)) {
      Serial.println("Starting fetch task...");
      bool success = fetch_events(current_events);
      
      if (success) {
        // Convert to C-arrays to pass to UI
        int count = current_events.size();
        const char* titles[count];
        unsigned long times[count];
        const char* types[count];

        for(int i=0; i<count; i++) {
          titles[i] = current_events[i].title.c_str();
          times[i] = current_events[i].time;
          types[i] = current_events[i].type.c_str();
        }

        // LVGL is not thread-safe by default, 
        // we should theoretically use a mutex here if display_loop is on another core.
        ui_update_events(titles, times, types, count);
        
        last_fetch_time = millis();
        force_fetch = false;
      } else {
        Serial.println("Fetch failed, will retry later.");
      }
    }
    
    // Sleep to prevent blocking watchdog
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to open
  
  Serial.println("Starting RemindMe Agenda...");

  // 1. Init Display & LVGL
  display_setup();

  // 2. Init UI
  ui_init();

  // 3. Connect to Wi-Fi
  setup_wifi();

  // 4. Create Background Fetch Task
  // Pin fetch task to Core 0 to leave Core 1 free for LVGL/Loop
  xTaskCreatePinnedToCore(
      fetch_task,       /* Task function. */
      "FetchTask",      /* String with name of task. */
      10000,            /* Stack size in bytes. */
      NULL,             /* Parameter passed as input of the task */
      1,                /* Priority of the task. */
      &fetchTaskHandle, /* Task handle. */
      0);               /* Core where the task should run */
}

void loop() {
  // Feed LVGL
  display_loop();
  
  // A small delay to let other background processes run
  delay(5);
}
