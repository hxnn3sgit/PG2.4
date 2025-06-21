#include <iostream>
#include <string>

#include "linked_list.h"

int main(int argc, char **argv) {
    LinkedList<int> my_list;

    if (!argc > 1) {
        std::cerr << "no arguments. please provide some!";
        return EXIT_FAILURE;
    }

    std::cout << "appending arguments to list" << std::endl;

    for (int i = 0; i < 100; ++i) {
        my_list.append(i);
    }

    std::cout << my_list << std::endl;

    try {
        my_list.insertAt(34, 99999);
    } catch (std::out_of_range &e) {
        std::cerr << "element couldn't be inserted at position " << argc - 2 << ", " << e.what() << std::endl;
    } catch (std::runtime_error &e) {
        std::cerr << "element couldn't be inserted at position " << argc - 2 << ", " << e.what() << std::endl;
    }

    std::cout << "after inserting: " << std::endl << my_list << std::endl;

    try {
        my_list.deleteAt(20);
    } catch(std::out_of_range &e) {
        std::cerr << "element couldn't be deletet at position 20: " << e.what() << std::endl;
    } catch(std::runtime_error &e) {
        std::cerr << "element couldn't be deletet at position 20: " << e.what() << std::endl;
    }

    std::cout << "after deleting: " << std::endl << my_list << std::endl;

    /*for (LinkedList<int>Iterator it = my_list.begin(); it != my_list.end(); ++it) {
        
    }*/
}