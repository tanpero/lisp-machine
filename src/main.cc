#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>
#include "mman.h"

enum class TokenType {
    Number, Symbol, String, OpenParen, CloseParen
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(value) {}
};

static bool isValidSymbol(char c) {
    return std::isgraph(c) && c != '(' && c != ')' && c != '"';
}

class Lexer {
    size_t position = 0;
    size_t size;

    std::string source;
    std::vector<Token> tokens;

    size_t parenLevels = 0;

public:
    Lexer(std::string source) : source(source), size(source.size()), tokens({}) {}

    std::vector<Token> tokenize();

private:

    Token getNumber() {
        return { TokenType::Number, readNumber(source, position) };
    }

    Token getString() {
        return { TokenType::String, readString(source, position) };
    }

    Token getIdentifier() {
        return { TokenType::Symbol, readIdentifier(source, position) };
    }

private:

    std::string readNumber(const std::string& str, size_t& start) {

        size_t i = start;

        std::string result;

        if (str[i] == '-') {
            result += '-';
            ++i;
        }

        while (std::isdigit(str[i])) {
            result += str[i];
            ++i;
        }

        if (str[i] == '.')
        {
            result += str[i];
            ++i;
        }

        while (std::isdigit(str[i])) {
            result += str[i];
            ++i;
        }

        start = i;

        return result;
    }


    std::string readString(const std::string& str, size_t& start) {

        std::string result;
        size_t i = start + 1;

        while (i < str.length()) {
            char currentChar = str[i];

            if (currentChar == '\\' && i + 1 < str.length()) {
                char nextChar = str[i + 1];
                switch (nextChar) {
                case 'n':
                    result += '\n';
                    break;
                case 't':
                    result += '\t';
                    break;
                default:
                    result += nextChar;
                    break;
                }
                i += 2;
            }
            else if (currentChar == '\"') {
                ++i;
                break;
            }
            else {
                result += currentChar;
                ++i;
            }
        }

        start = i;

        return result;
    }

    std::string readIdentifier(const std::string& str, size_t& start) {

        size_t i = start;
        std::string identifier;


        while (isValidSymbol(str[i])) {
            identifier += str[i];
            ++i;
        }

        start = i;

        return identifier;
    }

};


#define current source[position]

std::vector<Token> Lexer::tokenize()
{
    while (position < size) {
        if (std::isblank(current) || current == '\n') {
            while (std::isblank(current) || current == '\n')
            {
                position++;
            }
        }
        else if (current == '(')
        {
            tokens.push_back({ TokenType::OpenParen, "("});
            position++;
        }
        else if (current == ')')
        {
            tokens.push_back({ TokenType::CloseParen, ")" });
            position++;
        }
        else if (current == '-')
        {
            if (std::isdigit(source[position + 1]))
            {
                tokens.emplace_back(getNumber());
            }
            else
            {
                tokens.emplace_back(getIdentifier());
            }
        }
        else if (isValidSymbol(current) && !isdigit(current))
        {
            tokens.emplace_back(getIdentifier());
        }
        else if (std::isdigit(current))
        {
            tokens.emplace_back(getNumber());
        }
        else if (current == '"')
        {
            tokens.emplace_back(getString());
        }
        else
        {
            std::cerr << "Unexpected character: \"" << current << "\"\n\n";
            exit(-1);
        }
    }
    return tokens;
}

#undef current
















int main() {

    auto tokens = Lexer(R"((define f x (x))
    (+ "Hello" -1.5)
)").tokenize();

    for (auto t : tokens) std::cout << t.value << "\n";

    return 0;
}
