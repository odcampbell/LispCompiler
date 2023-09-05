#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "token.cpp"
#include "tokenType.hpp"


using namespace std;

class Scanner {
private:
    string source;
    vector<Token> tokens;

    unordered_map<string, TokenType> keywords ={
        {"and", AND},
        {"false" ,  FALSE},
        {"if" ,     IF},
        {"nil" ,    NIL},
        {"or" ,     OR},
        {"return" , RETURN},
        {"true" ,   TRUE},
        {"define" ,    DEFINE},
        {"SET" ,  SET},
        {"cons" ,     CONS},
        {"cond" ,    COND},
        {"car" ,     CAR},
        {"cdr" ,     CDR},
        {"eq" , EQ},
        {"list?" ,   LIST}
    };
    
    unsigned int start = 0;
    unsigned int current = 0;
    int line = 1;

   bool isAtEnd(){
        return current >= source.length();
    }
    
    char advance(){
        return source.at(current++);
    }

    bool match(char expected) {
        if (isAtEnd()) return false;
        if (source.at(current) != expected) return false;

        current++;
        return true;
    }
    
    char peek() {
        if (isAtEnd()) return '\0';
        return source.at(current);
    }

    char peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source.at(current + 1);
    } 

    void addToken(TokenType type){
        addToken(type, NULL);
    }

    void addToken(TokenType type, auto literal) {
        string text = source.substr(start, current);
        cout<<" ADDTOKEN "<<text<<"Num: "<<literal<<endl;

        Token curr(type, text, literal, line);
        tokens.push_back(curr );
    }

    void tstring() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            cout<< "Unterminated string. Line: "<< line <<endl;
            return;
        }

        // The closing ".
        advance();

        // Trim the surrounding quotes.
        string value = source.substr(start + 1, current - 1);
        addToken(STRING, value);
    }

    void number() {
        while (isdigit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && isdigit(peekNext())) {
        // Consume the "."
            advance();

            while (isdigit(peek())) advance();
        }

        addToken(NUMBER, stod(source.substr(start, current)));
    }

    void identifier(){
        while (isalpha(peek()) || isdigit(peek())) advance();

        string text = source.substr(start, current);
        // cout<<" In Identifier "<<text<<endl;

        TokenType type;// = keywords.at(text);

        if (keywords.find(text) == keywords.end()) {
            type = IDENTIFIER;
            // cout<<" In Identifier- NO KEY "<<endl;

        }
        else{
            type = keywords.at(text);
            cout<<" In Identifier- BIG KEY "<<endl;

        }

        addToken(type);
    }

public:
    Scanner(string source) {
        this->source = source;
    }

    vector<Token> scanTokens(){

        while (!isAtEnd()) {
            start = current;
            scanToken();
        }

        Token curr(BEOF, "", NULL, line);
        tokens.push_back( curr);

        return tokens;
    }

    void scanToken(){
        

        char c = advance(); //next char type function 
        cout<<" Inside scanToken- Advance char: "<< c << endl;

        switch (c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': addToken(MINUS); break;
            case '+': addToken(PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '*': addToken(STAR); break; 
            case '/': addToken(SLASH); break; //no comments in my code
            case '!':
                addToken(match('=') ? BANG_EQUAL : BANG);
                break;
            case '=':
                addToken(match('=') ? EQUAL_EQUAL : EQUAL);
                break;
            case '<':
                addToken(match('=') ? LESS_EQUAL : LESS);
                break;
            case '>':
                addToken(match('=') ? GREATER_EQUAL : GREATER);
                break;
            case ' ':
            case '\r':
            case '\t':
                // Ignore whitespace.
                break;
            case '\n':
                line++;
                break;

            case '"': tstring(); break;
            default:
                if (isdigit(c)) {
                    cout<<" Inside scanTokens- NUMBER: "<<endl;

                    number();
                }
                else if(isalpha(c)){
                    cout<<" Inside scanTokens- Identifier: "<<endl;

                    identifier();
                }
                else {
                    cout << "Unexpected character. Line:"<< line << endl;
                }
                break;
        }
    }

  
};