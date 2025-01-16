#pragma once

#include <vector>
class Piece{
public:
    enum PieceColor{
        WHITE_PIECE = 0,
        BLACK_PIECE = 1
    };
    struct Position{
        int ind_row;
        int ind_col;
        // Overload the == operator to compare Position objects
        bool operator==(const Position& other) const {
            return ind_row == other.ind_row && ind_col == other.ind_col;
        }
    };
    Piece();
    Piece(char c, Position starting_position);
protected:
    Position m_position {0,0};
    PieceColor m_color;
    std::vector<Piece::Position> m_moves;
public:
    bool validMove(Position target);
    void setPosition(Position current_pos);

    void printPosition();
    void printColor();
    void printDiag();
};
class Pawn : public Piece{
public:
    Pawn();
    Pawn(char c, Position starting_position);
};

