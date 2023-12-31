#pragma once
#include <string>
#include <vector>
#include <functional>
#include <cassert>

class ListValue;
class SymbolValue;
class IntValue;
class FnValue;
class ExceptionValue;
class TrueValue;
class FalseValue;
class NilValue;


class Value {
    public:

    enum class Type {
        List,
        Symbol,
        Integer,
        Fn,
        Exception,
        False,
        True,
        Nil,
    };

    virtual std::string inspect() = 0;
    virtual Type type() const = 0;
    virtual bool is_symbol() {return false;}
    virtual bool is_truthy() {return true;}
    virtual bool is_true() const {return false;}
    virtual bool is_false() const {return false;}
    virtual bool is_nil() const {return false;}
    virtual bool is_list() {return false;}
    virtual bool is_listy() {return false;}
    virtual bool is_integer() {return false;}
    virtual bool operator==( Value *) const {return false;}

    // bool operator!=( Value *other) const {return !(*this == other);}
    // virtual bool is_listy() {return false;}

    ListValue* as_list();
    IntValue* as_int();
    SymbolValue* as_symbol();
    FnValue* as_fn();
    ExceptionValue *as_exception();
    TrueValue *as_true();
    FalseValue *as_false();
    NilValue *as_nil();
};

class ListValue : public Value{
    public:
    ListValue(){}

    void push(Value* val){
        m_list.push_back(val);
    }

    virtual std::string inspect() override;
    virtual Type type() const override { return Type::List;}
    bool is_list() override {return true;}
    // virtual bool is_listy() {return true;}
    virtual bool operator==(Value *) const override;

    auto begin() {return m_list.begin();}
    auto end() {return m_list.end();}

    bool is_empty() {return m_list.size() == 0;}
    size_t size() const { return m_list.size(); }
    Value* at(size_t index) const{ return m_list.at(index); }
    void pop_front() { m_list.erase(m_list.begin()); }

    private:
    std::vector<Value *> m_list {};
};


struct HashMapHash{
    std::size_t operator()(Value *key) const noexcept {
        return std::hash<std::string> {}(key->inspect());
    }
};

struct HashMapPred{
     bool operator()(Value *lhs, Value *rhs) const{
        return lhs->inspect() == rhs->inspect(); //FIX ME
    }
};

class SymbolValue : public Value{
    public:
    SymbolValue(std::string str)  //tokens instead of lexemes?
        : m_str {str} {}
    
    std::string str() { return m_str;}

    virtual std::string inspect() override{ return str();} //for printing
    virtual Type type() const override { return Type::Symbol;}
    bool matches(const char *str) const{ return m_str == str;}
    virtual bool is_symbol() override {return true;}
    bool operator==( Value *other) const override  {
        return other->is_symbol() && const_cast<Value*>(other)->as_symbol()->m_str == m_str;
    } 

    private:
    std::string m_str;
};

using Function = std::function<Value *(size_t, Value**)>;

class IntValue : public Value {
    public:
    IntValue (long l)
        : m_long { l } {}

    long to_long(){ return m_long; }

    virtual std::string inspect() override{ 
        return std::to_string(m_long); //may be able to use these for car/cdr/cons functions
    } //for printing

    virtual bool is_integer() override{
        return true;
    }

    //cont Val?
    virtual Type type() const override{ return Type::Integer;}
    bool operator==( Value *other) const override  {
        return other->as_int() && const_cast<Value*>(other)->as_int()->m_long == m_long;
    } 
    //inspect
    
    private: 
    long m_long { 0 };
};

class FnValue : public Value{
    public:
    FnValue(Function fn)
        : m_fn { fn } {}

    Function to_fn() { return m_fn;}

    virtual std::string inspect() override{ 
        return "<fn placeholder>";
    } //for printing

    virtual Type type() const override{ return Type::Fn;}
    bool operator==( Value *other) const override  {
        return other == this;
    } 
    private: 
    Function m_fn {nullptr};
};

class ExceptionValue : public Value{
    public:
    ExceptionValue(std::string message)
        : m_message { message } {}

    const std::string &message() { return m_message;}

    virtual std::string inspect() override{ 
        return "<exception " + m_message + ">";
    } //for printing

    virtual Type type() const override { return Type::Exception;}

    private: 
    std::string m_message;
};

class TrueValue : public Value{
    public:
        virtual bool is_true() const override {return true;}
        virtual std::string inspect() override {return "true"; }
        virtual Type type() const override {return Type::True;}

        bool operator==( Value *other) const override  {
            return other->is_true();
        } 
        
};

class FalseValue : public Value{
    public:
        virtual bool is_false() const override {return true;}
    
        virtual std::string inspect() override {return "false"; }
        virtual Type type() const override {return Type::False;}
        virtual bool is_truthy() {return false;}

           bool operator==( Value *other) const override  {
            return other->is_false();
        } 

};

class NilValue : public Value{
    public:
        virtual bool is_nil() const override {return true;}

        virtual std::string inspect() override {return "nil"; }
        virtual Type type() const override {return Type::Nil;}
        virtual bool is_truthy() override {return false;}

        bool operator==( Value *other) const override  {
            return other->is_nil();
        } 

};