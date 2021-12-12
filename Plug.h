#ifndef PLUG_H
#define PLUG_H value

#include <Arduino.h>

class Plug
{
  public:
    Plug(String, String);
    void measure();
  private:
    // Normal Variables
    float I;
    float P;
    float limit;
    int zeroRef;
    String path;
    String ilce;
    String relayStat;
    String plugName;

    // Constants
    const int V = 220;
    const int relayPin = D5;
    const int frequency = 50;
    const float adcScale = 65536.0;
    const float sensitivity = 0.185;

    // Methods
    float getCurrentAC();
};
#endif
