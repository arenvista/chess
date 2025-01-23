#include "include_piece.hpp"
// Rook
void Rook::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'R' : 'r';}
void Rook::generateMoves(Board board){
    std::vector<Position> movements = { {1,0}, {0,-1}, {-1,0}, {0,1}, };
    for (Position direction : movements){
        int row = direction.row;
        int col = direction.col;
        int target_row = row+m_position.row;
        int target_col = col+m_position.col;
        if (target_row<0 || target_col<0){continue;}
        bool has_piece = board.hasPiece({target_row, target_col}); //stops moving in direction once first piece is hit
        while(!has_piece && target_row<BOARD_SIZE && target_row > -BOARD_SIZE && target_col <BOARD_SIZE && target_col > -BOARD_SIZE){
            m_moves.push_back({row,col});
            if(row==0 && col<0){col--;}
            if(row==0 && col>0){col++;}
            if(col==0 && row<0){row--;}
            if(col==0 && row>0){row++;}
            target_row = row+m_position.row;
            target_col = col+m_position.col;
            has_piece = board.hasPiece({target_row, target_col});
        }
        target_row = row+m_position.row;
        target_col = col+m_position.col;
        auto piece = board.getPiece({target_row, target_col});
        if(has_piece && target_row<BOARD_SIZE && target_row > -BOARD_SIZE && target_col <BOARD_SIZE && target_col > -BOARD_SIZE){
            m_attack_moves.push_back({row,col});
        }
    }
}

bool Rook::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {false};
    for (Position attack: m_attack_moves){ if (attack == movement){isAttack = true;} }
    if (isAttack){ //if attack
        auto piece_under_attack = board.getPiece(target);
        if (board.hasPiece(target) && piece_under_attack->getColor() != m_color){
            return true;
        }
    } else { //not an attack
        for (Position move : m_moves){
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    return false;
}

Rook::Rook(char c, Position starting_position, Board board) : Bishop(){
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_position = starting_position;
    setSymbol();
    generateMoves(board);
}

void Rook::updateThreat(Board& board){
    for (Position pos: m_attack_moves){
        Position target = {pos.row+m_position.row, pos.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
    for (Position pos: m_moves){
        Position target = {pos.row+m_position.row, pos.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
};
