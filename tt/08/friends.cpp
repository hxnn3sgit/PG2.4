#include <iostream>
#include <string>
#include <string>
using std::cout, std::endl, std::string;

class rational {
	int n, d;
public:
	rational(int n, int d) : n(n), d(d) {}
	
	// KEINE memberfunkion
	friend rational operator*(const rational &a, const rational &b) {
		return rational(a.n * b.n, a.d * b.d);
	}

	// recap reihenfolge:
	friend rational operator*(const rational &r, int factor) { return rational(r.n*factor, r.d); }
	friend rational operator*(int factor, const rational &r) { return rational(r.n*factor, r.d); }

	friend std::ostream& operator<<(std::ostream &stream, const rational &r) {
		stream << r.n << "/" << r.d;
		return stream;
	}
};




int main() {
	rational x(1,2), y(1,4);
	rational z = 2 * x * y;

	cout << z << endl;
}

