#ifndef NODE_H
#define NODE_H value

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

class Node
{
  public:
    Node(String, String);
  private:
    // Normal Variables
    int state;
    String path;
    String ilce;
    String nodeType;
    String nodeName;

    // Methods
    void initNode();
};
#endif
