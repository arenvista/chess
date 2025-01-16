#include "board.hpp"
#include "piece.hpp"
#include "ui.hpp"

class Game{
    Board m_board;
    UI m_ui;
    int m_round;
public:
    bool attemptMove(Piece::Position starting, Piece::Position ending);
    void runGame();
};
