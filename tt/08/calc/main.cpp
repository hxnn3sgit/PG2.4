#include "token.h"
#include "calc.h"
#include <vector>
#include <iostream>

int main() {
	std::vector<token> tokens = tokenize(std::cin);

	for (int i = 0; i < tokens.size(); ++i)
		std::cout << tokens[i] << std::endl;

	if (syntax_check(tokens)) {
		std::cout << "Ergebnis: " << (float)simple_eval_ltr(tokens) << std::endl;
	}
}
