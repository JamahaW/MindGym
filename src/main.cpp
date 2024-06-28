#include <Arduino.h>
#include <GyverTM1637.h>
#include "ledbutton.hpp"
#include "game.hpp"


#define PIN_TM1637_CLK A5
#define PIN_TM1637_DIO A4

GyverTM1637 disp(PIN_TM1637_CLK, PIN_TM1637_DIO);

LedButton buttons[] = {
    LedButton(2, 3),
    LedButton(4, 5),
    LedButton(7, 6),
    LedButton(9, 8),
};

MindGymGame game;

void setup() {
  Device_Check();
}

void loop() {
  game.update();
}