#include <iostream>
#include <cstring>
#include <cassert>

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
    pg2_string substring(char c, int length);
    bool is_empty(const pg2_string &my_str);
    int find(char c);
    void clear();
    friend bool operator==(const pg2_string &str_1, const pg2_string &str_2);
    friend bool operator!=(const pg2_string &str_1, const pg2_string &str_2);
	friend ostream& operator<<(ostream &os, const pg2_string &my_str);
    pg2_string operator[](int index);
};

void pg2_string::clear() {
	delete [] data;
	len = 0;
}

int pg2_string::find(char c) {
	for (int i = 0; i < len; ++i) {
		if (data[i] == c)
			return i;
	}
	return -1;
}

bool operator==(const pg2_string &str_1, const pg2_string &str_2) {
	if (str_1.len != str_2.len)
		return false;
	for (int i = 0; i < str_1.len; ++i) {
		if (str_1.data[i] != str_2.data[i])
			return false;
	}

	return true;
}

// my function:
void pg2_string::append(char *append_data) {
	pg2_string temporary(append_data);
	int new_len = len + temporary.len;
	char *new_data = new char [new_len + 1]; // + 1 is already added in the original string
	
	for (int i = 0; i < len; ++i) {
		new_data[i] = data[i];
	}
	
	for (int j = 0; j < temporary.len; ++j) {
		new_data[len + j] = temporary.data[j]; // copy from pg2_string, it is safer
	}
	
	new_data[new_len] = '\0';
	
	delete[] data; // delete old data to ensure behaving
	data = new_data;
	len = new_len;
}

pg2_string pg2_string::substring(char c, int length) {
	assert(length < len); // data.len has to be bigger than substring length
	
	int counter = 0;
	while (data[counter] != '\0') {
		if(data[counter] == c)
			break;
		counter++;
	}

	if (counter == len) // means starting character is not in there
		return pg2_string("nix_gefunden");

	char *temp = new char[counter];
	for (int i = 0; i < length; ++i) {
		temp[i] = data[counter+i];
	}

	pg2_string substr(temp);
	delete [] temp;	
	return substr;
}	

ostream& operator<<(ostream &os, const pg2_string &my_str) {
	for (int i = 0; i < my_str.len; ++i)
		os << my_str.data[i];
	return os;
}

int main() {
    // pg2_string first_str;
    pg2_string first_str("Das ist ein Test");
    pg2_string second_str("Hannes");
	cout << "first_str: " << first_str << endl;
	cout << "second_str: " << second_str << endl;
  
	//cout << first_str.substring('T', 3) << endl;
	second_str.append(" du bist lustig");
	cout <<  second_str << endl;
	cout << "first_str.find('a'): " << first_str.find('a') << endl;
	first_str.clear();
	cout << "first_str after clear: " << first_str << endl;

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
- append function *
- substring function *
- find function
- comparison functions ( ==, !=)
- access operator []
- concatenation operator
- stream operators
- empty check



*/
