#pragma once
#include <string>
#include <vector>
#include <cassert>

class ListValue;
class SymbolValue;
class IntValue;
class FnValue;


class Value {
    public:

    enum class Type {
        List,
        Symbol,
        Integer,
        Fn,
    };

    virtual std::string inspect() { assert(0);}
    virtual Type type() { assert(0);}

    ListValue* as_list();
    IntValue* as_int();
    SymbolValue* as_symbol();
    FnValue* as_fn();
};

class ListValue : public Value{
    public:
    ListValue(){}

    void push(Value* val){
        m_list.push_back(val);
    }

    virtual std::string inspect();
    virtual Type type() { return Type::List;}

    auto begin() {return m_list.begin();}
    auto end() {return m_list.end();}

    bool is_empty() {return m_list.size() == 0;}
    size_t size() { return m_list.size(); }
    Value* at(size_t index) { return m_list.at(index); }

    private:
    std::vector<Value *> m_list {};
};

class SymbolValue : public Value{
    public:
    SymbolValue(std::string str)  //tokens instead of lexemes?
        : m_str {str} {}
    
    std::string str() { return m_str;}

    virtual std::string inspect() { return str();} //for printing
    virtual Type type() { return Type::Symbol;}


    private:
    std::string m_str;
};

using FnPtr = Value*(*)(size_t, Value**);

class IntValue : public Value {
    public:
    IntValue (long l)
        : m_long { l } {}

    long to_long(){ return m_long; }

    virtual std::string inspect() { 
        return std::to_string(m_long);
    } //for printing

    virtual Type type() { return Type::Integer;}
    //inspect
    
    private: 
    long m_long { 0 };
};

class FnValue : public Value{
    public:
    FnValue(FnPtr fn)
        : m_fn { fn } {}

    FnPtr to_fn() { return m_fn;}

    virtual std::string inspect() { 
        return "placeholder";
    } //for printing

    virtual Type type() { return Type::Fn;}

    private: 
    FnPtr m_fn {nullptr};
};