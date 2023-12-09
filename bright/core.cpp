#include "core.hpp"
#include "printer.hpp"
#include <iostream>

std::unordered_map<std::string, Function> build_namespace(){
    std:: unordered_map<std:: string, Function> ns;
    ns["+"] = add;
    ns["-"] = subtract;
    ns["*"] = mul;
    ns["/"] = divide;

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

Value *empty_q(size_t argc, Value**args){
    assert(argc >=1);
    if (args[0]->is_list() && args[0]->as_list()->is_empty() ){ //Fixme
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

// Value *lt(size_t argc, Value**args){}

// Value *gt(size_t argc, Value**args){}

// Value *lte(size_t argc, Value**args){}

// Value *gte(size_t argc, Value**args){}

// Value *car(size_t argc, Value**args){}

// Value *cdr(size_t argc, Value**args){}

// Value *cons(size_t argc, Value**args){}
