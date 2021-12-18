#include "Plug.h"

Plug::Plug(String plugName, String ilce) {
  this->ilce = ilce;
  this->state = 0;
  this->plugName = plugName;
  this->path = "hm001/plugs/" + plugName;
}
