#pragma once
#include "bishop.hpp"
class Rook : public Bishop{
    std::vector<Position> m_attack_moves;
public:
    Rook();
    Rook(char c, Position starting_position, Board board);
    virtual void setSymbol();
    virtual void updateThreat(Board& board);
    bool validMove(Position target, Board board);
    void generateMoves(Board board);
};
