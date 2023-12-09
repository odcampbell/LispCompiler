#pragma once
// #include <string>
#include <optional>
#include <vector>
#include <unordered_map>
#include "token.hpp"
#include "types.hpp"
#include "tokenType.hpp"


using namespace std;

// Class used to handle lexical analysis, cutt a given line of code into 
// lexemes that are apart of the alphabet of this language
class Scanner {
private:
    string source;
    vector<Token> tokens;

    //FIX ME? handle capitlization by lowercase comp?
    unordered_map<string, TokenType> keywords ={
        {"and", AND},
        {"false" ,  FALSE},
        {"if" ,     IF},
        {"nil" ,    NIL},
        {"or" ,     OR},
        {"return" , RETURN},
        {"true" ,   TRUE},
        {"def" ,    DEFINE},
        {"let" ,    LET},
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
    
    // returns next element and increments the current element index
    // consumes a char
    char advance(){
        return source.at(current++);
    }

    // used to check "next" element is apart of one conceptual thing with the
    // prev element, e.g., >= or !=
    bool match(char expected) {
        if (isAtEnd()) return false;
        if (source.at(current) != expected) return false;

        current++;
        return true;
    }
    
    // returns next element but does NOT increment element
    // doesnt consume char
    char peek() {
        if (isAtEnd()) return '\0';
        return source.at(current);
    }

    // finish??
    char peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source.at(current + 1);
    } 

    // wrapper that just takes in token type
    // exists to overload function for parts of the grammar that are terminals
    void addToken(TokenType type){
        addToken(type, NULL);
    }

    // uses private memebrs to initialize Token obj via constructor and add it to 
    // scanner's Token vector
    void addToken(TokenType type, auto literal) {
        string text = source.substr(start, ( current - start));

        Token curr (type, text, literal, line);
        tokens.push_back(curr );
    }

    // handles string literals by consuming the quotes and saving the 
    // enclosed string as a token
    void tstring() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            cout<< "Unterminated string. Line: "<< line <<endl;
            return;
        }

        // The closing ". so current+1
        advance();

        // Trim the surrounding quotes.
        string value = source.substr(start + 1, (current - 1 ) - (start + 1));

        addToken(STRING, value);
    }

    // increments current index until the last digit in the number is consuemd
    // adds the number (type casted basically) as a Token,to the scanners token vector
    void number() {
        while (isdigit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && isdigit(peekNext())) {
        // Consume the "."
            advance();

            while (isdigit(peek())) advance();
        }

        addToken(NUMBER, stod(source.substr(start, ( current - start)))); //FIX ME?
    }


    /*
    identifiers are some sort of variable (func, arg, etc)
    handles case where we've made sure its not apart of the grammar
    and it's not a number or string literal, if it is found in the keyword
    use that type as it's part of the grammar, otherwise its broadly just a var (IDENTIFIER)
    add that token to the scanner's Token vector
    */
    void identifier(){//update here for def! let* nil?
        while (isalpha(peek()) || isdigit(peek())) advance();

        string text = source.substr(start, ( current - start));

        TokenType type;

        if (keywords.find(text) == keywords.end()) {
            type = IDENTIFIER;
        }
        else{
            type = keywords.at(text);
        }

        addToken(type);
    }

public:

    // Constructor that initialzes object with user input (one line)
    Scanner(string source) {
        this->source = source;
    }

    //Using "source" string intialized via constructor above
    vector<Token> scanTokens(){

        while (!isAtEnd()) {
            start = current;
            // cout<<endl<<"Before Scan: Start= "<< start << " Curr= " << current<< endl;
            scanToken();
        }

        Token curr(BEOF, "", NULL, line);
        tokens.push_back( curr);

        return tokens;
    }


    /*
    Given string (source), go character by character checking for parts of grammar,
    variables, keywords, numbers, or strings to seperate by individual tokens in a 
    vector (which helper functions handle). This vector represents alphabetical lexemes or 
    smallest parts that the grammar can then interpret and use to build correct sentences.
    Thus, the vector that results from this func must be passded through generators based
    on the grammar for the language
    */
    void scanToken(){

        char c = advance(); // returns and consumes prev char

        switch (c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': {
                int curr = current;
                if(source.at(curr) == ' '){
                    // cout << "Next char must be space"<< endl;
                    addToken(MINUS); 
                }
                else if(isdigit(source.at(curr))){
                    // cout << "Next char must be digit. Curr:"<<curr<<" "<< source.at(curr)<< endl;
                    advance(); //consume -
                    number();
                }
                else{
                    cout << "Unexpected character. Line:"<< line <<" Curr: "<< curr << endl;
                }
                    
                break;
                }
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
                    number();
                }
                else if(isalpha(c)){
                    // cout << "Alphas:(!@#$%^&) cause issues here"<< line << endl;

                    identifier();
                }
                else {
                    cout << "Unexpected character. Line:"<< line << endl;
                }
                break;
        }
    }

};

// Class stores tokens and positions, used to do some generative grammar work
class Reader {
    public:

    // Constructor to initialize class obj with token vector <single elements>
    Reader(vector<Token> &tokens)
        : readerTokens { tokens } { }
    
    // returns token at current pos and increments
    optional<Token> next(){

        if(readerIndex < readerTokens.size()){
            return readerTokens.at(readerIndex++); //entire token needed or lexeme?
        }
        return {};
    }

    // just returns token at current pos
    optional<Token> peek(){
        if(readerIndex < readerTokens.size()){
            return readerTokens.at(readerIndex);
        }
        return{};
    }

    // optional<Token> peekNext(){ //shows next without consuming

    //     if(readerIndex < readerTokens.size()){
    //         readerIndex++;
    //         auto token = readerTokens.at(readerIndex);
    //         readerIndex--;
    //         return token; //entire token needed or lexeme?
    //     }
    //     return {};
    // }

    // bool is_number(const std::string& s){
    //     string::const_iterator it = s.begin();
    //     while (it != s.end() && isdigit(*it)) ++it;
    //     return !s.empty() && it == s.end();
    // }

    private:
        vector<Token> &readerTokens;
        size_t readerIndex { 0 };

};


//read_str takes the line input, scans into lexemes, and initializes the reader obj
//with a token vector, then calls read form
// on the tokens vector just pass around the reference 

Value *read_form(Reader &reader);

ListValue *read_list(Reader &reader); //return value? enum?

Value *read_atom(Reader &reader); //return value? enum?

Value *read_int(Reader &reader); //return value? enum?

//read form takes in the reader object, uses peak which returns the token (just fine)
// switch on the lexeme