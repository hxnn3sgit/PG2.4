#include <iostream>

namespace raum1 {
	void say_hello() {
		std::cout << "Hello from raum1" << std::endl;
	}
}

namespace raum2 {
	void say_hello() {
		std::cout << "Hello from raum2" << std::endl;
	}
}

int main() {
	raum1::say_hello();
	raum2::say_hello();

	return 0;
}
