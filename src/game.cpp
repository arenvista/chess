#include "game.hpp"
#include <iostream>

bool Game::attemptMove(Piece::Position starting, Piece::Position ending){
    return false;
}

void Game::runGame(){
    m_board.printBoard();
    std::string move = m_ui.askForMove();
    std::cout << "Move is: " << move << "\n";
    std::array<Piece::Position, 2> move_pos = m_ui.parsePositions(move);
    m_board.getPiece(move_pos[0]);
}

