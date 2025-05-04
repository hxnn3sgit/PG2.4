#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

struct name {
	string vorname, nachname;
};

name* create_name_array(int argc, char **argv) {
	int size = argc - 1;
	name *my_names = new name[size];

	for (int i = 1; i < argc; ++i) { 
		stringstream ss(argv[i]);
		string token;
		vector<string> name_tokens;
		while (ss >> token) {
			name_tokens.push_back(token);
		}
		my_names[i-1].nachname = name_tokens[1];
		my_names[i-1].vorname = name_tokens[0];
	}

	return my_names;
}

void teilnehmer(const name *my_names, int size) {
	for (int i = 0; i < size; ++i) {
		if (my_names[i].vorname == "Brijnesh" && my_names[i].nachname == "Jain")
			cout << "Hallo bj" << endl;
		else
			cout << "Hallo " << my_names[i].vorname << endl;
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cerr << "Keine Namen übergeben. Programm beenden..." << endl;
		return -1;
	}

	name *my_names = create_name_array(argc, argv);
	int size = argc - 1;
	teilnehmer(my_names, size);
	return 0;
}
