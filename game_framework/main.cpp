#include <iostream>

#include "framework.h"

using std::cout, std::endl;

int main() {
	Player p1("Hannes");

	p1.addPoints(10);
	
	cout << p1 << endl;	
	
	p1.resetScore();

	cout << "after reset score: " << p1 << endl;

	return 0;
}
