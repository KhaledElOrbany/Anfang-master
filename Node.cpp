#include "Node.h"

Node::Node(String nodeName, String nodeType, String ilce) {
  this->ilce = ilce;
  this->state = 0;
  this->nodeType = nodeType;
  this->nodeName = nodeName;
  this->path = "hm001/nodes/" + this->nodeType + "/" + this->nodeName;
}

void Node::initNode() {
  
}
