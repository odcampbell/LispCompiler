#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "scanner.cpp"

//class for tokens instead of global vector issue
std::string READ(std::string input) {
    // Tokenizer function here - no analysis for now
    // string stream for strings in input cout input

    std::string copyin = input;

    Scanner scanner(copyin);
    std::vector<Token> curr_tokens = scanner.scanTokens();

    std::stringstream ss(input);
    std::string rawToken;
    std::vector<std::string> tokens;

    int i = 0;
    std::cout << "tokens: ( ";

    while (ss >> rawToken){
        tokens.push_back(rawToken);
        std::cout << tokens.at(i) << ", ";
        i++;
    }
    std::cout << " )" << std::endl;

    

    return input; 
}

std::string EVAL(std::string input) {return input; }

std::string PRINT(std::string input) {return input; }


std::string rep(std::string input){
    auto ast = READ(input);
    auto result = EVAL(ast);
    return PRINT(result);
}

//run file function
// add functionality to main to check args for a file
// eval and print for interactive only? 

//add in error functionality?
int main(){

    std::string input;

    for(;;) { // infinite loop
        std::cout << "user> ";

        if(!std:: getline(std::cin, input)){
            break;
        }
           
        std::cout << rep(input) << std::endl;
    }  
    return 0;
}