#pragma once
#include "pawn.hpp"
class Knight : public Pawn{
    std::vector<Position> m_attack_moves;
public:
    Knight();
    Knight(char c, Position starting_position);
    bool validMove(Position target, Board board);
    void updateThreat(Board& board);
    void setSymbol();
};
