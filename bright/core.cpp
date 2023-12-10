#include "core.hpp"
#include "printer.hpp"
#include "types.hpp"
#include <iostream>

std::unordered_map<std::string, Function> build_namespace(){
    std:: unordered_map<std:: string, Function> ns;
    ns["+"] = add;
    ns["-"] = subtract;
    ns["*"] = mul;
    ns["/"] = divide;
    ns["%"] = mod; 
    ns["prn"] = prn;
    ns["list?"] = list_q;
    ns["list"] = list;
    ns["num?"] = num_q;
    ns["nil?"] = nil_q;
    ns["and?"] = and_q;
    ns["or?"] = or_q;
    ns["symbol?"] = symbol_q;
    ns["count"] = count;
    ns["="] = eq;
    ns["<"] = lt;
    ns["<="] = lte;
    ns[">"] = gt;
    ns[">="] = gte;
    ns["not"] = not_fun;
    ns["car"] = car;
    ns["cdr"] = cdr;
    ns["cons"] = cons;

    return ns;
}


Value *add(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() + b->as_int()->to_long();
    return new IntValue {result};
}

Value *mod(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() % b->as_int()->to_long();
    return new IntValue {result};
}

Value *subtract(size_t argc, Value**args){
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

Value *divide(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    assert(a->type() == Value::Type::Integer);
    assert(b->type() == Value::Type::Integer);

    long result = a->as_int()->to_long() / b->as_int()->to_long();
    return new IntValue {result};
}


Value *prn(size_t argc, Value**args){
    assert(argc >=1);
    std::cout<< pr_str(args[0]) <<"\n";
    return new NilValue;
}

//takes params and returns as list
Value *list(size_t argc, Value**args){
    auto l = new ListValue {};
    for(size_t i=0; i<argc; ++i){
        l->push(args[i]);
    }
    return l;
}

// true if first param is list
Value *list_q(size_t argc, Value**args){
    assert(argc >=1);
    if (args[0]->is_list() ){
        return new TrueValue;
    }
    return new FalseValue;
    
}

// true if first param is list
Value *symbol_q(size_t argc, Value**args){
    assert(argc >=1);

    auto a = args[0];
    if((a->type() == Value::Type::Symbol) || !(a->is_integer())){
      return new TrueValue;
    }
    return new FalseValue;
}

// support decimals one day then update here
Value *num_q(size_t argc, Value**args){
    assert(argc == 1);
    if (args[0]->is_integer() ){
        return new TrueValue;
    }
    return new FalseValue;
    
}

Value *nil_q(size_t argc, Value**args){
    assert(argc >=1);
    if (args[0]->is_list() && args[0]->as_list()->is_empty() ){ //Fixme
        return new TrueValue;
    }
    return new FalseValue;
}

Value *and_q(size_t argc, Value**args){ //takes exprs
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];
    if (a->is_truthy() && b->is_truthy() ){ 
        return new TrueValue;
    }
    return new FalseValue;
}

Value *or_q(size_t argc, Value**args){
    assert(argc == 2);
    auto a = args[0];
    auto b = args[1];

    if (a->is_truthy() || b->is_truthy() ){ 
        return new TrueValue;
    }
    return new FalseValue;
}

Value *count(size_t argc, Value**args){
    assert(argc >=1);
    if(args[0]->is_list()){
        return new IntValue { static_cast<long>(args[0]->as_list()->size())}; //fixme
    }
    return new IntValue {0};
}

Value *eq(size_t argc, Value**args){
    assert(argc >=2);
    auto a = args[0];
    auto b = args[1];
    
    if(*a == b){
        return new TrueValue;
    }
    return new FalseValue;
}

Value *lt(size_t argc, Value**args){
    assert(argc >=2);
    auto a = args[0];
    auto b = args[1];
    assert(a->is_integer());
    assert(b->is_integer());

    if( a->as_int()->to_long() < b->as_int()->to_long())
        return new TrueValue;
    return new FalseValue;
}

Value *gt(size_t argc, Value**args){
    assert(argc >=2);
    auto a = args[0];
    auto b = args[1];
    assert(a->is_integer());
    assert(b->is_integer());

    if( a->as_int()->to_long() > b->as_int()->to_long())
        return new TrueValue;
    return new FalseValue;
}

Value *lte(size_t argc, Value**args){
    assert(argc >=2);
    auto a = args[0];
    auto b = args[1];
    assert(a->is_integer());
    assert(b->is_integer());

    if( a->as_int()->to_long() <= b->as_int()->to_long())
        return new TrueValue;
    return new FalseValue;
}

Value *gte(size_t argc, Value**args){
    assert(argc >=2);
    auto a = args[0];
    auto b = args[1];
    assert(a->is_integer());
    assert(b->is_integer());

    if( a->as_int()->to_long() >= b->as_int()->to_long())
        return new TrueValue;
    return new FalseValue;
}

Value *not_fun(size_t argc, Value**args){
    assert(argc >=1);
    if( args[0]->is_truthy())
        return new FalseValue;
    return new TrueValue;
}

Value *car(size_t argc, Value**args){
    try{
        if(argc != 1) 
            throw new ExceptionValue{" car only accepts 1 element"};

        if(args[0]->is_list()){
            return args[0]->as_list()->at(0);
        }
        else{
            throw new ExceptionValue{args[0]->inspect() + " car called on non-list"};
            return args[0];
        }
    }
    catch(ExceptionValue* exception){
        std::cerr << exception->message() << std::endl;
        return args[0];
    }
}

Value *cdr(size_t argc, Value**args){

    try{
            
        if(argc != 1) 
            throw new ExceptionValue{" cdr only accepts 1 element"};

        if(args[0]->is_list()){
            auto l = new ListValue {};
            auto len = args[0]->as_list()->size();
            for(size_t i=1; i<len; ++i){
                l->push(args[0]->as_list()->at(i));
            }
            return l;
        }
        else{
            throw new ExceptionValue{args[0]->inspect() + " not a list"};
            return args[0];
        }
    }
    catch(ExceptionValue* exception){
        std::cerr << exception->message() << std::endl;
        return args[0];
    }
}

Value *cons(size_t argc, Value**args){
    
    try{
            
        if(argc != 2) 
            throw new ExceptionValue{" cons only accepts 2 elements"};

        auto l = new ListValue {};
        l->push(args[0]);
        l->push(args[1]);
        return l;
    }
    catch(ExceptionValue* exception){
        std::cerr << exception->message() << std::endl;
        return args[0];
    }
}
