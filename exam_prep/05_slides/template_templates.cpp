#include <iostream>
#include <vector>
#include <list>

template<template<typename> class Container, typename T>
class DataBox {
	Container<T> box;
public:
	DataBox() = default;
	DataBox(std::initializer_list<T> list) : box(list) {}

	template<template<typename> class Container1, typename U>
	friend std::ostream& operator<<(std::ostream& out, const DataBox<Container1, U> &other);
};

template<template<typename> class Container, typename T>
std::ostream& operator<<(std::ostream &out, const DataBox<Container, T> &other) {
	out << "container print:" << std::endl;
	for (const auto &element : other.box)
		out << element << std::endl;
	
	return out;
}

int main() {
	DataBox<std::vector, int> int_box({1, 2, 3});
   	DataBox<std::list, std::string> string_box({"hello", "world"});

	std::cout << int_box << std::endl;
	std::cout << string_box << std::endl;

	return 0;
}
