#include "include_piece.hpp"
//Knight
void Knight::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'N' : 'n';}

Knight::Knight() : Pawn(){ }
Knight::Knight(char c, Position starting_position){
    m_position = starting_position;
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_moves = std::vector<Position>{ {2,1}, {2,-1}, {-2, 1}, {-2,-1} };
    setSymbol();
};

bool Knight::validMove(Position target, Board board){
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
    // //std::cout << "move invalid\n";
    return false;
}
