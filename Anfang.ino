#include "Node.h"
#include "Connect.h"

Node plug00("plug00", "plugs", "Serdivan");
Node plug01("plug01", "plugs", "Serdivan");

void setup() {
  Serial.begin(115200);
  Connect connection;
  Firebase.setString("hm01/masterMacAddress", WiFi.macAddress());
}

void loop() {
  
}
