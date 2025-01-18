#pragma once

#include <unordered_map>
struct Position {
    int row;
    int col;

    // Overload the == operator to compare Position objects, if required
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};


enum PieceColor{
    WHITE_PIECE = 0,
    BLACK_PIECE = 1
};


enum Rows{ A, B, C, D, E, F, G, H };
extern std::unordered_map<char, Rows> rowMap; 
