#include <iostream>
#include <fstream>
#include "tokenizer.h"

int main(int argc, char **argv)  {
    try {
        
        std::fstream fin("to_calc");
        std::vector<Token> my_tokens = tokenize(fin);
		for (const auto &token : my_tokens) {
			std::cout << token << std::endl;
		}
    } catch (invalid_char &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    }

    return 0;
}
