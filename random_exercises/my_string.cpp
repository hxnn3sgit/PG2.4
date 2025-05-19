#include <iostream>
#include <cstring>

using namespace std;

class pg2_string {
private:
    char *data;
    int len;
public:
    pg2_string() : data(nullptr), len(0) {}
    pg2_string(char *input_data) {
        int counter = 0;
        while (input_data[counter] != '\0')
            counter++;

        // wich one is better?
        //data = (char*)malloc(sizeof(char) * counter + 1);
        data = new char [counter + 1]; 
        len = counter;
        memcpy(data, input_data, counter);
        data[counter] = '\0';
    }
    ~pg2_string() { delete [] data; len = 0; }

    int lenth() { return len; }
    void append(char *append_data);
    pg2_string substring(char c, int len);
    bool is_empty(const pg2_string &my_str);
    int find(char c);
    void clear();
    friend bool operator==(const pg2_string &str_1, const pg2_string &str_2);
    friend bool operator!=(const pg2_string &str_1, const pg2_string &str_2);
	friend ostream& operator<<(ostream &os, const pg2_string &my_str);
    pg2_string operator[](int index);
};

void pg2_string::append(char *append_data) {
	pg2_string temporary(append_data);
	int new_len = len + temporary.len + 1;
	char *new_data = new char [new_len]; // + 1 is already added in the original string
	for (int i = 0; i < len; ++i) {
		new_data[i] = data[i];
	}
	for (int i = len + 1, j = 0; i < new_len, j < temporary.len; ++i, ++j) {
		new_data[i] = append_data[j];
	}
	new_data[new_len+1] = '\0';
	data = new_data;
	len = new_len;
}

ostream& operator<<(ostream &os, const pg2_string &my_str) {
	for (int i = 0; i < my_str.len; ++i)
		os << my_str.data[i];
	return os;
}

int main() {
    // pg2_string first_str;
    pg2_string second_str("Hannes");
    cout << "second str: " << second_str << endl;
    //first_str = "Das ist ein Test";
    second_str.append(" das ist lustig");
	cout << "second str after appending: " << second_str << endl;
    //cout << first_str.substring("T", 3) << endl; // should return Tes
    


    return 0;
}

/*
to implement:
- copy constructor
- move constructor
- destructor
- copy assignment operator
- move assignment operator
- clear function
- append function
- substring function
- find function
- comparison functions ( ==, !=)
- access operator []
- concatenation operator
- stream operators
- empty check



*/
