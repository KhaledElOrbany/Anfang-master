#ifndef CONNECT_H
#define CONNECT_H value

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <FirebaseArduino.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Arduino.h>

#define FIREBASE_HOST "fir-demo-7221e.firebaseio.com"
#define FIREBASE_AUTH "O4YFLC8gchXku2fOLDyxEGofDfjCYFanGQTqYIL1"

enum WifiState {
  wifiIsClosed, wifiIsOpened
};

class Connect
{
  public:
    Connect();

    String nodeId = "plug00";
    String path = "/hm01/plugs/" + nodeId;
    String nodeMacAddress = WiFi.macAddress();

    WifiState wifiState = wifiIsOpened;
};
#endif
