#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

struct name_node {
private:
	string vorname, nachname;
public:
	name_node(string vorname, string nachname) : vorname(vorname), nachname(nachname) {}
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

class name_list {
private:
	name_node *head;;
public:
	name_list() : head(nullptr) {}
	name_list(string vorname, string nachname);
	~name_list();
	// name_node create_node(string vorname, string nachname); // "helper"
	void append_node(name_node my_node);
	int len();
}

name_list::name_list(string vorname, string nachname) {
	head = create_node(vorname, nachname);
	head->next = nullptr;
}



name_node* name_list::create_node(string vorname, string nachname) {
	name_node *new_name_node = new name_node;
	new_name_node.vorname = vorname;
	new_name_node.nachname = nachname;
	return new_name_node;
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
