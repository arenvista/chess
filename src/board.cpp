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
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            std::cout << m_board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::variant<Pawn> Board::getPiece(Piece::Position starting){
    char p = m_board[starting.ind_row][starting.ind_col];
    std::cout << "Selected " << p << "\n";
    std::variant<Pawn> piece {};
    switch(p){
        case 'P':
            std::cout << "Pawn Detected...\n";
            piece = Pawn(p, starting);
    }
    Pawn test = std::get<Pawn>(piece);
    test.printDiag();
    return piece;
}
