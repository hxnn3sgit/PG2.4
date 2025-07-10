#include <stack>

#include "expression_tree.h"

// wenn auf stack * oder / liegt und current_op +, -; hat das höhere Berechtigung als +, - -> true
// wenn auf stack * oder / liegt und current_op *, /; hat das gleiche berechtigung -> true
// wenn auf stack + oder - liegt und current_op *, /; hat +, - niedrigere berechtigung -> false
// wenn auf stack + oder - liegt und current_op +, -; hat das gleiche Berechtigung -> true
bool has_higher_or_equal_prio(const char top_stack_element, const char current_op) {
	if ( (top_stack_element == '+' || top_stack_element == '-') && (current_op == '*' || current_op == '/') )
		 return false;
	else
		return true;
}

expressionTree::Node* get_top_element(std::stack<expressionTree::Node*> &value_stack) {
    auto top_element = value_stack.top();
    value_stack.pop();
    return top_element;
}

expressionTree::Node get_top_element(std::stack<expressionTree::Node> &operator_stack) {
    auto top_element = operator_stack.top();
    operator_stack.pop();
    return top_element;
}

expressionTree* expressionTree::build_expression_tree(const std::vector<Token> &tokens) {
	std::stack<expressionTree::Node> operator_stack;
	std::stack<expressionTree::Node*> value_stack;
	expressionTree *new_expr_tree = new expressionTree();

    for (const auto &token : tokens) {
    	if (token.isNumber()) {
			expressionTree::Node *value_node = new expressionTree::Node(token.getValue());
			value_stack.push(value_node);
		} else if (token.isOperator()) {
			char current_op = token.getOperator();
            expressionTree::Node top_stack_op;
            if (!operator_stack.empty())
			    top_stack_op = get_top_element(operator_stack);
			while (!operator_stack.empty() && has_higher_or_equal_prio(top_stack_op.op, current_op)) {
				// build the tree

                expressionTree::Node to_calc_op_node = get_top_element(operator_stack);
				expressionTree::Node *right_value_node = get_top_element(value_stack);
				expressionTree::Node *left_value_node = get_top_element(value_stack);

                expressionTree::Node *operator_node;
                operator_node->right = right_value_node;
                operator_node->left = left_value_node;

                value_stack.push(operator_node);
               
			}
            // process remaining tokens in stack:
            // - push the tokens
          

		}
	}

    return nullptr;
	// return value_stack.top(); // sollte root node des expr trees returnen, keine referenz, da .pop() eine referenz returnt
}

expressionTree::~expressionTree() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
