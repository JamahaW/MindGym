#include <EEPROM.h>
#include "game.hpp"


using device::display;
using device::buttons;

void MindGymGame::stepsPlay() {
    display.displayByte(_P, _L, _A, _Y);

    for (uint8_t i = 0; i <= cursor; i++) {
        LedButton& b = buttons[steps[i]];

        b.setLed(true);
        delay(PLAY_BLINK_TIMEOUT);

        b.setLed(false);
        delay(PLAY_BLINK_TIMEOUT);
    }
}

bool MindGymGame::inputCheck() {
    for (uint8_t i = 0; i <= cursor; i++) {
        display.displayInt(i);
        if (steps[i] != device::waitForClick()) return false;
    }
    return true;
}

void MindGymGame::gameOver() {
    new_game = true;
    max_score = max(max_score, cursor);

    EEPROM.write(0, max_score);

    uint8_t game_over_str[]{ _G, _A, _N, _N, _E, 0, _E, _n, _d };
    display.runningString(game_over_str, sizeof(game_over_str), RUN_STRING_SPEED);

    display.displayInt(max_score);
    delay(GAMEOVER_SCORE_DISPLAT_TIMEOUT);
    display.displayInt(cursor);
    delay(GAMEOVER_SCORE_DISPLAT_TIMEOUT);
}

void MindGymGame::begin() {
    new_game = false;
    cursor = 0;
    device::initRandom();
    for (int8_t& x : steps) x = random() & 0b11;

    max_score = EEPROM.read(0);

    uint8_t press_any_button[]{ _P, _r, _E, _S, _S, 0, _A, _n, _y, 0, _B, _u, _t, _t, _o, _n };
    display.runningString(press_any_button, sizeof(press_any_button), RUN_STRING_SPEED);
    device::waitForClick();
    display.clear();
}

void MindGymGame::update() {
    if (new_game) begin();

    stepsPlay();

    if (!inputCheck()) {
        gameOver();
        return;
    }

    cursor++;
    delay(INPUT_SCRORE_DISPLAY_TIMEOUT);
}
