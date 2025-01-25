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
        auto piece_under_attack = board.getPiece(target);
        if (piece_under_attack->getColor() != m_color){
            return true;
        }
    } else {
        for (Position move : m_moves){
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    return false;
}
void King::updateThreat(Board& board){
    for (Position attack: m_attack_moves){
        Position attack_pos = {attack.row+m_position.row,  attack.col+m_position.col}; //position to be attacked
        if (attack_pos.row >-1 && attack_pos.col > -1 && attack_pos.row < 8 && attack_pos.col < 8){
            board.setThreatCell(attack_pos, this->m_color); //set cell to threatened under right board_color
        }
    }
    for (Position attack: m_moves){
        Position attack_pos = {attack.row+m_position.row,  attack.col+m_position.col}; //position to be attacked
        if (attack_pos.row >-1 && attack_pos.col > -1 && attack_pos.row < 8 && attack_pos.col < 8){
            board.setThreatCell(attack_pos, this->m_color); //set cell to threatened under right board_color
        }
    }

}
