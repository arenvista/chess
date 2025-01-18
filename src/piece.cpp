#include "piece.hpp"
#include "board.hpp"
#include <cctype>  
#include <iostream>


//Parent Function ---------------------
/// Checks if the move to the target position is valid based on the piece's possible moves.
bool Piece::validMove(Position target, Board board){
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
void Pawn::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'P' : 'p';}
const char Pawn::getSymbol(){return m_symbol;}

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

//Bishop Function ------
void Bishop::setSymbol(){ m_symbol = m_color == BLACK_PIECE ? 'B' : 'b';}
const char Bishop::getSymbol(){return m_symbol;}

Bishop::Bishop(){};
void Bishop::generateMoves(Board board){
    std::cout << "Generating Moves For Bishop\n";
    std::vector<Position> movements = { {1,1}, {1,-1}, {-1,1}, {-1,-1}, };
    for (Position direction : movements){
        int row = direction.row;
        int col = direction.col;
        bool res = board.hasPiece({row+m_position.row, col+m_position.col});
        std::cout << "Row: " << row << "Col: " << col << "Has Piece Result:=" << res  << "\n";
        while(!board.hasPiece({row+m_position.row, col+m_position.col}) ){
            while(row<BOARD_SIZE && row > -BOARD_SIZE && col <BOARD_SIZE && col > -BOARD_SIZE){

                std::cout << "Adding Move to Bishop: " << row << " | " << col << "\n";
                m_moves.push_back({row,col});
                if(row>0){row++;}
                else{row--;}
                if(col>0){col++;}
                else{col--;}
            }
        }
        if(board.hasPiece({row, col})){
            m_attack_moves.push_back({row,col});
        }
    }

}
bool Bishop::validMove(Position target, Board board){
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
        std::cout << "Targeting" << target.row << " | " << target.col << "\n";
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

    Bishop::Bishop(char c, Position starting_position, Board board){
    m_position = starting_position;
    std::cout  << "Creating Bishop @: " << starting_position.row << " | " << starting_position.col << "\n";
    generateMoves(board);
    setSymbol();
}

void Bishop::updateThreat(Board& board){};
