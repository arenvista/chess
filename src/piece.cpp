#include "piece.hpp"
#include "board.hpp"
#include <cctype>  
#include <iostream>


//Parent Function ---------------------
/// Checks if the move to the target position is valid based on the piece's possible moves.
bool Piece::validMove(Position target){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    // std::cout << "Current Pos" << m_position.row << " | " << m_position.col << "\n";
    // std::cout << "Attepting to Move: " << movement.row << " | " << movement.col << "\n";
    for (Position move : m_moves){
        // std::cout << "Move Possible to: " << move.row << " | " << move.col << "\n";
        if (movement == move){ return true; }
    }
    // std::cout << "move invalid\n";
    return false;
}

Piece::Piece(){}

// Initializes a Piece with a given character representing color and a starting position.
Piece::Piece(char c, Position starting_position){
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_position = starting_position;
}

/// Print the current position (column and row indices) of the chess piece to the console.
void Piece::printPosition(){ std::cout << "Col:[" << m_position.col << "]    Row:[" << m_position.row << "]\n"; }
/// Prints the piece's color to the console.
void Piece::printColor(){ m_color == BLACK_PIECE ? std::cout << "BLACK\n" : std::cout << "WHITE\n"; }
// Prints the piece's diagonal information, including its position and color.
void Piece::printDiag(){printPosition(); printColor();}


Position Piece::getPosition(){ return m_position; }
PieceColor Piece::getColor(){ return m_color; }

//Pawn Function ---------------------
Pawn::Pawn() : Piece(){ }
Pawn::Pawn(char c, Position starting_position) : Piece(c, starting_position){
    m_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,0}, {2,0} } : std::vector<Position>{ {-1,0}, {-2,0} };
    m_attack_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,1}, {1,-1} } : std::vector<Position>{ {-1,-1}, {-1,1} };
};

void Pawn::updateThreat(Board& board){
    for (Position attack: m_attack_moves){
        Position attack_pos = {attack.row+m_position.row,  attack.col+m_position.col};
        if (attack_pos.row >-1 && attack_pos.col > -1 && attack_pos.row < 8 && attack_pos.col < 8){
            std::string color = m_color == BLACK_PIECE ? "BLACK" : "WHITE"; 
            // std::cout<< "Pawn: " << color << " Origin: " << m_position.row << " " << m_position.col << " || Attacking: " << attack.row+m_position.row << " " <<  attack.col+m_position.col << " Attack Vector " << attack.row << " " << attack.col << "\n";
            board.setThreatCell(attack_pos, this->m_color);
        }
    }
    // std::cout << "Finished Attack\n\n";
}
