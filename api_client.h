#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <vector>
#include "event_model.h"

// Initialize Wi-Fi connection using stored credentials
void setup_wifi();

// Scans for Wi-Fi networks and returns a list of SSIDs
std::vector<String> scan_wifi_networks();

// Connect to a new Wi-Fi network and save to NVS
bool connect_new_wifi(const String& ssid, const String& password);

// Fetch events from the Google App Script URL and parse the JSON into a vector of Event
bool fetch_events(std::vector<Event>& events_list);

#endif // API_CLIENT_H
