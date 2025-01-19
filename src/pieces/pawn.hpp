#pragma once
#include "piece.hpp"

class Pawn : public Piece{
    std::vector<Position> m_attack_moves;
public:
    Pawn();
    Pawn(char c, Position starting_position);
    virtual void setSymbol();
    void updateThreat(Board& board);
    virtual bool validMove(Position target, Board board);
};
