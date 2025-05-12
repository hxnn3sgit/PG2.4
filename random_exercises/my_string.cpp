#include <iostream>

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
    bool operator==(const pg2_string &str_1, const pg2_string &str_2);
    bool operator!=(const pg2_string &str_1, const pg2_string &str_2);
    pg2_string operator[](const pg2_string &str, int index);




};

int main() {
    pg2_string first_str;
    pg2_string second_str("Hannes");
    
    first_str = "Das ist ein Test";
    second_str.append(" das ist lustig");

    cout << first_str.substring("T", 3) << endl; // should return Tes
    


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