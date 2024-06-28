#pragma once
#include "device.hpp"


/// @brief Игра "Повторяшка"
struct MindGymGame {

    static constexpr int MAX_STEPS = 128;
    static constexpr int PLAY_BLINK_TIMEOUT = 500;
    static constexpr int RUN_STRING_SPEED = 100;
    static constexpr int INPUT_SCRORE_DISPLAY_TIMEOUT = 800;
    static constexpr int GAMEOVER_SCORE_DISPLAT_TIMEOUT = 1000;

    int8_t steps[MAX_STEPS];
    mutable uint8_t cursor = 0;
    mutable uint8_t max_score = 0;
    mutable bool new_game = true;

    /// @brief Воспроизвести последовательность
    void stepsPlay();

    /// @brief Проверка ввода последовательности
    /// @return игрок верно повторил последовательность
    bool inputCheck();

    /// @brief Завершить этот сеанс игры
    void gameOver();

    /// @brief Подготовить новый сеанс игры
    void begin();

    public:

    /// @brief обновление игры
    void update();
};
