#include <Arduino.h>
#include "config.h"
#include "settings.h"
#include "event_model.h"
#include "api_client.h"
#include "display_setup.h"
#include "ui.h"
#include "power_manager.h"
#include "button_handler.h"
#include <vector>

TaskHandle_t fetchTaskHandle = NULL;

std::vector<Event> current_events;
unsigned long last_fetch_time = 0;
bool force_fetch = true;

// A FreeRTOS task to fetch JSON in the background
void fetch_task(void *pvParameters) {
  while (true) {
    unsigned long fetch_interval = get_sync_interval_ms();
    if (force_fetch || (millis() - last_fetch_time >= fetch_interval)) {
      Serial.println("Starting fetch task...");
      bool success = fetch_events(current_events);
      
      if (success) {
        int count = current_events.size();
        // VLA (Variable Length Arrays) are standard in GCC
        const char* titles[count > 0 ? count : 1];
        unsigned long times[count > 0 ? count : 1];
        const char* types[count > 0 ? count : 1];

        for(int i=0; i<count; i++) {
          titles[i] = current_events[i].title.c_str();
          times[i] = current_events[i].time;
          types[i] = current_events[i].type.c_str();
        }

        ui_update_events(titles, times, types, count);
        
        last_fetch_time = millis();
        force_fetch = false;
      } else {
        Serial.println("Fetch failed, will retry later.");
      }
    }
    
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Starting RemindMe Agenda...");

  // 1. Init NVS Settings
  settings_init();

  // 2. Init Power Manager (AXP2101, screen sleep)
  power_init();

  // 3. Init Buttons
  button_init();

  // 4. Init Display & LVGL
  display_setup();

  // 5. Init UI
  ui_init();

  // 6. Connect to Wi-Fi
  setup_wifi();

  // 7. Create Background Fetch Task
  xTaskCreatePinnedToCore(
      fetch_task,
      "FetchTask",
      10000,
      NULL,
      1,
      &fetchTaskHandle,
      0);
}

void loop() {
  // Process UI
  display_loop();
  
  // Process buttons
  button_loop();

  // Process sleep timeouts
  power_loop();
  
  // Small delay to let other processes run
  delay(5);
}
