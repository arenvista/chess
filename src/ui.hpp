#include "piece.hpp"
#include <string>
#include <array>
#include "board.hpp"

class UI{
public:
    UI();
    enum Rows{ A, B, C, D, E, F, G };
    std::unordered_map<char, Rows> rowMap;
    std::string askForMove();
    bool validateInput(std::string input);
    std::array<Piece::Position, 2> parsePositions(std::string input);
};
