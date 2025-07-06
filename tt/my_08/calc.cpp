#include "calc.h"

bool math::syntax_check(const std::vector<Token> &calc_tokens) {
		Token::TokenType expected_token = Token::TokenType::NUMBER;

    if ((!calc_tokens[0].isNumber() || !calc_tokens[0].isVariable()) && calc_tokens.size() == 1) {
        return false;
    }

    for (int i = 0; i < calc_tokens.size(); ++i) {
		if (expected_token == Token::TokenType::NUMBER)
			expected_token = Token::TokenType::OPERATOR;
		else if (expected_token == Token::TokenType::OPERATOR)
			expected_token = Token::TokenType::NUMBER;
		else if (expected_token == Token::TokenType::VARIABLE)
			expected_token == Token::TokenType::OPERATOR;
		else	
			return false;
	}

	return true;
}

float math::simple_eval_ltr(const std::vector<Token> &tokens) {
	
	return 1.0;
}
