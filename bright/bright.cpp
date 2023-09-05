#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "scanner.cpp"

//class for tokens instead of global vector issue
std::string READ(std::string input) {
    // Tokenizer function here - no analysis for now

    // Sep string into tokens
    Scanner scanner(input);
    std::vector<Token> curr_tokens = scanner.scanTokens();

    cout << "[ ";

    //Loop through current line, seperating along whitespace
    for (auto it : curr_tokens) {
  
        // Print the values
       if( it.type != BEOF) cout <<  it.lexeme << " ";
    }

    cout << "]" << endl;

    return input; 
}

std::string EVAL(std::string input) {return input; }

std::string PRINT(std::string input) {return input; }


std::string rep(std::string input){
    auto ast = READ(input);
    auto result = EVAL(ast);
    return PRINT("Rep->PrintFun"); //FIXME - currently printing input in cout in main
}

//run file function
// add functionality to main to check args for a file
// eval and print for interactive only? 2

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