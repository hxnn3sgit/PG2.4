#include <iostream>

struct add {
	double number;
	add(double x) : number(x) {}
	double operator()(double y) { return number + y; }
};

int main() {
	
	add add_number(2);
	std::cout << add_number(2) << std::endl;

	int x = 3, y = 5;

	auto result = [](int x, int y) { return x + y; };

	std::cout << result(3, 5) << std::endl;


	return 0;
}
