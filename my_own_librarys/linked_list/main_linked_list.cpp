#include <iostream>
#include <string>

#include "linked_list.h"

int main(int argc, char **argv) {
    LinkedList<int> my_list;

    if (!argc > 1) {
        std::cerr << "no arguments. please provide some!";
        return EXIT_FAILURE;
    }

	// simple appending:
	
    std::cout << "appending from 0 to 99 to list" << std::endl;

    for (int i = 0; i < 5; ++i) {
        my_list.append(i);
    }

    std::cout << my_list << std::endl;
	

	// inserting on special position:
	/*
    try {
        my_list.insertAt(34, 99999);
    } catch (std::out_of_range &e) {
        std::cerr << "element couldn't be inserted at position " << argc - 2 << ", " << e.what() << std::endl;
    } catch (std::runtime_error &e) {
        std::cerr << "element couldn't be inserted at position " << argc - 2 << ", " << e.what() << std::endl;
    }

    std::cout << "after inserting: " << std::endl << my_list << std::endl;
	*/

	// deleting at certain position:
	/*	
    try {
        my_list.deleteAt(8998);
    } catch(std::out_of_range &e) {
        std::cerr << "element couldn't be deletet at position 20: " << e.what() << std::endl;
    } catch(std::runtime_error &e) {
        std::cerr << "element couldn't be deletet at position 20: " << e.what() << std::endl;
    }

    std::cout << "after deleting: " << std::endl << my_list << std::endl;
	*/

	// Iterator tests:
	/*
    std::cout << "iterating with iterator for loop:" << std::endl;
    for (LinkedList<int>::Iterator it = my_list.begin(); it != my_list.end(); ++it) {
        std::cout << *it << std::endl;
    }

    for (const auto &x : my_list)
        std::cout << x << "\t";
    std::cout << std::endl;
	*/

	// Initializer List tests:
	/*	
	std::cout << "-----------------------------------\ninitializer list\n";
	LinkedList<int> init_list = { 1,2,3,4,5 };
	//LinkedList<int> init_list_2({1,2,3,4,5,6});

	std::cout << init_list << std::endl;
	//std::cout << init_list_2 << std::endl;

	LinkedList<int> test_append_empty_list;
	*/

	// size function test:
	/*	
	int sizee = my_list.size();	
	std::cout << sizee << std::endl;
	*/

	// cctor move ctor copy/move assign op tests:
	
	LinkedList<int> copied_list(my_list);
	LinkedList<int> moved_list(std::move(copied_list));
	
	std::cout << "copied_list: " << copied_list << std::endl;
	std::cout << "moved_list: " << moved_list << std::endl;
	


}
