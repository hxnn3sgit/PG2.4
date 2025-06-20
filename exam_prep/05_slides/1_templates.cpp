#include <iostream>
#include <string>

namespace my_funcs {
	template<typename T>
	T max(const T &first, const T &second) {
		if (first > second)
			return first;
		else
			return second;
	}
	
	template<typename U>
	U min(const U &first, const U &second) {
		if (first < second)
			return first;
		else
			
			return second;
	}

};

int main() {

	std::cout << my_funcs::max(1, 4) << std::endl;
	std::cout << my_funcs::max(3.2, 8.2) << std::endl;
	std::cout << my_funcs::max(std::string("abc"), std::string("def")) << std::endl;

	int a = 1, b = 4;
	std::cout << my_funcs::min<int>(1, 4) << std::endl;
	std::cout << my_funcs::min<float>(3.2, 8.2) << std::endl;
	std::cout << my_funcs::min(std::string("abc"), std::string("def")) << std::endl;
	std::cout << my_funcs::max<float>(1.1, 4) << std::endl;
	return 0;

}
