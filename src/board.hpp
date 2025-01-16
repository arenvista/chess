#pragma once
#include "piece.hpp"
#include <unordered_map>
#include <variant>

class Board{
    char m_board[8][8];
public:
    enum Rows{ A, B, C, D, E, F, G };
    std::unordered_map<char, Rows> rowMap;
    Board();
    Board(char board[8][8]);
    void printBoard();
    void setCell(int row, int col, char value);
    std::variant<Pawn> getPiece(Piece::Position starting);
};
