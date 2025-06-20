#include <iostream>
#include <string>
using std::cout, std::endl, std::string;
/*
struct X {
	mutable int y = 1, z = 2;
	void pretty_safe() const {
		y = z = 99;
	}
	friend std::ostream& operator<<(std::ostream &stream, const X &x) {
		stream << "X{y=" << x.y << ",z=" << x.z << "}";
		return stream;
	}
};

void foo(const X &x) {
	x.pretty_safe();
}
*/

int foo(int a, int b) {
	return a+b;
}

int main() {
// 	X x;
// 	foo(x);
// 	cout << x << endl;
	int aaa = 1;
	int bbb = 2;
	int ccc = foo(aaa,bbb); // INLINE könnte hier aaa+bbb draus machen
}
