#pragma once

#include "tokenizer.h"

class division_by_zero : public std::exception {
private:
	std::string message;
public:
	division_by_zero(const std::string &msg) : message(msg) {}
	const virtual char* what() {
		return message.c_str();
	}
};

namespace math {
	bool syntax_check(const std::vector<Token> &calc_tokens);
	float simple_eval_ltr(const std::vector<Token> &tokens);
};
