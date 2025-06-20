#pragma once

#include <vector>
#include <iostream>
#include <string>

class token {
public:
	enum kind { number, op, varname }; // try@home: enum class
	enum kind kind;
	int int_value;
	std::string name;
public:
	token() = delete;
	token(int val)  : kind(number), int_value(val) {}
	token(char val) : kind(op), name(1,val) {}
	token(const std::string &val) : kind(varname), name(val) {}

	friend std::ostream& operator<<(std::ostream &stream, const token &t) {
		stream << "token{";
		if (t.kind == token::number) stream << t.int_value;
		else stream << t.name;
		stream << "}";
		return stream;
	}
};

std::vector<token> tokenize(std::istream &input);