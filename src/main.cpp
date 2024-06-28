#include <Arduino.h>
#include <GyverTM1637.h>
#include "ledbutton.hpp"

#define MAX_STEPS 128

int8_t steps[MAX_STEPS];
uint8_t cursor = 0;

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

void customRandomInit() {
  uint32_t offset = micros();

  for (uint8_t i = 0; i < RANDOM_ITERATIONS; i++)
    offset += (analogRead(A0) & 0b11) << i;

  randomSeed(offset);

  for (uint8_t i = 0; i < MAX_STEPS; i++) {
    steps[i] = random() & 0b11;
  }
}

#define ON_BLINK_PERIOD 80

int8_t getPressedIndex() {
  for (int8_t ret = 0; ret < 4; ret++) {
    LedButton& b = buttons[ret];
    b.tick();

    if (b.click())
      return ret;
  }
  return -1;
}

void onStartup() {
  Serial.begin(9600);

  disp.clear();
  disp.brightness(7);

  disp.displayByte(0xFF, 0xFF, 0xFF, 0xFF);

  for (LedButton& b : buttons)
    b.setLed(true);
  
  delay(200);

  for (LedButton& b : buttons)
    b.setLed(false);
}

#define STEPS_PLAY_TIMEOUT_MS 400

void stepsPlay() {
  for (uint8_t i = 0; i <= cursor; i++) {
    LedButton& b = buttons[steps[i]];

    disp.displayInt(i);
    b.setLed(true);
    delay(STEPS_PLAY_TIMEOUT_MS);

    b.setLed(false);
    delay(STEPS_PLAY_TIMEOUT_MS);
  }
}

int8_t waitUserInput() {
  int8_t ret;

  while (true) {
    disp.displayByte(_P, _i, _n, _G);

    ret = getPressedIndex();

    if (ret != -1)
      return ret;
  }

  return ret;
}

bool stepsRepeatCheck() {
  for (uint8_t i = 0; i <= cursor; i++) {
    if (steps[i] != waitUserInput())
      return false;
  }
  return true;
}

void setup() {
  onStartup();

  waitUserInput();
  customRandomInit();

  delay(1000);
}

void loop() {
  stepsPlay();

  if (!stepsRepeatCheck()) {
    disp.displayByte(_E, _N, _D, 0);
    exit(0);
  }

  cursor++;
}