#pragma once
#include <vector>
#include "position.hpp"

class Board;

class Piece {
public:
    Piece();
    Piece(char c, Position starting_position);
protected:
    Position m_position {0,0};
    PieceColor m_color;
    std::vector<Position> m_moves;
public:
    bool validMove(Position target);
    void setPosition(Position current_pos);

    void printPosition();
    void printColor();
    void printDiag();


    Position getPosition();
    PieceColor getColor();
    virtual void updateThreat(Board& board) = 0;

    // virtual void updateThreat(Board& board);
};
class Pawn : public Piece{
    std::vector<Position> m_attack_moves;
public:
    Pawn();
    Pawn(char c, Position starting_position);
    void updateThreat(Board& board);
};

