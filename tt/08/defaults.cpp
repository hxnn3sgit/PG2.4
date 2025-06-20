#include <iostream>
#include <string>
using std::cout, std::endl, std::string;

struct X {
	int y = 1, z = 2;
	X() : y(2) {}
	X(int a) : z(a) {}
};

int main() {
	X x(22);
	cout << x.y << endl;
	cout << x.z << endl;
}
