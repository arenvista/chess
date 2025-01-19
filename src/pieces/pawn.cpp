#include "include_piece.hpp"

//Pawn Function ---------------------
void Pawn::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'P' : 'p';}

Pawn::Pawn() : Piece(){ }
Pawn::Pawn(char c, Position starting_position) : Piece(c, starting_position){
    m_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,0}, {2,0} } : std::vector<Position>{ {-1,0}, {-2,0} };
    m_attack_moves = m_color == BLACK_PIECE ? std::vector<Position>{ {1,1}, {1,-1} } : std::vector<Position>{ {-1,-1}, {-1,1} };
    setSymbol();
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

bool Pawn::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {false};
    for (Position attack: m_attack_moves){ if (attack == movement){isAttack = true;} }
    if (isAttack){
        std::cout << "is attack\n";
        auto piece_under_attack = board.getPiece(target);
        if (board.hasPiece(target) && piece_under_attack->getColor() != m_color){
            return true;
        }
    } else {
        std::cout << "Current Pos: " << m_position.row << " | " << m_position.col << "\n";
        std::cout << "Attepting to Move: " << movement.row << " | " << movement.col << "\n";
        std::cout << "is NOT attack\n";
        for (Position move : m_moves){
            std::cout << "Move Possible to: " << move.row << " | " << move.col << "\n";
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    // std::cout << "move invalid\n";
    return false;
}
