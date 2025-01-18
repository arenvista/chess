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
    char m_symbol;
    std::vector<Position> m_moves;
public:
    virtual bool validMove(Position target, Board board);
    void setPosition(Position current_pos);
    virtual void setSymbol()=0;

    void printPosition();
    void printColor();
    void printDiag();


    const char getSymbol();
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
    virtual void setSymbol();
    void updateThreat(Board& board);
    bool validMove(Position target, Board board);
};


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
