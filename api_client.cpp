#include "api_client.h"
#include "config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void setup_wifi() {
    Serial.print("Connecting to Wi-Fi ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi connected.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to Wi-Fi.");
    }
}

bool fetch_events(std::vector<Event>& events_list) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Cannot fetch events: Wi-Fi disconnected.");
        return false;
    }

    HTTPClient http;
    // Set up HTTPS connection
    http.begin(GOOGLE_SCRIPT_URL);
    // Use GET request and follow redirects (Google Scripts always redirects to script.googleusercontent.com)
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    
    Serial.println("Fetching events from Google App Script...");
    int httpCode = http.GET();

    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println("JSON Received.");
            
            // Clear the existing list
            events_list.clear();

            // Parse JSON. Adjust the capacity based on expected payload size.
            // A DynamicJsonDocument in PSRAM is recommended if memory is tight, 
            // but for ESP32-S3 we have plenty of RAM.
            DynamicJsonDocument doc(8192);
            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                http.end();
                return false;
            }

            // The JSON is expected to be an array of objects
            for (JsonObject obj : doc.as<JsonArray>()) {
                Event ev;
                ev.title = obj["title"].as<String>();
                ev.time = obj["time"].as<unsigned long>();
                ev.type = obj["type"].as<String>();
                events_list.push_back(ev);
            }
            Serial.printf("Successfully parsed %d events/tasks.\n", events_list.size());
            http.end();
            return true;
        } else {
            Serial.printf("HTTP GET failed, code: %d\n", httpCode);
        }
    } else {
        Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    return false;
}
