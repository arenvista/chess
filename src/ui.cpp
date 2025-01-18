#include "ui.hpp"
#include <iostream>
#include <regex>

UI::UI(){};

bool UI::validateInput(std::string input){
    std::regex pattern(R"([a-zA-Z]\d[a-zA-Z]\d)");
    if (input.length() == 4 && std::regex_match(input, pattern)) {
        return true;
    } else{
        std::cout << "\nInvalid Input [Correct Usage: a1a2]: ";
    }
    return false;
}

std::string UI::askForMove(){
    std::string userInput {};
    std::cout << "Please enter your move (e.g., e2e4):";
    std::getline(std::cin, userInput);
    while(!validateInput(userInput)){
        std::getline(std::cin, userInput);
    }
        return userInput;
}

std::array<Position, 2> UI::parsePositions(std::string input){
    std::array<Position, 2> positions {};
    std::array<std::string, 2> input_positions = {input.substr(0,2), input.substr(2,2)};
    for(int i=0; i<2; i++){
        std::string input_pos = input_positions[i];
        // std::cout << "Parsing {"<< input_pos <<"} | Row[" << input_pos[1] <<"]    Col[" << rowMap[input_pos[0]] << "]\n";
        Position pos {input_pos[1]-'0', rowMap[input_pos[0]]};
        positions[i] = pos;
    }
    return positions;
}
