#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <vector>
#include "event_model.h"

// Initialize Wi-Fi connection
void setup_wifi();

// Fetch events from the Google App Script URL and parse the JSON into a vector of Event
bool fetch_events(std::vector<Event>& events_list);

#endif // API_CLIENT_H
