#pragma once
#include "position.hpp"
#include "array"
#include <memory>
#include <vector>
#include <stack>

class Piece;

constexpr int BOARD_SIZE = 8;
using board_t = std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE>; // Define the Board type as an 8x8 array

//
class Board{
    board_t m_board;
    board_t m_white_attack_board;
    board_t m_black_attack_board;
    Position m_wking_pos;
    Position m_bking_pos;

    std::vector<board_t> m_deque_board_history;           // Vector to hold a history of Boards
    std::vector<board_t> m_deque_white_threat_history;
    std::vector<board_t> m_deque_black_threat_history;
    std::stack<board_t> m_stack_board_history; // Stack to hold a history of Boards
    static const size_t m_MAX_HISTORY_SIZE = 5; // Limit stack size to 5 elements

public:


    void copyToBoard(board_t copy, board_t& target);
    void passToBoard(board_t copy, board_t target);
    //pushes board to stack
    void pushtoBoardHistory(board_t board_state); 
    //pops from stack
    board_t popFromBoardHistory();
    void resetToLastHistory();
    void initalizeBoard(board_t& board, board_t initalizerBoard);
    Board();
    Board(board_t board);
    /// @brief Prints the current state of the chess board to the console.
    void printBoard(const board_t board);
    /// Set the value of a board cell at a given position.
    void setCell(Position pos,  char value);
    /// Fetches the pawn piece from a given board position.
    std::unique_ptr<Piece> getPiece(Position starting);

    char getCell(Position pos);

    bool kingIsSafe();
    board_t& getBoard();
    board_t& getThreatBoard(PieceColor color);
    /// Prints a visual representation of the board showing all threatened squares.
    void printThreatBoard();
    // Generates a board with all possible threats from each piece.
    void generateThreatBoard();
    /// Sets the threat status of a cell based on the position and color of a threatening piece.
    void setThreatCell(Position pos, PieceColor color);
    //return true is position has a piece
    bool hasPiece(Position target);
    void addToBoardDeque(board_t boardTarget);
};
