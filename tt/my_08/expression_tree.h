#pragma once

#include <iostream>
#include <vector>

#include "calc.h"
#include "tokenizer.h"

class expressionTree {
public:
    struct Node {
        int value;
        std::string var;
        char op;
		Node *left;
		Node *right;

        Node () = default;
        Node (int v) : value(v),var(""), left(nullptr), right(nullptr) {} // if is a value
        Node (const std::string &v) : value(0), var(v), left(nullptr), right(nullptr) {} // if is variable
        Node (const char o) : value(0), var(""), op(o), left(nullptr), right(nullptr) {} // if is operator
    };
	Node *root;
public:
    //expressionTree()
    expressionTree() : root(nullptr) {};
    ~expressionTree(); //deletes the whole tree
    expressionTree* build_expression_tree(const std::vector<Token> &tokens); // constructs the tree and returns a pointer to the start
    
    friend std::ostream& operator<<(std::ostream &out, const expressionTree &other);
};
