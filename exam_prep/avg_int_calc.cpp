#include <iostream>
#include <string>

using std::cout, std::endl, std::string;

// ich würde hier gar kein array anlegen, einfach die summe aller zahlen über std::cin berechnen und dann durch die anzahl teilen, aber in der aufgabe ist was anderes beschrieben
double average(std::istream &in, int n) {
	string line;
	int *arr = new int[n];
	
	for (int i = 0; i < n; ++i) {
		int number = 0;
		std::getline(in, line);
		try {
			number = std::stoi(line);
		} catch (std::invalid_argument &e) {
			std::cerr << "conversion failed: " << e.what() << endl;
			continue;
		} catch (std::out_of_range &e) {
			std::cerr << "conversion failed: " << e.what() << endl;
			continue;
		}
		arr[i] = number;
	}
	
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += arr[i];
	}

	delete [] arr;

	return float(sum / n);
}

int main() {
	int n = 10;
	float avg = average(std::cin, n);
	cout << "avg(10 numbers): " << avg << endl;

	return 0;
}
