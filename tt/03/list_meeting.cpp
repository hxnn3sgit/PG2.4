#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

struct name_node {
public:
    string vorname, nachname;
	struct name_node *next;
public:
	name_node() : vorname(""), nachname(""), next(nullptr) {}
    name_node(string vorname, string nachname) : vorname(vorname), nachname(nachname), next(nullptr) {}
};

class name_list {
private:
    name_node data;
    name_node *head;
public:
    name_list() : head(nullptr) {}
    //~name_list() { // go through list, delete everything };
    // name_node create_node(string vorname, string nachname); // "helper"
    void append_teilnehmer(char *arg);
    int len();
    friend ostream& operator<<(ostream& os, const name_list &my_list);
	friend void teilnehmer(const name_list &my_list);
};

vector<string> split_names(char *arg);

void name_list::append_teilnehmer(char *arg) {
    // to do:
    // - create a name node
    // - go to end of list
    // - end of list is the new created node
	
	vector<string> vor_und_nachname = split_names(arg);
	
	name_node *new_name_node = new name_node(vor_und_nachname[0], vor_und_nachname[1]);
	name_node *run = head;

	if (head == nullptr) { 
		head = new_name_node;
	} else {
		while(run->next != nullptr) { // wtf
			run = run->next; // wtf
		}
		run->next = new_name_node;
	}
}

vector<string> split_names(char *arg) {
	vector<string> splitted_name;
	stringstream ss(arg);
	string token;
	while (ss >> token)
		splitted_name.push_back(token);
	return splitted_name;
}

void teilnehmer(name_list &my_list) {
    // iterate through list (maybe custom iterator class) -> later
    // print Hello and vorname from every node

	name_node *run = my_list.head;

	while (run) {
		cout << "Hallo " << run->vorname << endl;
	}
	
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Keine Namen übergeben. Programm beenden..." << endl;
        return -1;
    }
    
    name_list my_list;
    for(int i = 1; i < argc; ++i) {
        my_list.append_teilnehmer(argv[i]);
    }
    
    //cout << my_list << endl;
    //teilnehmer(my_list);
    return 0;
} 

/*name* create_name_array(int argc, char **argv) {
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
}*/
