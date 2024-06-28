#pragma once

#include <Arduino.h>
#include <EncButton.h>


/// @brief Кнопка с светодиодом
class LedButton : public Button {

    /// @brief цифровой пин светодиода
    const uint8_t PIN_LED;

    public:

    /// @brief Кнопка с светодиодом
    /// @param button Пин кнопки PULLUP
    /// @param led Пин светодиода
    LedButton(uint8_t button, uint8_t led) : Button(button), PIN_LED(led) {
        pinMode(PIN_LED, OUTPUT);
    }

    /// @brief Установить состояние светодиода
    /// @param state false - выкл, true - вкл
    void setLed(bool state) const { digitalWrite(PIN_LED, state); }
};