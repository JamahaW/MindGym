#pragma once

#include "ledbutton.hpp"
#include <GyverTM1637.h>


namespace device {

extern GyverTM1637 display;
extern LedButton buttons[4];

static constexpr int BUTTON_INDEX_UNKNOWN = -1;
static constexpr int RANDOM_GEN_ITERS = 16;

int8_t getPressedButtonIndex();

int8_t waitForClick();

void initRandom();

void check();

} // namespace device

