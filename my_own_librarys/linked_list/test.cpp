#include <iostream>
#include <list>
#include "linked_list.h"
int main() {
	std::list<int> my_list;

	my_list.push_back(1);
	my_list.push_back(2);

	for (const auto &element : my_list) {
		std::cout << element << std::endl;
	}


	LinkedList<int> own_list;
	

	return 0;
}
