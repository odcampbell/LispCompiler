#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "scanner.hpp"
#include "printer.hpp"
#include "env.hpp"

Value *READ (std::string input) {

    // Sep string into tokens put into vector
    Scanner scanner(input);
    std::vector<Token> curr_tokens = scanner.scanTokens();
    
    // Start creating meaningful lists/list of lists/symbols from the tokens
    Reader reader(curr_tokens);
    return read_form(reader); //which returns read form..
}

Value *eval_ast(Value *ast, Env &env);

Value *EVAL(Value *ast, Env &env) { //eg (+ 2 3)
    if(ast->type() != Value::Type::List){ // + 2 3
        return eval_ast(ast, env);
    }
    else if(ast->as_list()->is_empty()){
        return ast;
    }
    else{//looks like lists are always evaluated..

    //Ensure function is being called or something else? e.g., try sumn else first?
        auto list = ast->as_list();
        auto first = list->at(0);
        if(first->is_symbol() && first->as_symbol()->matches("def")){
            auto key = list->at(1)->as_symbol();
            auto val = EVAL(list->at(2),env);
            env.set(key,val);
            return val;
        }
        else if(first->is_symbol() && first->as_symbol()->matches("let")){ //exception, (let (a 9 b 10) a) = 9
            auto new_env = new Env {&env};
            auto bindings = list->at(1)->as_list();
            for(size_t i = 0; i <bindings->size(); i+=2){
                auto key = bindings->at(i)->as_symbol();
                assert(i+1 < bindings->size());
                auto val = EVAL(bindings->at(i+1), *new_env);
                new_env->set(key,val);
            }
            return EVAL(list->at(2), *new_env);
        }
        else{
            try{
                auto list = eval_ast(ast,env)->as_list(); // add fun, 2, 3
                if(list->at(0)->type() != Value::Type::Fn){
                    throw new ExceptionValue{list->inspect() + " doesnt start with function"};
                }
                else{ ////////old
                    
                    auto fn = list->at(0)->as_fn()->to_fn();
                    Value *args[list->size()-1]; // make array w/0 function spot
                    for (size_t i =1; i< list->size(); ++i){
                        args[i-1] = list->at(i);
                    }
                    return fn(list->size() - 1,args);
                }
            }catch(ExceptionValue* exception){
                std::cerr << exception->message() << std::endl;
            }return ast;
        }
    }
}

// takes in ast and env, switches on type of env
//returns symbols or lists of symbol values for each 
// internal list and its respective symobl
Value *eval_ast(Value *ast, Env &env){ 
    switch (ast->type()){
        case Value::Type::Symbol: { //diff from int, has own type
            return env.get(ast->as_symbol());
        }
        case Value::Type::List:{
            // std::cout<< "list: " << ast->inspect() << endl;
            auto result = new ListValue {};
            for( auto val : *ast->as_list()){
                // std::cout<< "val: " << val->inspect() << endl;

                result->push(EVAL(val, env)); //push a bunch of symbol values to list val
            }
            return result; // add func, 2, 3
        }
        default:
            return ast; // ints
    }
}

std::string PRINT(Value *input) { return pr_str(input);}

std::string rep(std::string input, Env &env){

    try {
        auto ast = READ(input); //vector of vectors / strings
        // auto temp = PRINT(ast); // record
        // std::cout<< "TEMP: "<<temp<<'\n';
        auto result = EVAL(ast,env);
        return PRINT(result); //FIXME - currently printing input in cout in main
    } catch(ExceptionValue* exception){
        std::cerr << exception->message() << std::endl;
        return "";
    }

}

//run file function
// add functionality to main to check args for a file
// eval and print for interactive only? 2

//add in error functionality?
//FIXME: only recognizing these functions, why is it erroring tho?

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

    auto env = new Env {nullptr}; //top level
    env->set(new SymbolValue("+"), new FnValue {add});
    env->set(new SymbolValue("-"), new FnValue {sub});
    env->set(new SymbolValue("*"), new FnValue {mul});
    env->set(new SymbolValue("/"), new FnValue {div});

    std::string input;

    for(;;) { // infinite loop
        std::cout << "user> ";

        if(!std:: getline(std::cin, input)){
            break;
        }
           
        std::cout << rep(input, *env) << std::endl;
    }  
    return 0;
}