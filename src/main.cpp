#include <Arduino.h>
#include "game.hpp"

MindGymGame game;

void setup() {
  device::check();
}

void loop() {
  game.update();
}