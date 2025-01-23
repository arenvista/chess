#include "include_piece.hpp"
//Queen Function ------
void Queen::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'Q' : 'q';}

Queen::Queen(){};

void Queen::generateMoves(Board board){
    std::vector<Position> movements = { {1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {0,-1}, {-1,0}, {0,1}  };
    for (Position direction : movements){
        int row = direction.row;
        int col = direction.col;
        Position target = {m_position.row + row, m_position.col + col};
        bool hasPiece = board.hasPiece(target);
        while(!hasPiece && target.row<BOARD_SIZE && target.row > -1 && target.col <BOARD_SIZE && target.col > -1){
            //std::cout << "Adding Move to Queen: " << row << " | " << col << "\n";
            m_moves.push_back({row,col});
            //in line
            if(row==0 && col<0){col--;} //update left
            if(row==0 && col>0){col++;} //update right
            if(col==0 && row<0){row--;} //update down
            if(col==0 && row>0){row++;} //update top
            //in diag
            if(col>0 && row>0){ col++; row++; } //update tr
            if(col>0 && row <0){ col++; row--; } //update br
            if(col<0 && row <0){ col--; row--; } //update tr
            if(col<0 && row>0){ col--; row++;} //update  bl
            target = {m_position.row + row, m_position.col + col};
        }
        if(hasPiece && target.row<BOARD_SIZE && target.row > -1 && target.col <BOARD_SIZE && target.col > -1){
            m_attack_moves.push_back({row,col});
        }
    }
}

bool Queen::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {false};

    for (Position attack: m_attack_moves){
        if (attack == movement){
            isAttack = true;
        }
    }

    if (isAttack){
        auto piece_under_attack = board.getPiece(target);
        if (board.hasPiece(target) && piece_under_attack->getColor() != m_color){
            return true;
        }
    }else{
        for (Position move : m_moves){
            //std::cout << "Move Possible to: " << move.row << " | " << move.col << " || " << rowMap[target.row] << "|" << target.col << "\n";
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    // //std::cout << "move invalid\n";
    return false;
}

Queen::Queen(char c, Position starting_position, Board board) : Bishop(){
    m_position = starting_position;
    generateMoves(board);
    setSymbol();
}

void Queen::updateThreat(Board& board){
    for (Position pos: m_attack_moves){
        Position target = {pos.row+m_position.row, pos.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
    for (Position pos: m_moves){
        Position target = {pos.row+m_position.row, pos.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
};

