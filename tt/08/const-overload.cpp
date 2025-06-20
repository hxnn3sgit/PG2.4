#include <iostream>
using std::cout, std::endl;

// konstruiert und nicht "guter stil" weil die operatoren ganz andere sachen machen
class thing {
	int x;
public:

	void operator()(int a, int b) {
		cout << __PRETTY_FUNCTION__ << endl;
		x = a + b;
	}
	
	int operator()(int a, int b) const {
		cout << __PRETTY_FUNCTION__ << endl;
		return x + a + b;
	}
};

void foo(thing &x) {
	x(1, 2);
}

void bar(const thing &x) {
	x(1, 2);
}

int main() {
	thing t;
	foo(t);
	bar(t);
	t(2,3);
}
