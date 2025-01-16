#include "piece.hpp"
#include <string>
#include <array>
#include "board.hpp"

class UI{
public:
    UI();
    enum Rows{ A, B, C, D, E, F, G };
    std::unordered_map<char, Rows> rowMap;

    /// Asks the player for their next move in a text-based interface.
    std::string askForMove();

    /// @brief Validates the user input for chess move format.
    /// @param input The string containing the input to validate.
    /// @return true if input is valid, false otherwise.
    bool validateInput(std::string input);

    /// Parses two chess positions from a string input.
    std::array<Piece::Position, 2> parsePositions(std::string input);
};
