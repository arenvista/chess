#include "board.hpp"
#include "variant"
#include "memory"
#include <iostream>

const char INITAL_BOARD[8][8] = {
    // This represents the pieces on the board.
    // Keep in mind that pieces[0][0] represents A1
    // pieces[1][1] represents B2 and so on.
    // Letters in CAPITAL are white
    { 'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R'  },
    { 'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'  },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p'  },
    { 'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r'  }, 
};

Board::Board(){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            m_board[i][j] = INITAL_BOARD[i][j];
        }
    }
}

Board::Board(char board[8][8]) {
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            m_board[i][j] = board[i][j];
        }
    }
}

void Board::printBoard(){
    char rows[8] = {'A','B','C','D','E','F','G','H'};
    for (int i = 0; i < 8; ++i){
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j){
            std::cout << m_board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for(int i=0; i<8; i++){
        std::cout << rows[i] << " ";
    }
    std::cout << "\n";
}

void Board::setCell(Piece::Position pos,  char value){ m_board[pos.ind_row][pos.ind_col] = value; }

std::variant<Pawn> Board::getPiece(Piece::Position starting){
    char p = m_board[starting.ind_row][starting.ind_col];
    std::cout << "Selected " << p << "\n";
    std::variant<Pawn> piece {};
    switch(std::toupper(p)){
        case 'P':
            piece = Pawn(p, starting);
            Pawn test = std::get<Pawn>(piece);
            test.printDiag();
    }
    return piece;
}

bool Board::kingIsSafe(Piece::Position starting, Piece::Position ending){
    return true;
}

