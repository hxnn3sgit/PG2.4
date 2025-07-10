#include "calc.h"
#include "expression_tree.h"

#include <string>

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
			expected_token = Token::TokenType::OPERATOR;
		else	
			return false;
	}

	return true;
}

void calc_value(float &lhs, Token op, Token rhs) {
	float lhs_value = lhs;
	float rhs_value = rhs.getValue();
	char calc_op = op.getOperator();

	switch(calc_op) {
		case '+':
			lhs = lhs_value + rhs_value;
			break;
		case '-':
			lhs = lhs_value - rhs_value;
			break;
		case '*':
			lhs = lhs_value * rhs_value;
			break;
		case '/':
			if (rhs_value == 0)
				throw division_by_zero("cannot divide by zero");
			else
				lhs = lhs_value / rhs_value;
				break;
		default:
			throw std::logic_error("invalid calc operator: " + calc_op); 
	}
}

float math::simple_eval_ltr(const std::vector<Token> &tokens) {
	float result = tokens[0].getValue();
	calc_value(result, tokens[1], tokens[2]);

	for (int i = 3; i < tokens.size() - 1; i += 2) {
		calc_value(result, tokens[i], tokens[i+1]);
	}

	return result;
}

float math::proper_eval(const std::vector<Token> &tokens) {
	expressionTree tree;
	expressionTree *my_tree = tree.build_expression_tree(tokens);

	return 0.0;
}