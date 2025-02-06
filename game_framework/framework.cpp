// framework.cpp

#include <iostream>

#include "framework.h"

// Player class:

std::ostream &operator<<(std::ostream &os, const Player &p) {
	return os << "Spieler: [" << p.getName() << "], Punkte: [" << p.getScore() << "]";
}
