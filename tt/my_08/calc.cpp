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

float calc_value(Token lhs, Token op, Token rhs) {
	float lhs_value = lhs.getValue();
	float rhs_value = rhs.getValue();
	char calc_op = op.getOperator();

	switch(calc_op) {
		case '+':
			return lhs_value + rhs_value;
		case '-':
			return lhs_value - rhs_value;
		case '*':
			return lhs_value * rhs_value;
		case '/':
			if (rhs_value == 0)
				throw division_by_zero("cannot divide by zero");
		default:
			throw std::logic_error("invalid calc operator"); 
	}


}

float math::simple_eval_ltr(const std::vector<Token> &tokens) {
	float result = 0.0;
	for (int i = 0; i < tokens.size() - 2; ++i) {
		result += calc_value(tokens[i], tokens[i+1], tokens[i+2]);
	}

	return result;
}
