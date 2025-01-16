#include "game.hpp"
#include <iostream>
#include <variant>

bool Game::attemptMove(Piece::Position starting, Piece::Position ending){
    auto piece = m_board.getPiece(starting);
    bool isValidMove = std::visit([ending](auto &&arg) -> bool {
        return arg.validMove(ending);
    }, piece);
    if(isValidMove){
        m_board.setCell(starting, ' ');
        m_board.setCell(ending, 'P');
    }
    m_board.printBoard();
    return false;
}

void Game::runGame(){
    m_board.printBoard();
    std::string move = m_ui.askForMove();
    std::cout << "Move is: " << move << "\n";
    std::array<Piece::Position, 2> move_pos = m_ui.parsePositions(move);
    attemptMove(move_pos[0], move_pos[1]);
}

