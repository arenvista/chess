#include "board.hpp"
#include <cctype>
#include "memory"
#include "piece.hpp"
#include <iostream>

const char INITAL_BOARD[BOARD_SIZE][BOARD_SIZE] = {
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
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            m_board[i][j] = INITAL_BOARD[i][j];
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            m_attack_boards[i][j][WHITE_PIECE] = ' ';
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            m_attack_boards[i][j][BLACK_PIECE] = ' ';
        }
    }
}

Board::Board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            m_board[i][j] = board[i][j];
        }
    }
}

void Board::printBoard(){
    char rows[BOARD_SIZE] = {'A','B','C','D','E','F','G','H'};
    for (int i = 0; i < BOARD_SIZE; ++i){
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j){
            std::cout << m_board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << rows[i] << " ";
    }
    std::cout << "\n";
}

void Board::setCell(Position pos,  char value){ m_board[pos.row][pos.col] = value; }

std::unique_ptr<Piece> Board::getPiece(Position starting){
    char p = m_board[starting.row][starting.col];
    // std::cout << "Selected " << p << "\n";
    switch(std::toupper(p)){
        case 'P':
            return std::make_unique<Pawn>(p, starting); 
        // Implement the creation of other pieces as required
        default:
            return std::make_unique<Pawn>(p, starting);
    }
 }

//Threat
void Board::setThreatCell(Position pos, PieceColor color){
    // std::cout << "Setting Threat... " << pos.row << pos.col << "\n";
    color == WHITE_PIECE ? m_attack_boards[pos.row][pos.col][WHITE_PIECE]='*' : m_attack_boards[pos.row][pos.col][BLACK_PIECE]='*';
}

void Board::generateThreatBoard(){
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            char cell = m_board[i][j];
            if (cell != ' '){
                auto piece = getPiece({i,j});
                // Create a visitor that will call the `move` method on the Piece base class
                piece->updateThreat(*this);
            }
        }
    }
}

void Board::printThreatBoard(){
    std::cout << "PRINTING THREAT\nBLACK ATTACK BOARD\n";
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            std::cout << m_attack_boards[i][j][BLACK_PIECE] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "WHITE ATTACK BOARD\n";
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            std::cout << m_attack_boards[i][j][WHITE_PIECE] << " ";
        }
        std::cout << "\n";
    }
}

bool Board::kingIsSafe(Position starting, Position ending){
    return true;
}

