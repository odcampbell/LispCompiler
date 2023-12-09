#include "scanner.hpp"

Value *read_form(Reader &reader){ //garbage collection?
    auto token = reader.peek(); //returns current token wait no it doesnt..

    if(!token){
      return NULL;
    }

    switch(token.value().lexeme.at(0)){ //value() grabs val from optional
      case '(':
        return read_list(reader);
        //check isdigit peek, then pass in boolean flag
      case '-':{
        if(token.value().lexeme.length() == 1) 
          return read_atom(reader);
        else if ( isdigit(token.value().lexeme.at(1))){
          return read_int(reader);
        }else{
          return read_atom(reader);//not exactly.. e.g., -A -$
        }
      }
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        return read_int(reader);
      //   case '\'':
      default:
        if(token.value().lexeme == "true"){
          reader.next();
          return new TrueValue {};
        }
        else if (token.value().lexeme == "false"){
          reader.next();
          return new FalseValue {};
        }
        else if (token.value().lexeme == "nil"){
          reader.next();
          return new NilValue {};
        }
        return read_atom(reader);
    }
    // switch make a list val type class?
}

ListValue  *read_list(Reader &reader){ //return value? enum? // change opt str?
  //returns list value?

  // auto t= 
  reader.next(); // consume '(' // should equal something?

  auto *list = new ListValue {};

  while (auto token = reader.peek()){
    if (token.value().lexeme == ")"){ //end of list
      // auto t = 
      reader.next(); // consume ')'
      break;
    }
      
    list->push(read_form(reader)); //get body of list i.e., more lists or atoms
  }// end while

  return list;
}

Value *read_atom(Reader &reader){
  return new SymbolValue { reader.next().value().lexeme }; //do I want token or string here?
}

Value  *read_int(Reader &reader){ //return value? enum? // change opt str?
  auto token = reader.next(); // consume '(' // should equal something?
  long num = 0;
  bool neg = false;
  // cout<< "yup int"<<endl;
  for(char c : token.value().lexeme){
    if(c == '-'){
      neg = true;
    }
    else{
      num *= 10;
      int digit = c - 48;  
      num += digit;
    }
  } //end for

  if(neg) 
    num *= -1;
      
  return new IntValue { num };
}