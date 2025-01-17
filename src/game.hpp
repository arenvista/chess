#pragma once
#include "board.hpp"
#include "piece.hpp"
#include "position.hpp"
#include "ui.hpp"

class Game{
    Board m_game_board;
    UI m_ui;
    int m_round;
public:
    bool attemptMove(Position starting, Position ending);
    void runGame();
};
