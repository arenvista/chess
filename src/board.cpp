#include "board.hpp"
#include <cctype>
#include "memory"
#include "include_piece.hpp"
#include <iostream>

void Board::copyToBoard(board_t copy, board_t& target){
    for (int row=0; row<BOARD_SIZE; row++){
        for(int col=0; col<BOARD_SIZE; col++){
            target[row][col] = copy[row][col];
        }
    }
}

constexpr board_t INITIAL_THREAT_BOARD = { {
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
        }
};
constexpr board_t INITIAL_BOARD = {{
    { 'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R'  },
    { 'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'  },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { '-', '-', '-', '-', '-', '-', '-', '-' },
    { 'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p'  },
    { 'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r'  }
}};

void Board::initalizeBoard(board_t& board, board_t initalizerBoard){
    copyToBoard(initalizerBoard, board);
}


void Board::pushtoBoardHistory(board_t board_state){
    m_deque_board_history.push_back(board_state);
}

board_t Board::popFromBoardHistory(){
    board_t prior_state = m_deque_board_history.back();
    m_deque_board_history.pop_back();
    return  prior_state;
}

void Board::resetToLastHistory(){
    board_t prior_state = popFromBoardHistory();
    copyToBoard(prior_state, m_board);
}

Board::Board(){
    Board::initalizeBoard(m_board, INITIAL_BOARD);
    m_bking_pos = {0, E};
    m_wking_pos = {7, E};
}

Board::Board(board_t board) {
    copyToBoard(board, m_board);
}

void Board::printBoard(board_t board){
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
        case 'B':
            std::cout << "Making Bishop: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<Bishop>(p, starting, *this); 
        case 'R':
            // std::cout << "Making Rook: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<Rook>(p, starting, *this); 
        case 'N':
            // std::cout << "Making Knight: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<Knight>(p, starting); 
        case 'Q':
            // std::cout << "Making Queen: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<Queen>(p, starting, *this); 
        case 'K':
            // std::cout << "Making King: @Location: " <<  starting.row << " | " << starting.col << " OfChar(" << p << ")\n";
            return std::make_unique<King>(p, starting); 
        default:
            return std::make_unique<Pawn>(p, starting);
    }
 }

board_t& Board::getBoard(){return m_board;}
board_t& Board::getThreatBoard(PieceColor color){return color == WHITE_PIECE ? m_white_attack_board : m_black_attack_board;}

//Threat
void Board::setThreatCell(Position pos, PieceColor color){
    color == WHITE_PIECE ? m_white_attack_board[pos.row][pos.col]='*' : m_black_attack_board[pos.row][pos.col]='*';
}

char Board::getCell(Position pos){
    return m_board[pos.row][pos.col];
}

void Board::generateThreatBoard(){
    Board::initalizeBoard(m_white_attack_board, INITIAL_THREAT_BOARD);
    Board::initalizeBoard(m_black_attack_board, INITIAL_THREAT_BOARD);
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            char cell = m_board[i][j];
            std::cout << "Targeting cell " << i << " " << j << "\n";
               if (cell!='-'){
                auto piece = getPiece({i,j});
                std::cout <<  "generating for " << piece->getSymbol() << "\n";
                // Create a visitor that will call the `move` method on the Piece base class
                piece->updateThreat(*this);
            }
        }
    }
    return;
}

void Board::printThreatBoard(){
    std::cout << "BLACK ATTACK BOARD:" << std::endl;
    printBoard(m_black_attack_board);
    std::cout << "WHITE ATTACK BOARD:" << std::endl;
    printBoard(m_white_attack_board);
}

bool Board::kingIsSafe(){
    Position wk {};
    Position bk{};

    for (int row=0; row<8; row++){
        for (int col=0; col<8; col++){
            char cell = m_board[row][cell];
            if (cell == 'k'){wk={row,cell};}
            else if (cell == 'K'){bk={row,cell};}
        }
    }

    if(m_white_attack_board[bk.row][bk.col] != '*' && m_black_attack_board[wk.row][wk.col] != '*'){return true;}
    else{return false;}
}

bool Board::hasPiece(Position target){
    if (m_board[target.row][target.col] == '-'){return false;}
    return true;
}

void Board::addToBoardDeque(board_t boardTarget){
    m_deque_board_history.push_back(boardTarget);
}
