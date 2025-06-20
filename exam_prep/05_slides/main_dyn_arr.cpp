#include "dyn_arr.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cerr << "no args provided, please give some args!" << std::endl;
		return EXIT_FAILURE;
	} else {
		dyn_arr<std::string> my_dyn_arr;
		for (int i = 1; i < argc; ++i) {
			// int value = std::stoi(argv[i]);
			my_dyn_arr.push_data_back(argv[i]);
		}

		std::cout << my_dyn_arr << std::endl;

		std::cout << "using iterators:" << std::endl;
		/*for (dyn_arr<int>::Iterator it = my_dyn_arr.begin(); it != my_dyn_arr.end(); it++) {

		} */
	}
}

