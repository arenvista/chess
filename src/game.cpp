#include "game.hpp"
#include <iostream>
#include "include_piece.hpp"
#include "position.hpp"

bool Game::attemptMove(Position starting, Position ending){
    auto piece = m_game_board.getPiece(starting);
    std::cout <<"Attempting Move\n";
    bool isValidMove = piece->validMove(ending, m_game_board);
    std::cout <<"Validated Moves...\n";
    if(isValidMove){
        std::cout << "Setting Cell...\n";
        m_game_board.pushtoBoardHistory(m_game_board.getBoard());
        m_game_board.setCell(starting, '-');
        m_game_board.setCell(ending, piece->getSymbol());
        if (!m_game_board.kingIsSafe()){
            m_game_board.resetToLastHistory();
            return false;
        }
        return true;
    }
    return false;
}

void Game::runGame(){
    std::cout << "A is black; a is white \n";
    m_game_board.printBoard(m_game_board.getBoard());
    int turn_count{WHITE_PIECE};
    while(true){
        std::cout << "Turn Move is... " << turn_count << "\n"; 
        // std::string move = "b0c2"; 
        std::string move = m_ui.askForMove();
        std::string color =  turn_count ==  BLACK_PIECE ? "BLACK_PIECE" : "WHITE_PIECE";
        std::cout << "Move is: " << move << "\nFor Color: " << color << "\n";
        std::array<Position, 2> move_pos = m_ui.parsePositions(move);
        auto p =  m_game_board.getPiece(move_pos[0]);
        bool color_match = p->getColor() != turn_count; 
        //diag
        std::string sel = color_match == WHITE_PIECE ? "WHITE_PIECE" : "BLACK_PIECE";
        std::cout << "Selected a " << sel << "\n";
        while (!color_match){
            std::cout << "Wrong Color...\n";
            std::string move = m_ui.askForMove();
            std::cout << "Move is: " << move << "\n";
            move_pos = m_ui.parsePositions(move);
            auto p =  m_game_board.getPiece(move_pos[0]);
            color_match = p->getColor() != turn_count; 
        }
        std::cout << "Color Match:" << color_match  << p->getColor() << "\n";
        m_game_board.pushtoBoardHistory(m_game_board.getBoard());
        bool moveAttempt = attemptMove(move_pos[0], move_pos[1]);
        if (!m_game_board.kingIsSafe()){
            m_game_board.copyToBoard(m_game_board.popFromBoardHistory(), m_game_board.getBoard());
            continue;
        }
        std::cout << "Finished move" << "\n";
        m_game_board.generateThreatBoard();
        // m_game_board.printThreatBoard();
        m_game_board.printBoard(m_game_board.getBoard());
        if (moveAttempt == true){
            turn_count = turn_count == WHITE_PIECE ? BLACK_PIECE : WHITE_PIECE;
        }
        std::cout << "Finished itter\n";
    }
}
