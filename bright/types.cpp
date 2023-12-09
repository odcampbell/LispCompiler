#include "types.hpp"
//used for static type casting
ListValue *Value::as_list(){
    assert(type() == Type::List);
    return static_cast<ListValue*>(this);

}
IntValue *Value::as_int(){
    assert(type() == Type::Integer);
    return static_cast<IntValue*>(this);

}
SymbolValue *Value::as_symbol(){
    assert(type() == Type::Symbol);
    return static_cast<SymbolValue*>(this);

}
FnValue *Value::as_fn(){
    assert(type() == Type::Fn);
    return static_cast<FnValue*>(this);
}

ExceptionValue *Value::as_exception(){
    assert(type() == Type::Exception);
    return static_cast<ExceptionValue*>(this);
}

TrueValue *Value::as_true(){
    assert(type() == Type::True);
    return static_cast<TrueValue*>(this);
}

FalseValue *Value::as_false(){
    assert(type() == Type::False);
    return static_cast<FalseValue*>(this);
}

NilValue *Value::as_nil(){
    assert(type() == Type::Nil);
    return static_cast<NilValue*>(this);
}
    
std::string ListValue::inspect() {
    std::string out= "(";

    for (auto *value : m_list){
        out.append(value->inspect());
        out.append(" ");
    }
    
    if( m_list.size() > 0){
        out[out.length()-1] = ')';
    }
    else{
        out.append(")");
    }
    
    return out; // string of form: (2 , 3 , 4 , 5 , 6 , 7 , 8)
}

bool ListValue::operator==(Value *other) const {
    if(type() != other->type()){
        return false;
    }

    auto other_list = other->as_list();

    if(size() != other_list->size()){
        return false;
    }

    for(size_t i=0; i<size(); ++i){
        if(!(*at(i) == other_list->at(i))){ //other?
            return false;
        }
    }
    return true;
}