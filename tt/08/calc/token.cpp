#include "token.h"
#include <string>

using std::string, std::cout, std::endl;

bool is_operator(char c) {
	switch (c) {
	case '*': case '+': case '-': case '/': case '%': return true;
	default: return false;
	}
}

std::vector<token> tokenize(std::istream &input) {
	std::vector<token> tokens;

	int ival;
	char opval;
	string varval;

	while (true) {
		char current = input.get();
		if (input.eof())
			break;
		if (isspace(current))
			continue;
		if (isdigit(current)) {
			int number;
			input.putback(current);
			input >> number;
			tokens.push_back(token(number));
		}
		else if (is_operator(current)) {
			cout << "Parsed operator " << current << endl;
			tokens.push_back(token(current));
		}
		else if (isalpha(current)) {
			string accum(1, current);
			while (true) {
				current = input.get();
				if (input.eof())
					break;
				if (isalnum(current))
					accum += current;
				else {
					input.putback(current);
					break;
				}
			}
			cout << "Parsed name " << accum << endl;
			tokens.push_back(token(accum));
		}
		else {
			cout << "Unparsed: " << current << endl;
		}
	}

	return tokens;
}
