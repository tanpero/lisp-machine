#ifndef _LEXER_HH_
#define _LEXER_HH_

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>

enum TokenType {
    Number, Symbol, String, Boolean, OpenParen, CloseParen
};



struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(value) {}
};


class Lexer {
public:
    Lexer(std::string source) :
        source(source), position(0), size(source.size()), tokens({}), parenLevels(0) {};
    std::vector<Token> tokenize();

private:
    size_t position;
    size_t size;
    std::string source;
    std::vector<Token> tokens;
    size_t parenLevels;

    Token getNumber();
    Token getString();
    Token getSymbol();

    std::string readNumber(const std::string& str, size_t& start);
    std::string readString(const std::string& str, size_t& start);
    std::string readSymbol(const std::string& str, size_t& start);
};

#endif // !_LEXER_HH_
