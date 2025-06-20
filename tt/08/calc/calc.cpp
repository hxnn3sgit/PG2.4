#include "calc.h"
#include "token.h"
#include <cassert>

bool syntax_check(const std::vector<token> &tokens) {
    if (tokens.empty() || tokens.size() == 1)
        return false;

    bool current_state = true;
    if (!( (tokens[0].kind == token::number) || tokens[0].kind == token::varname) && 
           (tokens[tokens.size()-1].kind == token::number || tokens[tokens.size()-1].kind == token::varname) )  { // if not number: return false
        return false;
    }
    
     // true = number/varname, false = op
    for (const auto &token: tokens) {
        if (current_state == true && (token.kind == token::number || token.kind == token::varname)) { // token soll nummer/varname sein
            current_state = false; // nächstes token wird auf false gesetzt um auf op hinzuweisen
        } else if (current_state == false && token.kind == token::op) {
            current_state = true; // nächstes token 
        } else {
            return false; 
        }
    }
}

int apply_operator(const int left_number, const char op, const int right_number) {
    switch (op) {
        case '+': return left_number + right_number;
        case '-': return left_number - right_number;
        case '*': return left_number * right_number;
        case '/': assert(right_number != 0);   return left_number / right_number;
    }
} 

int simple_eval_ltr(const std::vector<token> &tokens) {
    int result;
    if (tokens[0].kind == token::number)
        result = tokens[0].number;
    
    for (int i = 1 ; i < tokens.size(); ++i) {
        result += apply_operator(result, tokens[i].op, tokens[i+1].number);
    }

    return result;

}