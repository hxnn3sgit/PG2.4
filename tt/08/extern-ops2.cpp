#include <iostream>
#include <string>
#include <string>
using std::cout, std::endl, std::string;

//  aus 07/string: operator^ für strings
//  können wir das auch für std::string machen?

string operator^(const string &str, int exp) {
	string res;
	for (int i = 0; i < exp; ++i)
		res += str;
	return res;
}

int main(int argc, char **argv) {
	string str = argv[1];
	int exp = atoi(argv[2]);
// 	string res;
// 	for (int i = 0; i < exp; ++i)
// 		res += str;
// 	cout << res << endl;

	cout << (str^exp) << endl;
}
