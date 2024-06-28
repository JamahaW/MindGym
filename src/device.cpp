#include "device.hpp"

GyverTM1637 display(A5, A4);

LedButton buttons[4] = {
    LedButton(2, 3),
    LedButton(4, 5),
    LedButton(7, 6),
    LedButton(9, 8),
};


int8_t device::getPressedButtonIndex() {
    for (int8_t ret = 0; ret < 4; ret++) {
        LedButton& b = buttons[ret];
        b.tick();

        if (b.click()) return ret;
    }
    return BUTTON_INDEX_UNKNOWN;
}

int8_t device::waitForClick() {
    int8_t ret;
    while ((ret = getPressedButtonIndex()) == BUTTON_INDEX_UNKNOWN) {}
    return ret;
}

void device::initRandom() {
    uint32_t offset = micros();
    for (uint8_t i = 0; i < RANDOM_GEN_ITERS; i++)
        offset += (analogRead(A0) & 0b11) << i;

    randomSeed(offset);
}

void device::check() {
    display.clear();
    display.brightness(7);

    for (uint16_t i = 0; i <= 0xff; i++) {
        display.displayByte(i, i, i, i);

        delay(1);

        if (i > 10) continue;

        for (LedButton& b : buttons) {
            b.setLed(true);
            delay(50);
            b.setLed(false);
        }
    }
}
