#include "types.hpp"

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
    
    return out;
}



