#include <string>
#include <vector>

#include "token.h"

bool syntax_check(const std::vector<token> &tokens);

int simple_eval_ltr(const std::vector<token> &tokens);