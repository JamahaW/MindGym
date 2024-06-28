#pragma once
#include <Arduino.h>
#include <GyverTM1637.h>
#include "ledbutton.hpp"

extern GyverTM1637 disp;
extern LedButton buttons[4];


int8_t Device_getPressedIndex() {
    for (int8_t ret = 0; ret < 4; ret++) {
        LedButton& b = buttons[ret];
        b.tick();

        if (b.click()) return ret;
    }
    return -1;
}

int8_t Device_waitInput() {
    int8_t ret;
    while ((ret = Device_getPressedIndex()) == -1) {}
    return ret;
}

void Device_initRandom() {
    static constexpr int RANDOM_GEN_ITERS = 16;

    uint32_t offset = micros();
    for (uint8_t i = 0; i < RANDOM_GEN_ITERS; i++)
        offset += (analogRead(A0) & 0b11) << i;

    randomSeed(offset);
}

void Device_Check() {
    disp.clear();
    disp.brightness(7);

    disp.displayByte(0xFF, 0xFF, 0xFF, 0xFF);

    for (LedButton& b : buttons)
        b.setLed(true);

    delay(200);

    for (LedButton& b : buttons)
        b.setLed(false);
}

struct MindGymGame {

    static constexpr int MAX_STEPS = 128;
    static constexpr int PLAY_BLINK_TIMEOUT = 500;
    static constexpr int RUN_STRING_SPEED = 100;

    int8_t steps[MAX_STEPS];
    mutable uint8_t cursor = 0;
    mutable uint8_t max_score = 0;
    mutable bool new_game = true;

    void stepsPlay() {
        disp.displayByte(_P, _L, _A, _Y);

        for (uint8_t i = 0; i <= cursor; i++) {
            LedButton& b = buttons[steps[i]];

            b.setLed(true);
            delay(PLAY_BLINK_TIMEOUT);

            b.setLed(false);
            delay(PLAY_BLINK_TIMEOUT);
        }
    }

    bool inputCheck() {
        disp.displayByte(_i, _n, _P, 0);

        for (uint8_t i = 0; i <= cursor; i++) {
            if (steps[i] != Device_waitInput()) return false;
        }
        return true;
    }

    void gameOver() {
        new_game = true;
        max_score = max(max_score, cursor);

        uint8_t game_over_str[]{ _G, _A, _N, _N, _E, 0, _E, _n, _d };
        disp.runningString(game_over_str, sizeof(game_over_str), RUN_STRING_SPEED);
        disp.point(true);
        disp.displayClockScroll(max_score, cursor, 50);
        delay(1000);
        disp.point(false);
    }

    void begin() {
        new_game = false;
        cursor = 0;
        Device_initRandom();

        for (int8_t& x : steps) x = random() & 0b11;

        uint8_t press_any_button[]{ _P, _r, _E, _S, _S, 0, _A, _n, _y, 0, _B, _u, _t, _t, _o, _n };
        disp.runningString(press_any_button, sizeof(press_any_button), RUN_STRING_SPEED);

        Device_waitInput();

        disp.clear();
    }

    public:

    void update() {
        if (new_game) begin();

        stepsPlay();

        if (!inputCheck()) {
            gameOver();
            return;
        }

        cursor++;
    }

};

