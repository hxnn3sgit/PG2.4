#include <iostream>

using namespace std;

int add(int a, int b) {
	int result = a + b;
	return result;
}

int multiply(int a, int b) {
	int result = a * b;
	return result;
}

int main() {

	cout << "hello petra" << endl;
	cout << add(1, 5) << endl;
	cout << multiply(2, 6) << endl;
	cout <<  "hello hannes" << endl;

	return 0;
}
