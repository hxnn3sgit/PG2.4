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
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

std::vector<Token> tokenize(std::istream &in) {
	int var;
	char op;
	std::string var_name;

	std::vector<Token> tokens;
	char current_token_c;

	while (in.get(current_token_c)) {
		// main loop, goes through input stream, char by char, building tokens an appending them to arr
		std::string token;
		if (isdigit(current_token_c)) { 
			in.putback(current_token_c);
			int number;
			in >> number;
			Token numeric_token(number);
			tokens.push_back(numeric_token);
		} else if (is_operator(current_token_c)) {
			Token op_token(current_token_c);
			tokens.push_back(op_token);
		} else if (isalpha(current_token_c) || current_token_c == '_') {
			// variables:
			token.push_back(current_token_c);
			while ( current_token_c = in.get()) {
				if (isalpha(current_token_c) || current_token_c == '_') {
					token.push_back(current_token_c);
				} else {
					in.putback(current_token_c);
					break;
				}	
			}
			Token varname_token(token);
			tokens.push_back(varname_token);
		} else if (isspace(current_token_c)) {
			continue;
		}
		 else {
			throw std::invalid_argument("invalid character skipping this term: " + std::string(1, current_token_c));
			
		}
	}

	return tokens;
}
