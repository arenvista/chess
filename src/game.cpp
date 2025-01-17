#include "game.hpp"
#include <iostream>
#include <variant>

bool Game::attemptMove(Position starting, Position ending){
    auto piece = m_board.getPiece(starting);
    bool safeKing = m_board.kingIsSafe(starting, ending);
    bool isValidMove = piece->validMove(ending);
    if(isValidMove && safeKing){
        std::cout << "valid move\n";
        m_board.setCell(starting, ' ');
        m_board.setCell(ending, piece->getColor() == BLACK_PIECE ? 'P' : 'p');
    }
    m_board.printBoard();
    return false;
}

void Game::runGame(){
    m_board.printBoard();
    while(true){
        std::string move = m_ui.askForMove();
        std::cout << "Move is: " << move << "\n";
        std::array<Position, 2> move_pos = m_ui.parsePositions(move);
        attemptMove(move_pos[0], move_pos[1]);
        std::cout << "Finished move" << "\n";
        // m_board.generateThreatBoard();
        // m_board.printThreatBoard();
    }
}

