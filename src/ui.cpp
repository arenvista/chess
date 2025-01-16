#include "ui.hpp"
#include <iostream>
#include <regex>

UI::UI(){
    rowMap['a'] = A;
    rowMap['b'] = B;
    rowMap['c'] = C;
    rowMap['d'] = D;
    rowMap['e'] = E;
    rowMap['f'] = F;
    rowMap['g'] = G;
}

bool UI::validateInput(std::string input){
    std::regex pattern(R"([a-zA-Z]\d[a-zA-Z]\d)");
    if (input.length() == 4 && std::regex_match(input, pattern)) {
        return true;
    }
    return false;
}

std::string UI::askForMove(){
    std::string userInput {};
    std::cout << "Please enter your move (e.g., e2e4): ";
    while(!validateInput(userInput)){
        std::getline(std::cin, userInput);
    }
        return userInput;
}

std::array<Piece::Position, 2> UI::parsePositions(std::string input){
    std::array<Piece::Position, 2> positions {};
    std::array<std::string, 2> input_positions = {input.substr(0,2), input.substr(3,2)};
    for(int i=0; i<2; i++){
        std::string input_pos = input_positions[i];
        Piece::Position pos {rowMap[input_pos[0]], input_pos[1]-'0'};
        positions[i] = pos;
    }
    return positions;
}
