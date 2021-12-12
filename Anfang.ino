#include "Plug.h"
#include "Connect.h"

int currentSec = 0;
Plug plug("plug01", "Serdivan");

void setup() {
  Serial.begin(115200);
  Connect connection;
}

void loop() {
  if (currentSec == 60) {
    currentSec = 1;
  }
  currentSec++;
  Serial.println(currentSec);
  delay(1000);
}
