#include <iostream>
#include <string>
#include <string>
#include <cmath>
using std::cout, std::endl, std::string;

class complex_number {
	double real, imag;
public:
	complex_number(double real, double imag) : real(real), imag(imag) {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	static complex_number polar(double angle, double radius) {
		double real = radius*cos(angle);
		double imag = radius*sin(angle);
		cout << __PRETTY_FUNCTION__ << endl;
		return complex_number(real, imag);
	}
};
	
complex_number polar(double angle, double radius) {
	double real = radius*cos(angle);
	double imag = radius*sin(angle);
	cout << __PRETTY_FUNCTION__ << endl;
	return complex_number(real, imag);
}



int main() {
	complex_number pos(2.0f,3.0);
	complex_number pos2 = complex_number::polar(3.1415, 90);
	complex_number pos3 = polar(3.1415, 90);

}
