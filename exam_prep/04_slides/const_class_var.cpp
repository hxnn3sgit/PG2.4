#include <iostream>

class MyClass {
	const int counter;
public:
	MyClass(const int c) : counter(c) {}
	int getCounter() { return counter; }
};

int main() {
	MyClass obj1(28);

	std::cout << obj1.getCounter() << std::endl;

	return 0;
}
