#pragma once
#include "pawn.hpp"
class King : public Pawn{
    std::vector<Position> m_attack_moves;
public:
    King();
    King(char c, Position starting_position);
    bool validMove(Position target, Board board);
    void setSymbol();
};
