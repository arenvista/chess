#include "include_piece.hpp"
// Rook
void Rook::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'R' : 'r'; std::cout << "Setting Symbol as " << m_color;}

Rook::Rook(){};
void Rook::generateMoves(Board board){
    std::cout << "Generating Moves For Rook\n";
    std::vector<Position> movements = { {1,0}, {0,-1}, {-1,0}, {0,1}, };
    for (Position direction : movements){
        int row = direction.row;
        int col = direction.col;
        bool res = board.hasPiece({row+m_position.row, col+m_position.col});
        std::cout << "Result: " << res << "\n"; 
        while(!res && row<BOARD_SIZE && row > -BOARD_SIZE && col <BOARD_SIZE && col > -BOARD_SIZE){
            std::cout << "Row: " << row << " Col: " << col << " Has Piece Result=" << res  << " Char:" << board.getBoard()[row+m_position.row][col+m_position.col] << " At Place:" << row+m_position.row << flipRowMap[col+m_position.col] << " \n";
            std::cout << "Adding Move to Rook: " << row << " | " << col << "\n";
            m_moves.push_back({row,col});
            if(row==0 && col<0){col--;}
            if(row==0 && col>0){col++;}
            if(col==0 && row<0){row--;}
            if(col==0 && row>0){row++;}
            res = board.hasPiece({row+m_position.row, col+m_position.col});
        }
        std::cout << "Finished Direction\n";
        if(board.hasPiece({row, col})){
            m_attack_moves.push_back({row,col});
        }
    }
    std::cout << "Finished adding moves\n";
}

bool Rook::validMove(Position target, Board board){
    Position movement { target.row-m_position.row, target.col-m_position.col};
    bool isAttack {false};
    std::cout << "Validating Moves ##\n";
    for (Position attack: m_attack_moves){ if (attack == movement){isAttack = true;} }
    if (isAttack){ //if attack
        std::cout << "is attack\n";
        auto piece_under_attack = board.getPiece(target);
        if (board.hasPiece(target) && piece_under_attack->getColor() != m_color){
            return true;
        }
    } else { //not an attack
        std::cout << "Current Pos: " << m_position.row << " | " << m_position.col << "\n";
        std::cout << "Targeting" << target.row << " | " << target.col << "\n";
        std::cout << "Attepting to Move: " << movement.row << " | " << movement.col << "\n";
        std::cout << "is NOT attack\n";
        for (Position move : m_moves){
            std::cout << "Move Possible to: " << move.row << " | " << move.col << " || " << rowMap[target.row] << "|" << target.col << "\n";
            if (movement == move && board.hasPiece(target) == false){ return true; }
        }
    }
    // std::cout << "move invalid\n";
    return false;
}

Rook::Rook(char c, Position starting_position, Board board) : Bishop(){
    m_color = isupper(c) ? BLACK_PIECE : WHITE_PIECE;
    m_position = starting_position;
    std::cout  << "Creating Rook @: " << starting_position.row << " | " << starting_position.col << "Given: " << c << "\n";
    generateMoves(board);
    setSymbol();
}

void Rook::updateThreat(Board& board){};
