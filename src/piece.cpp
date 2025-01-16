#include "piece.hpp"
#include "board.hpp"
#include <cctype>  
#include <iostream>

//Parent Function ---------------------
/// Checks if the move to the target position is valid based on the piece's possible moves.
bool Piece::validMove(Position target){
    Position movement { target.ind_row-m_position.ind_row, target.ind_col-m_position.ind_col};
    for (Position move : m_moves){
        if (movement == move){ return true; }
    }
    return false;
}

Piece::Piece(){}

// Initializes a Piece with a given character representing color and a starting position.
Piece::Piece(char c, Position starting_position){
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_position = starting_position;
}

/// Print the current position (column and row indices) of the chess piece to the console.
void Piece::printPosition(){ std::cout << "Col:[" << m_position.ind_col << "]    Row:[" << m_position.ind_row << "]\n"; }
/// Prints the piece's color to the console.
void Piece::printColor(){ m_color == BLACK_PIECE ? std::cout << "BLACK\n" : std::cout << "WHITE\n"; }
// Prints the piece's diagonal information, including its position and color.
void Piece::printDiag(){printPosition(); printColor();}

//Pawn Function ---------------------
Pawn::Pawn() : Piece(){ }
Pawn::Pawn(char c, Position starting_position) : Piece(c, starting_position){
    m_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,0}, {2,0} } : std::vector<Position>{ {-1,0}, {-2,0} };
    m_attack_moves = BLACK_PIECE ? std::vector<Position>{ {1,1}, {1,-1} } : std::vector<Position>{ {-1,-1}, {-1,1} };
};
