#pragma once
#include "piece.hpp"
#include <unordered_map>
#include <variant>

class Board{
    char m_board[8][8];
public:
    Board();
    Board(char board[8][8]);
    /// @brief Prints the current state of the chess board to the console.
    void printBoard();
    /// Set the value of a board cell at a given position.
    void setCell(Piece::Position pos,  char value);
    /// Fetches the pawn piece from a given board position.
    std::variant<Pawn> getPiece(Piece::Position starting);
    /// Checks if the king remains safe after a move from the starting to ending position.
    bool kingIsSafe(Piece::Position starting, Piece::Position ending);
};
