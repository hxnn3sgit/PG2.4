#pragma once

#include "tokenizer.h"

namespace math {
	bool syntax_check(const std::vector<Token> &calc_tokens);
	float simple_eval_ltr(const std::vector<Token> &tokens);
};
