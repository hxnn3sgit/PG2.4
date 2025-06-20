#include <iostream>

enum Berechtigungen : unsigned int {
	Keine = 0,
	Lesen = 1 << 0,
	Schreiben = 1 << 1,
	Ausfuehren = 1 << 2
};

inline Berechtigungen operator&(Berechtigungen lhs, Berechtigungen rhs) {
	unsigned int underlying_lhs = static_cast<unsigned int>(lhs);
	unsigned int underlying_rhs = static_cast<unsigned int>(rhs);

	unsigned int result_as_int = underlying_lhs & underlying_rhs;

	return static_cast<Berechtigungen>(result_as_int);
}

inline Berechtigungen operator|(Berechtigungen lhs, Berechtigungen rhs) {
	unsigned int underlying_lhs = static_cast<unsigned int>(lhs);
	unsigned int underlying_rhs = static_cast<unsigned int>(rhs);

	unsigned int result_as_int = underlying_lhs | underlying_rhs;

	return static_cast<Berechtigungen>(result_as_int);
}

inline Berechtigungen& operator|=(Berechtigungen& lhs, Berechtigungen rhs) {
	lhs = lhs | rhs;
	return lhs;
}

inline Berechtigungen& operator&=(Berechtigungen& lhs, Berechtigungen rhs) {
	lhs = lhs & rhs;
	return lhs;	
}

bool HatRecht(Berechtigungen meine_rechte, Berechtigungen zu_pruefendes_recht) {
	return (meine_rechte & zu_pruefendes_recht) == zu_pruefendes_recht;
}

int main() {
	Berechtigungen meine_rechte = Berechtigungen::Ausfuehren;
	
	// prüfen, ob lesen-recht gesetzt ist:
	if (HatRecht(meine_rechte, Berechtigungen::Lesen))
		std::cout << "lesen recht ist gesetzt" << std::endl;

	if (HatRecht(meine_rechte, Berechtigungen::Ausfuehren))
		std::cout << "ausführen recht ist gesetzt" << std::endl;

	return 0;
}
