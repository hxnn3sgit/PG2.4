#include <iostream>
#include <string>
#include <vector>

double noten_durchschnitt (const std::vector<double> &noten) {
	double avg = 0.0;
	for (const auto &note : noten) {
		avg += note;
	}

	return (avg / noten.size());
}

int main() {
	std::vector<double> noten = { 1.0, 2.3, 3.7, 1.7, 4.0 };
	double noten_avg = noten_durchschnitt(noten);

	std::cout << "noten durchschnitt: " << noten_avg << std::endl;

	auto zaehleNotenUeberDurchschnitt = [noten_avg, &noten]() {
		int counter = 0;
		for (const auto &note : noten) {
			if (note > noten_avg)
				counter++;
		}

		return counter;
	};

	std::cout << "noten über durchschnitt: " << zaehleNotenUeberDurchschnitt() << std::endl;

	return 0;
}

/*
int main() {
	int x = 10;
	int y = 20;

	
	{
		int x = 5;
		auto myLambda = [=,&x]() {
			x = 30;
			return x + y;
		};
	}
 
	 std::cout << myLambda() << std::endl;
	std::cout << "x, y: " << x << ", " << y << std::endl;


	return 0;
}
*/

