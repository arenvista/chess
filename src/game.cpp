#include "game.hpp"
#include <iostream>
#include "include_piece.hpp"
#include "position.hpp"

bool Game::attemptMove(Position starting, Position ending){
    auto piece = m_game_board.getPiece(starting);
    std::cout <<"Attempting Move\n";
    bool safeKing = m_game_board.kingIsSafe(starting, ending);
    bool isValidMove = piece->validMove(ending, m_game_board);
    std::cout <<"Validated Moves...\n";
    if(isValidMove && safeKing){
        std::cout << "Setting Cell...\n";
        m_game_board.setCell(starting, '-');
        m_game_board.setCell(ending, piece->getSymbol());
    }
    m_game_board.printBoard(m_game_board.getBoard());
    return true;
}

void Game::runGame(){
    m_game_board.printBoard(m_game_board.getBoard());
    int turn_count{WHITE_PIECE};
    while(true){
        std::string move = "a1a3"; //m_ui.askForMove();
        std::string color =  turn_count ==  BLACK_PIECE ? "BLACK_PIECE" : "WHITE_PIECE";
        std::cout << "Move is: " << move << "For Color!!!: " << color << "\n";
        std::array<Position, 2> move_pos = m_ui.parsePositions(move);
        auto p =  m_game_board.getPiece(move_pos[0]);
        bool color_match = p->getColor() != turn_count; 

        while (!color_match){
            std::cout << "Wrong Color...\n";
            std::string move = m_ui.askForMove();
            std::cout << "Move is: " << move << "\n";
            move_pos = m_ui.parsePositions(move);
            auto p =  m_game_board.getPiece(move_pos[0]);
            color_match = p->getColor() != turn_count; 
        }

        turn_count = 1 - turn_count;
        attemptMove(move_pos[0], move_pos[1]);
        std::cout << "Finished move" << "\n";
        m_game_board.generateThreatBoard();
        m_game_board.printThreatBoard();
    }
}
