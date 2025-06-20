#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout, std::endl, std::string;

void check_if_valid_token_and_append(string &token, std::vector<string> &tokens) {
	// do logic if it is a valid token
	// logic if token is valid or not:
	// - the first character must me underscore, or alpha, if that is not the case we immediately
	//   can return false

	token.erase(std::remove_if(token.begin(), token.end(), [](char c) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');}), token.end());
	
	string cpp_token;

	if (! (isalpha(token[0]) || token[0] == '_'))
		return;
	else {
		int counter = 0; // start from second char
		
		while (isalnum(token[counter]) || token[counter] == '_') {
			cpp_token.push_back(token[counter]);
			++counter;
		}

		tokens.push_back(cpp_token);
	}
}

void get_tokens(std::istream &in, std::vector<string> &tokens) {
	string line;

	while (std::getline(in, line)) {
		std::istringstream iss(line);
		string token;
		
		while(std::getline(iss, token, ' ')) {
			check_if_valid_token_and_append(token, tokens);
		}	  
	}
		
}


int main(int argc, char **argv) {
	std::vector<string> tokens;
	
	if (argc > 2) {
		std::cerr << "please only one textfile or nothing to paste code in std::cin.";
		return EXIT_FAILURE;
	
	} else if (argc == 2) {
		// get filename and parse through file
		string filename = argv[1];
		std::ifstream f_in(filename);

		if (!f_in.is_open())
			std::cerr << "File not found!" << endl;
	
		get_tokens(f_in, tokens);
		cout << "Gefundene Bezeichner in Datei " << filename << ":" << endl;
		for (const auto &token : tokens)
			cout << "- " << token << endl;

	} else if (argc == 1) {
		// parse through std::cin
		get_tokens(std::cin, tokens);
		cout << "Gefundene Bezeichner:" << endl;	
		for (const auto &token : tokens)
			cout << "- " << token << endl;
	}
	
	return 0;
}
