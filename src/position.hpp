#pragma once

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

