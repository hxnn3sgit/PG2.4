#include <string>
#include <iostream>
#include <exception>
#include <vector>

class Token {
    enum class TokenType { NUMBER, OPERATOR, VARIABLE };
    TokenType Type;
    int Value = 0;
    char Op = '\0';
    std::string VariableName;
public:
    Token() = delete;
    Token(const int number) : Value(number), Type(TokenType::NUMBER) {}
    Token(const char op) : Op(op), Type(TokenType::OPERATOR) {}
    Token(const std::string varName) : VariableName(varName), Type(TokenType::VARIABLE) {}

    friend std::ostream& operator<<(std::ostream &out, const Token &other);
};

class invalid_char : public std::exception {
public:
    virtual const char *what() const noexcept {
		return "Invalid character recognized";
	}
};

std::vector<Token> tokenize(std::istream &in);