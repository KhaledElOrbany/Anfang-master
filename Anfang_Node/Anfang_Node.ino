#include <ESP8266WiFi.h>
#include <espnow.h>
#include <FirebaseArduino.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Arduino.h>

#define FIREBASE_HOST "fir-demo-7221e.firebaseio.com"
#define FIREBASE_AUTH "O4YFLC8gchXku2fOLDyxEGofDfjCYFanGQTqYIL1"

#define MY_NAME         "CONTROLLER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1

uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0x23, 0x5E, 0x4A};

struct __attribute__((packed)) dataPacket {
  int data;
};

enum WifiState {
  wifiIsClosed, wifiIsOpened
} wifiState = wifiIsOpened;

String nodeId = "plug00";
String path = "/hm01/plugs/" + nodeId;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res = wm.autoConnect("Node");
  if (!res) {
    Serial.println("Failed to connect");
  } else {
    Serial.println("connected...yeey :)");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  nodeInit();
}

void loop() {
  dataPacket packet;
  packet.data = 123;
  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  delay(3000);
}

void nodeInit() {
  closeWiFi();
  Firebase.setInt(path + "/wifiState", wifiState);
  Firebase.setString(path + "/nodeMacAddress", WiFi.macAddress());

  espNowInit();
}

void espNowInit() {
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }
  esp_now_set_self_role(MY_ROLE);
  // this function will get called once all data is sent
  esp_now_register_send_cb(transmissionComplete);
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  Serial.println("Initialized.");
}

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if (transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}

WifiState getWifiState() {
  return ((WifiState) Firebase.getInt(path + "/wifiState"));
}

void openWiFi() {
  wifiState = wifiIsOpened;
}

void closeWiFi() {
  wifiState = wifiIsClosed;
}
