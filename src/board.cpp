#include "board.hpp"
#include <cctype>
#include "memory"
#include "piece.hpp"
#include <iostream>

const char INITAL_THREAT_BOARD[BOARD_SIZE][BOARD_SIZE] = {
    // This represents the pieces on the board.
    // Keep in mind that pieces[0][0] represents A1
    // pieces[1][1] represents B2 and so on.
    // Letters in CAPITAL are white
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, 
};
const char INITAL_BOARD[BOARD_SIZE][BOARD_SIZE] = {
    // This represents the pieces on the board.
    // Keep in mind that pieces[0][0] represents A1
    // pieces[1][1] represents B2 and so on.
    // Letters in CAPITAL are white
    { 'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R'  },
    { 'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'  },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { 'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p'  },
    { 'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r'  }, 
};

void Board::initalizeBoard(char board[BOARD_SIZE][BOARD_SIZE], const char initalizerBoard[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            board[i][j] = initalizerBoard[i][j];
        }
    }
}

Board::Board(){
    Board::initalizeBoard(m_board, INITAL_BOARD);
}

Board::Board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            m_board[i][j] = board[i][j];
        }
    }
}

void Board::printBoard(const char board[BOARD_SIZE][BOARD_SIZE]){
    char rows[BOARD_SIZE] = {'A','B','C','D','E','F','G','H'};
    for (int i = 0; i < BOARD_SIZE; ++i){
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j){
            std::cout << board[i][j] << " ";
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
            break;
        case 'B':
            std::cout << "Making Bishop: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<Bishop>(p, starting, *this); 
            break;
        // Implement the creation of other pieces as required
        default:
            return std::make_unique<Pawn>(p, starting);
    }
 }


const char (&Board::getBoard() const)[BOARD_SIZE][BOARD_SIZE]{return m_board;}
const char (&Board::getThreatBoard(PieceColor color) const)[BOARD_SIZE][BOARD_SIZE]{ return color == WHITE_PIECE ? m_white_attack_board : m_black_attack_board; }

//Threat
void Board::setThreatCell(Position pos, PieceColor color){
    // std::cout << "Setting Threat... " << pos.row << pos.col << "\n";
    color == WHITE_PIECE ? m_white_attack_board[pos.row][pos.col]='*' : m_black_attack_board[pos.row][pos.col]='*';
}

void Board::generateThreatBoard(){
    Board::initalizeBoard(m_white_attack_board, INITAL_THREAT_BOARD);
    Board::initalizeBoard(m_black_attack_board, INITAL_THREAT_BOARD);
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            char cell = m_board[i][j];
                auto piece = getPiece({i,j});
                // Create a visitor that will call the `move` method on the Piece base class
                piece->updateThreat(*this);
        }
    }
}

void Board::printThreatBoard(){
    std::cout << "BLACK ATTACK BOARD:" << std::endl;
    printBoard(m_black_attack_board);
    std::cout << "WHITE ATTACK BOARD:" << std::endl;
    printBoard(m_white_attack_board);
}

bool Board::kingIsSafe(Position starting, Position ending){
    return true;
}

bool Board::hasPiece(Position target){
    if (m_board[target.row][target.col] != '-'){return true;}
    return false;
}
