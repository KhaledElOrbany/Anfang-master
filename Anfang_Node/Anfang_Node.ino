#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <espnow.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Arduino.h>

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

enum NodeTypes {
  Plug = 1,
  Light = 2,
  Fridge = 3
};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res = wm.autoConnect("Node");
  nodeInit();
}

void loop() {
  dataPacket packet;
  packet.data = 123;
  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  delay(3000);
}

void nodeInit() {
  addNodeToDB();
  closeWiFi();
  espNowInit();
}

void addNodeToDB() {
  StaticJsonBuffer<200> jsonBuffer;
  String json =
    "{\"NodeName\":\"new_node\",\"NodeMacAddress\":\"" + WiFi.macAddress() + "\"}";
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    Serial.println("parseObject() failed");
  } else {
    Serial.println("JSON OK");
  }

  String url = "http://192.168.1.50:5000/api/nodes/";

  Serial.println("TESTING POST");
  //Declare an object of class HTTPClient
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) {
    //Specify request destination
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("auth-key", "My_authentication_key");

    String data;
    root.printTo(data);
    //Send the request
    int httpCode = http.POST(data);

    //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      String payload = http.getString();
      //Print the response payload
      Serial.println(payload);
    }
    //Close connection
    http.end();
    Serial.println(httpCode);
  }
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

//WifiState getWifiState() {
//  return ((WifiState) Firebase.getInt(path + "/wifiState"));
//}

void openWiFi() {
  wifiState = wifiIsOpened;
}

void closeWiFi() {
  WiFi.disconnect();
  wifiState = wifiIsClosed;
}
