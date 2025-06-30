#include <iostream>

#include "tokenizer.h"

int main(int argc, char **argv)  {
    try {
        std::vector<Token> my_tokens = tokenize(std::cin);
    } catch (invalid_char &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    }
    


    return 0;
}