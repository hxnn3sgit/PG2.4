#include <iostream>
#include <vector>
#include <string>

#include "dyn_arr.h"

template<typename T>
void print_all(const T &my_container) {
	std::cout << "printing all container elements:" << std::endl;

	for (const auto &element : my_container) 
		std::cout << element << std::endl;
}

int main() {
	std::vector<std::string> my_vec = { "hallo", "test" };

	print_all(my_vec);

	DynArr<int> my_dyn_arr;

	my_dyn_arr.push_data_back(1);
	my_dyn_arr.push_data_back(2);

	print_all(my_dyn_arr);

	return 0;
}
