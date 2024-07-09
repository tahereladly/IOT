#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <WiFi.h>

class WiFiHelper {
public:
    WiFiHelper(const char* ssid, const char* password, bool _DEBUG = 0);
    void wifiInit();

private:
    const char* _SSID; // Declare private member variables
    const char* _PASSWORD;
    bool DEBUG;
};

#endif
