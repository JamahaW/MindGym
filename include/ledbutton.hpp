#pragma once

#include <Arduino.h>
#include <EncButton.h>

class LedButton : public Button {

    const uint8_t PIN_LED;
    mutable bool led_state = false;

    public:

    LedButton(uint8_t button, uint8_t led) : Button(button), PIN_LED(led) {
        pinMode(PIN_LED, OUTPUT);
    }

    void setLed(bool state) const { digitalWrite(PIN_LED, led_state = state); }

    void toggleLed() const { setLed(!led_state); }
};