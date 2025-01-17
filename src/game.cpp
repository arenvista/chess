#include "game.hpp"
#include <iostream>
#include <variant>

bool Game::attemptMove(Position starting, Position ending){
    auto piece = m_game_board.getPiece(starting);
    bool safeKing = m_game_board.kingIsSafe(starting, ending);
    bool isValidMove = piece->validMove(ending);
    if(isValidMove && safeKing){
        std::cout << "valid move\n";
        m_game_board.setCell(starting, ' ');
        m_game_board.setCell(ending, piece->getColor() == BLACK_PIECE ? 'P' : 'p');
    }
    m_game_board.printBoard(m_game_board.getBoard());
    return false;
}

void Game::runGame(){
    m_game_board.printBoard(m_game_board.getBoard());
    while(true){
        std::string move = m_ui.askForMove();
        std::cout << "Move is: " << move << "\n";
        std::array<Position, 2> move_pos = m_ui.parsePositions(move);
        attemptMove(move_pos[0], move_pos[1]);
        std::cout << "Finished move" << "\n";
        m_game_board.generateThreatBoard();
        m_game_board.printThreatBoard();
    }
}

