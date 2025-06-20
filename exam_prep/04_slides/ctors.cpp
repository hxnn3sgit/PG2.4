#include <iostream>

class SmartNumber {
private:
	int value;
public:
	SmartNumber() : value(0) { std::cout << __PRETTY_FUNCTION__ << std::endl; } // inline default ctor
	SmartNumber(const int value) : value(value) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	} // parameter with initializer, no reference due to int type
	SmartNumber(const SmartNumber &other) : value(other.value) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;	
	} // copy ctor
	SmartNumber(SmartNumber &&other) = delete; // move ctor
	
	int getValue() const { return value; }

};

int main() {
	SmartNumber a;
	SmartNumber b(10);
	SmartNumber c(b);
	SmartNumber d = 3.14;

	int v = c.getValue();

	std::cout << "v: " << v << std::endl;

	return 0;
}
