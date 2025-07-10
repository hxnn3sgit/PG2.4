#include <iostream>
#include <fstream>
#include <sstream>
#include "tokenizer.h"
#include "calc.h"
#include "expression_tree.h"

// new main aufgabe 4: /
int main(int argc, char **argv) {

	
	std::string line;
	while(std::getline(std::cin, line)) {
		std::istringstream iss(line);
		std::string iss_line;
		while (std::getline(iss, iss_line, ';')) {
			std::istringstream single_token_stream(iss_line);
			std::vector<Token> calc_tokens;
			try {
				calc_tokens = tokenize(single_token_stream);
			} catch (std::invalid_argument &e) {
				std::cerr << "exception during tokenizing: " << e.what() << std::endl;
				continue;
			}

			if (math::syntax_check(calc_tokens)) {
				try {
					float result = math::proper_eval(calc_tokens);
					std::cout << "[LOGGER:] result: " << result << "; ";
				} catch (division_by_zero &e) {
					std::cerr << "exception occured, skipping: " << e.what() << std::endl;
				} catch (std::logic_error &e) {
					std::cerr << "exception occured, skipping: " << e.what() << std::endl;
				}
			} else {
				std::cerr << "[ERROR:] syntax was wrong\n";
			}
		}	
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}