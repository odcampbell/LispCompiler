#pragma once
#include <string>
#include <vector>
#include <cassert>

class Value {
    public:
    virtual std::string inspect() { assert(0);}
};

class ListValue : public Value{
    public:
    ListValue(){}

    void push(Value* val){
        m_list.push_back(val);
    }

    virtual std::string inspect();

    private:
    std::vector<Value *> m_list {};
};

class SymbolValue : public Value{
    public:
    SymbolValue(std::string str)  //tokens instead of lexemes?
        : m_str {str} {}
    
    std::string str() { return m_str;}

    virtual std::string inspect() { return str();} //for printing


    private:
    std::string m_str;
};