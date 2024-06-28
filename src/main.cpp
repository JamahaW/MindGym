#include <Arduino.h>
#include <GyverTM1637.h>
#include "ledbutton.hpp"


#define MAX_STEPS 64

uint8_t steps[MAX_STEPS];
uint8_t last_step = 0;

#define PIN_TM1637_CLK A5
#define PIN_TM1637_DIO A4

GyverTM1637 disp(PIN_TM1637_CLK, PIN_TM1637_DIO);

LedButton buttons[] = {
  LedButton(2, 3),
  LedButton(4, 5),
  LedButton(7, 6),
  LedButton(9, 8),
};

#define RANDOM_ITERATIONS 8

uint32_t myinitRandomSeed(uint32_t offset) {
  for (uint8_t i = 0; i < RANDOM_ITERATIONS; i++) {
    offset += (analogRead(A0) & 0b11) << i;
  }
  return offset;
}

bool anyPressed() {
  for (LedButton& b : buttons) if (b.read()) return true;
  return false;
}

void test() {
  disp.displayByte(0xFF, 0xFF, 0xFF, 0xFF);

  for (LedButton& b : buttons)  b.setLed(true);
  delay(500);
  for (LedButton& b : buttons) b.setLed(false);
}

#define STEPS_PLAY_TIMEOUT_MS 200

void playSteps() {
  for (uint8_t i = 0; i <= last_step; i++) {
    disp.displayInt(i);
    LedButton& b = buttons[steps[i]];
    b.setLed(true);
    delay(STEPS_PLAY_TIMEOUT_MS);
    b.setLed(false);
    delay(STEPS_PLAY_TIMEOUT_MS);
  }
}

void appendStep() {
  steps[last_step++] = random() & 0b11;
}

void setup() {
  disp.clear();
  disp.brightness(7);

  test();

  delay(1000);

  uint8_t str[]{
    TM1637_letters::_H,
    TM1637_letters::_O,
    TM1637_letters::_L,
    TM1637_letters::_D,
    0,
    TM1637_letters::_A,
    TM1637_letters::_n,
    TM1637_letters::_y,
    0,
    TM1637_letters::_b,
    TM1637_letters::_u,
    TM1637_letters::_t,
    TM1637_letters::_t,
    TM1637_letters::_o,
    TM1637_letters::_n,
  };

  while (!anyPressed()) {
    disp.runningString(str, sizeof(str), 160);
  }

  uint32_t seed = myinitRandomSeed(micros());
  disp.displayInt(seed & 0xFFF);
  randomSeed(seed);
}

void loop() {

  playSteps();
  appendStep();
  delay(1000);



}