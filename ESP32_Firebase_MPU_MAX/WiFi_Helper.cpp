#include "WiFi_Helper.h"

WiFiHelper::WiFiHelper(const char* ssid, const char* password, bool _DEBUG) : _SSID(ssid), _PASSWORD(password), DEBUG(_DEBUG){
  // Constructor implementation remains unchanged
}

void WiFiHelper::wifiInit() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if(DEBUG){
      Serial.print("[INFO] Connecting to: ");
      Serial.println(_SSID);
    }

    WiFi.begin(_SSID, _PASSWORD);
    if(DEBUG && WiFi.status() != WiFi.status() != WL_CONNECTED){
      Serial.print("[INFO] ");
    }
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if(DEBUG){
          Serial.print("-");
        }
    }
    if(DEBUG){
      Serial.println("");
      Serial.println("[INFO] WiFi Connected");
    }
}
