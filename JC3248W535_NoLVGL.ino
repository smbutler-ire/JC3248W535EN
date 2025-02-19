// JC3248W535 Module
// Arduino_GFX with Touch
// NO LVGL
// Stephen Butler - Jan 2025

#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include "JC3248W535.h"

void setup() {
  InitDevice();
}

void loop() {
  printtxy();
  hello();
}
