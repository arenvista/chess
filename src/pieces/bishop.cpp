#include "include_piece.hpp"
//Bishop Function ------
void Bishop::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'B' : 'b';}

Bishop::Bishop(){};

void Bishop::generateMoves(Board board){
    //std::cout << "Generating Moves For Bishop\n";
    std::vector<Position> movements = { {1,1}, {1,-1}, {-1,1}, {-1,-1}, };
    for (Position direction : movements){
        std::cout << "stuck here 1\n";
        int row = direction.row;
        int col = direction.col;
        Position target = {row+m_position.row, col+m_position.col};
        bool res = board.hasPiece(target);
        //std::cout << "Row: " << row << "Col: " << col << "Has Piece Result:=" << res  << "\n";
        while(!res){
            // std::cout << "stuck here 2\n";
            while(target.row<BOARD_SIZE && target.row > -1 && target.col <BOARD_SIZE && target.col > -1){
                std::cout << "stuck here 3\n";
                //std::cout << "Adding Move to Bishop: " << row << " | " << col << "\n";
                m_moves.push_back({row,col});
                if(row>0){row++;}
                else{row--;}
                if(col>0){col++;}
                else{col--;}
                target = {row+m_position.row, col+m_position.col};
                res = board.hasPiece(target);
                std::cout << "target piece " << board.getPiece(target)->getSymbol() << " @" << target.row << target.col << "\n";
            }
            res = true;
        }
        if(res && target.row<BOARD_SIZE && target.row > -1 && target.col <BOARD_SIZE && target.col > -1){
            m_attack_moves.push_back({row,col});
        }
    }

}

bool Bishop::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {false};
    for (Position attack: m_attack_moves){ if (attack == movement){isAttack = true;} }
    if (isAttack){
        //std::cout << "is attack\n";
        auto piece_under_attack = board.getPiece(target);
        if (board.hasPiece(target) && piece_under_attack->getColor() != m_color){
            return true;
        }
    } else {
        //std::cout << "Current Pos: " << m_position.row << " | " << m_position.col << "\n";
        //std::cout << "Targeting" << target.row << " | " << target.col << "\n";
        //std::cout << "Attepting to Move: " << movement.row << " | " << movement.col << "\n";
        //std::cout << "is NOT attack\n";
        for (Position move : m_moves){
            //std::cout << "Move Possible to: " << move.row << " | " << move.col << " || " << rowMap[target.row] << "|" << target.col << "\n";
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    // //std::cout << "move invalid\n";
    return false;
}

Bishop::Bishop(char c, Position starting_position, Board board) : Piece(){
    m_position = starting_position;
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    std::cout << "Generating moves for bishop\n";
    //std::cout  << "Creating Bishop @: " << starting_position.row << " | " << starting_position.col << "\n";
    generateMoves(board);
    setSymbol();
}

void Bishop::updateThreat(Board& board){
    for (Position move: m_moves){
        Position target = {move.row+m_position.row, move.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
    for (Position move: m_attack_moves){
        Position target = {move.row+m_position.row, move.col+m_position.col};
        board.setThreatCell(target, m_color);
    }
};
