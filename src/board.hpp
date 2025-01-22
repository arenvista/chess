#pragma once
#include "position.hpp"
#include "array"
#include <memory>
#include <vector>

class Piece;

const int BOARD_SIZE = 8;

class Board{
    char m_board[BOARD_SIZE][BOARD_SIZE];
    char m_white_attack_board[BOARD_SIZE][BOARD_SIZE];
    char m_black_attack_board[BOARD_SIZE][BOARD_SIZE];

    using board_t = std::array<std::array<char, 8>, 8>; // Define the Board type as an 8x8 array
    std::vector<board_t> m_deque_board_history;           // Vector to hold a history of Boards
    std::vector<board_t> m_deque_white_threat_history;
    std::vector<board_t> m_deque_black_threat_history;


public:
    void initalizeBoard(char board[BOARD_SIZE][BOARD_SIZE], const char initalizerBoard[BOARD_SIZE][BOARD_SIZE]);
    Board();
    Board(char board[BOARD_SIZE][BOARD_SIZE]);
    /// @brief Prints the current state of the chess board to the console.
    void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
    /// Set the value of a board cell at a given position.
    void setCell(Position pos,  char value);
    /// Fetches the pawn piece from a given board position.
    std::unique_ptr<Piece> getPiece(Position starting);

    char getCell(Position pos);

    bool kingIsSafe(Position starting, Position ending);
    char (*getBoard())[8];
    char (*getThreatBoard(PieceColor color))[8];
    /// Prints a visual representation of the board showing all threatened squares.
    void printThreatBoard();
    // Generates a board with all possible threats from each piece.
    void generateThreatBoard();
    /// Sets the threat status of a cell based on the position and color of a threatening piece.
    void setThreatCell(Position pos, PieceColor color);
    const char (&getBoard() const)[BOARD_SIZE][BOARD_SIZE];
    const char (&getThreatBoard(PieceColor color) const)[BOARD_SIZE][BOARD_SIZE];
    //return true is position has a piece
    bool hasPiece(Position target);
    void addToBoardDeque(board_t boardTarget);
};
