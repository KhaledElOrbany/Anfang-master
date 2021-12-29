#include "Node.h"

Node::Node(String nodeName, String nodeType) {
  this->state = 0;
  this->nodeType = nodeType;
  this->nodeName = nodeName;
  this->path = "hm001/nodes/" + this->nodeType + "/" + this->nodeName;
}

void Node::initNode() {
  StaticJsonBuffer<112> jsonBuffer;
  char json[] = "{\"NodeName\":\"plug03\",\"NodeMacAddress\":\"data\"}";
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
