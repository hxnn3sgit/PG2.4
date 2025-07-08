#include <iostream>
#include <vector>

#include "calc.h"
#include "tokenizer.h"

class expressionTree {
private:
    struct Node {
        int value;
        std::string var;
        char op;
        Node (int v) : value(v),var("") {} // if is a value
        Node (const std::string &v) : value(0), var(v) {} // if is variable
        Node (const char o) : value(0), var(""), op(o) {} // if is operator
    };
    Node *left_node;
    Node *right_node;
public:
    //expressionTree()
    expressionTree() : left_node(nullptr), right_node(nullptr) {};
    ~expressionTree(); // deletes the whole tree
    expressionTree* build_expression_tree(const std::vector<Token> &tokens); // constructs the tree and returns a pointer to the start
    
    friend std::ostream& operator<<(std::ostream &out, const expressionTree &other);
};

expressionTree* expressionTree::build_expression_tree(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        std::cout << token << std::endl;
        // if (token.isNumber())

    }
}