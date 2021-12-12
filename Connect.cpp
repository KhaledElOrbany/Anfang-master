#include "Connect.h"

Connect::Connect() {
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res = wm.autoConnect("Anfang", "");
  if (!res) {
    Serial.println("Failed to connect");
  } else {
    Serial.println("connected...yeey :)");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
