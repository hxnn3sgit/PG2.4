#include <iostream>

class Rechteck {
	int breite;
	int höhe;
public:
	Rechteck(const int b, const int h) : breite(b), höhe(h) {}
	Rechteck(const int s) : Rechteck(s, s) {}
	Rechteck() : Rechteck(1) {}
	//rule of 3/5 wird ignoriert, bräuchte ich es hier? soll ich den default ctor explicit setzen?
	int fläche() const { return breite * höhe; }


	friend std::ostream& operator<<(std::ostream& out, const Rechteck &other);
};

std::ostream& operator<<(std::ostream& out, const Rechteck &other) {
	return ( out << "Rechteck Breite: " << other.breite << ", Höhe: " << other.höhe );
}

int main() {
	std::cout << Rechteck(4, 7).fläche() << std::endl;

	return 0;
}
