#pragma once
#include "piece.hpp"
#include <unordered_map>
#include <variant>

class Board{
    char m_board[8][8];
public:
    Board();
    Board(char board[8][8]);
    void printBoard();
    void setCell(Piece::Position pos,  char value);
    std::variant<Pawn> getPiece(Piece::Position starting);
};
