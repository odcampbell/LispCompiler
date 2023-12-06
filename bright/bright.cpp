#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "scanner.hpp"
#include "printer.hpp"

Value *READ (std::string input) {

    // Sep string into tokens put into vector
    Scanner scanner(input);
    std::vector<Token> curr_tokens = scanner.scanTokens();
    
    // Start creating lists/symbols from the tokens
    Reader reader(curr_tokens);
    return read_form(reader); //which returns read form..
    // cout << "[ ";

    // //Loop through current line, seperating along whitespace
    // for (auto it : curr_tokens) {
  
    //     // Print the values
    //    if( it.type != BEOF) cout <<  it.lexeme << " ";
    // }

    // cout << "]" << endl;

    // return input; 
}

Value *EVAL(Value *input) {return input;}

std::string PRINT(Value *input) { return pr_str(input);}


std::string rep(std::string input){
    auto ast = READ(input); //vector of vectors / strings
    auto result = EVAL(ast);
    return PRINT(result); //FIXME - currently printing input in cout in main
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