#include "include_piece.hpp"
//King
void King::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'K' : 'k';}

King::King() : Pawn(){ }
King::King(char c, Position starting_position){
    m_position = starting_position;
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_moves = { {1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {0,-1}, {-1,0}, {0,1}  };
    setSymbol();
};

bool King::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {board.hasPiece(target)};
    if (isAttack){
        //std::cout << "is attack\n";
        auto piece_under_attack = board.getPiece(target);
        if (piece_under_attack->getColor() != m_color){
            return true;
        }
    } else {
        //std::cout << "Current Pos: " << m_position.row << " | " << m_position.col << "\n";
        //std::cout << "Target Pos: " << target.row << " | " << target.col << "\n";
        //std::cout << "Attepting to Move: " << movement.row << " | " << movement.col << "\n";
        //std::cout << "is NOT attack\n";
        for (Position move : m_moves){
            //std::cout << "Move Possible to: " << move.row << " | " << move.col << "\n";
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    return false;
}
