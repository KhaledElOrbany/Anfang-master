#ifndef NODE_H
#define NODE_H value

#include <Arduino.h>

class Node
{
  public:
    Node(String, String, String);
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
