#include "Connect.h"

Connect connection;

#define MY_NAME         "CONTROLLER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1

// please update this with the MAC address of the receiver
uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct __attribute__((packed)) dataPacket {
  int data;
};

void setup() {
  nodeInit();
}

void loop() {
  dataPacket packet;
  packet.data = 123;
  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  delay(3000);
}

void nodeInit() {
  Firebase.setInt(connection.path + "wifiState", connection.wifiState);
  while (connection.wifiState == wifiIsOpened) {
    connection.wifiState = (WifiState) Firebase.getInt(connection.path + "wifiState");
    if (connection.wifiState == wifiIsClosed) {
      WiFi.disconnect();
    }
  }
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
