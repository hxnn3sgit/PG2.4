#include <iostream>
#include <fstream>
#include "tokenizer.h"
#include "calc.h"

int main(int argc, char **argv)  {
	std::vector<Token> my_tokens;
    try {
        std::fstream fin("to_calc");
        my_tokens = tokenize(fin);
		for (const auto &token : my_tokens) {
			std::cout << token << std::endl;
		}
    } catch (invalid_char &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    }

	if (math::syntax_check(my_tokens)) {
		std::cout << "[LOGGER]: syntax check successful.\n";
		float result = math::simple_eval_ltr(my_tokens);
		std::cout << "[LOGGER]: Result: " << result << std::endl;
	} else {
		std::cerr << "[ERROR]: syntax check failed!\n";
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
