#include <iostream>
#include <cctype>

#include "tokenizer.h"

std::ostream& operator<<(std::ostream& out, const Token &other) {
	if (other.Type == Token::TokenType::NUMBER)
		out << "Token{NUMBER:" << other.Value << "}";
	else if (other.Type == Token::TokenType::OPERATOR)
		out << "Token{OP:" << other.Op << "}";
	else if (other.Type == Token::TokenType::VARIABLE)
		out << "Token{VAR:" << other.VariableName << "}";

	return out;
}

bool is_operator(char c) {
	if(c == '+' || c == '-' || c == '/' || c == '*')
		return true;
	else
		return false;

	// könnte ich auch schreiben?:
	// return (c == '+' || c == '-' || c == '/' || c == '*');
}

std::vector<Token> tokenize(std::istream &in) {
	int var;
	char op;
	std::string var_name;

	std::vector<Token> tokens;
	char current_token_c;

	while (current_token_c = in.get()) {
		// main loop, goes through input stream, char by char, building tokens an appending them to arr
		std::string token;
		if (isdigit(current_token_c)) { 
			token.push_back(current_token_c);
			while (isdigit( (current_token_c = in.get()) )) // as long as c is a number, get c and push back it to token
				token.push_back(current_token_c);

			int num_token = std::stoi(token);
			Token numeric_token(num_token);
			tokens.push_back(numeric_token);
				
		} else if (is_operator(current_token_c)) {
			Token op_token(current_token_c);
			tokens.push_back(op_token);
		} else if (isalpha(current_token_c)) {
			// variables:
			
		} else {
			throw invalid_char();
		}


	}


	return tokens;
}