#include "Plug.h"

Plug::Plug(String plugName, String ilce) {
  this->I = 0;
  this->P = 0;
  this->zeroRef = 0;
  this->ilce = ilce;
  this->relayStat = "LOW";
  this->limit = 0.0;
  this->plugName = plugName;
  this->path = "hm001/plugs/" + plugName;
}

void Plug::measure() {
  
}

float Plug::getCurrentAC() {
  return 0.0;
}
