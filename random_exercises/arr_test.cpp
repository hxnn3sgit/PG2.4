#include <iostream>
#include <initializer_list>

class DynArr {
	int *data;
	size_t size;
	size_t capacity;
public:
	DynArr(std::initializer_list<int> init_list) : size(init_list.size()), capacity(init_list.size()) {
		data = new int[size];
		int index = 0;
		for (const auto &element : init_list) {
			data[index++] = element;
		}
	}	
};

int main() {

	DynArr my_arr({1, 2, 3});
		
	return 0;
}
