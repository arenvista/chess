#include "position.hpp"
std::unordered_map<char, Rows> rowMap = {
    {'a', A}, {'b', B}, {'c', C}, {'d', D},
    {'e', E}, {'f', F}, {'g', G}, {'h', H}
};


std::unordered_map<int, char> flipRowMap = {
    {A, 'a'}, {B, 'b'}, {C, 'c'}, {D, 'd'},
    {E, 'e'}, {F, 'f'}, {G, 'g'}, {H, 'h'}
};

auto get_direction_step = [](int current) -> int { 
    if (current > 0) return 1;
    if (current < 0) return -1;
    return 0;
};

int getDirectionStep(int num){
    return num > 0 ? 1 : -1;
}
