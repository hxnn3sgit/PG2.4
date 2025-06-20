#include <iostream>
using std::cout, std::endl, std::cin;

int add_n(int x, int add) {
	return x+add;
}

// klasse tut als wäre sie eine funktion "mit zustand"
class add {
	int to_add;
public:
	add(int to_add) : to_add(to_add) {}
	int operator()(int in) {
		return in + to_add;
	}
};

int main(int argc, char **argv) {
// 	int add = atoi(argv[1]);
// 	while (cin) {
// 		int x;
// 		cin >> x;
// 		cout << add_n(x, add) << endl;
// 	}
	add add_n = atoi(argv[1]);
	while (cin) {
		int x;
		cin >> x;
		cout << add_n(x) << endl;
	}
}
