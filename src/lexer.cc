#include "lexer.hh"


static bool isValidSymbol(char c) {
    return std::isgraph(c) && c != '(' && c != ')' && c != '"';
}

Token Lexer::getNumber() {
    return { TokenType::Number, readNumber(source, position) };
}

Token Lexer::getString() {
    return { TokenType::String, readString(source, position) };
}

Token Lexer::getSymbol() {
    return { TokenType::Symbol, readSymbol(source, position) };
}

std::string Lexer::readNumber(const std::string& str, size_t& start) {

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


std::string Lexer::readString(const std::string& str, size_t& start) {

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

std::string Lexer::readSymbol(const std::string& str, size_t& start) {

    size_t i = start;
    std::string identifier;


    while (isValidSymbol(str[i])) {
        identifier += str[i];
        ++i;
    }

    start = i;

    return identifier;
}


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
            tokens.push_back({ TokenType::OpenParen, "(" });
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
                tokens.emplace_back(getSymbol());
            }
        }
        else if (isValidSymbol(current) && !isdigit(current))
        {
            if (current == '#')
            {
                if (source[position + 1] == 't') {
                    tokens.push_back(Token{ TokenType::Boolean, "t" });
                    position += 2;
                    continue;
                }
                else if (source[position + 1] == 'f')
                {
                    tokens.push_back(Token{ TokenType::Boolean, "f" });
                    position += 2;
                    continue;
                }
            }
            tokens.emplace_back(getSymbol());
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



