#pragma once
#include "piece.hpp"
class Bishop : public Piece{
    std::vector<Position> m_attack_moves;
public:
    Bishop();
    Bishop(char c, Position starting_position, Board board);
    virtual void setSymbol();
    virtual void updateThreat(Board& board);
    virtual bool validMove(Position target, Board board);
    virtual void generateMoves(Board board);
};
