#ifndef PLUG_H
#define PLUG_H value

#include <Arduino.h>

class Plug
{
  public:
    Plug(String, String);
  private:
    // Normal Variables
    int state;
    String path;
    String ilce;
    String plugName;

    // Methods
};
#endif
