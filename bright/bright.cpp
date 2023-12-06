#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "scanner.hpp"
#include "printer.hpp"


using Env = std::unordered_map<SymbolValue *, Value *, HashMapHash, HashMapPred >;


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
Value *eval_ast(Value *ast, Env &env);

Value *EVAL(Value *ast, Env &env) {

    if(ast->type() != Value::Type::List){
        return eval_ast(ast, env);
    }
    else if(ast->as_list()->is_empty()){
        return ast;
    }
    else{
        auto list = eval_ast(ast,env)->as_list();
        auto fn = list->at(0)->as_fn()->to_fn();

        Value *args[list->size()-1];
        for (size_t i =1; i< list->size(); ++i){
            args[i-1] = list->at(i);
        }
        return fn(list->size() - 1,args);
    }

    // return input;
}

Value *eval_ast(Value *ast, Env &env){
    switch (ast->type()){
        case Value::Type::Symbol: {
            auto search = env.find(ast->as_symbol());
            if (search == env.end()){
                std::cerr <<"error, "<< ast->as_symbol()->str() << " not found\n";
                return new SymbolValue { "nil"};
            }
            return search->second;
        }
        case Value::Type::List:{
            auto result = new ListValue {};
            for( auto val : *ast->as_list()){
                result->push(EVAL(val, env));
            }
            return result;
        }
        default:
            return ast;
    }
}

std::string PRINT(Value *input) { return pr_str(input);}

std::string rep(std::string input, Env &env){
    auto ast = READ(input); //vector of vectors / strings
    auto result = EVAL(ast,env);
    return PRINT(result); //FIXME - currently printing input in cout in main
}

//run file function
// add functionality to main to check args for a file
// eval and print for interactive only? 2

//add in error functionality?

Value *add(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() + b->as_int()->to_long();
    return new IntValue {result};
}

Value *sub(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() - b->as_int()->to_long();
    return new IntValue {result};
}

Value *mul(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() * b->as_int()->to_long();
    return new IntValue {result};
}

Value *div(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() / b->as_int()->to_long();
    return new IntValue {result};
}

int main(){

    Env env {};
    env[new SymbolValue("+")] = new FnValue {add};
    env[new SymbolValue("-")] = new FnValue {sub};
    env[new SymbolValue("*")] = new FnValue {mul};
    env[new SymbolValue("/")] = new FnValue {div};

    std::string input;

    for(;;) { // infinite loop
        std::cout << "user> ";

        if(!std:: getline(std::cin, input)){
            break;
        }
           
        std::cout << rep(input, env) << std::endl;
    }  
    return 0;
}