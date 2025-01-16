#include "piece.hpp"
#include <cctype>  
#include <iostream>

bool Piece::validMove(Position target){
    Position movement { target.ind_row-m_position.ind_row, target.ind_col-m_position.ind_col};
    std::cout << "Attempting to move from Row|Col:" << m_position.ind_row <<" | " << m_position.ind_col <<"\n";
    std::cout << "To " << target.ind_row<< " | " << target.ind_col << "\n";
    std::cout << "Movement" << movement.ind_row<< " | " << movement.ind_col << "\n";
    for (Position move : m_moves){
        std::cout << "Possible Moves: " << move.ind_row << "|" << move.ind_col << "\n";
        if (movement == move){
            std::cout << "IS VALID \n";
            return true;
        }
    }
    return false;
}
Piece::Piece(){

}
Piece::Piece(char c, Position starting_position){
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_color == BLACK_PIECE ? std::cout << "is black" : std::cout << "is white";
    m_position = starting_position;
}

void Piece::printPosition(){ std::cout << "Col:[" << m_position.ind_col << "]    Row:[" << m_position.ind_row << "]\n"; }
void Piece::printColor(){ std::cout << "Team: " << m_color << "\n";}
void Piece::printDiag(){printPosition(); printColor();}


Pawn::Pawn() : Piece(){ }
Pawn::Pawn(char c, Position starting_position) : Piece(c, starting_position){
    m_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,0}, {2,0}, {1,1}, {1,-1} } : std::vector<Position>{ {-1,0}, {-2,0}, {-1,-1}, {-1,1} };
};


