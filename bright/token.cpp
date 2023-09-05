#include "tokenType.hpp"
#include <string>
#include <iostream>

using namespace std;

class Token {
public:

    TokenType type;
    string lexeme;
    string literal;
    int line; 

    Token(TokenType type, string lexeme, auto literal, int line) {
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }

    string toString() {
        return type + " " + lexeme + " " + literal;
    }
};