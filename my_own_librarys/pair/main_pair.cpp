#include <iostream>
#include <utility>

#include "../dyn_arr/dyn_arr.h"
#include "pair.h"

int main() {

    
    Pair<int, int> first_one(3, 1);
    Pair second_one(2, 9);

    std::cout << (first_one < second_one) << std::endl;

    Pair copied_one(first_one);
    std::cout << first_one << copied_one << std::endl;

    Pair moved_second(std::move(second_one));
    std::cout << moved_second << std::endl;

    std::cout << second_one << std::endl;

    return 0;
}