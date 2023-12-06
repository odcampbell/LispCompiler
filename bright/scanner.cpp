#include "scanner.hpp"

Value *read_form(Reader &reader){ //garbage collection?
    auto token = reader.peek(); //returns current token

    if(!token){
      return NULL;
    }

    switch(token.value().lexeme.at(0)){ //value() grabs val from optional
      case '(':
        return read_list(reader);
    //   case '[':
      //     return read_vector(reader);
      //   case '{':
      //     return read_hash_map(reader);
      //   case '\'':
      //   case '`':
      //   case '~':
      //   case '@':
      //     return read_quoted_value(reader);
      //   case '^':
    //     return read_with_meta(reader);
      default:
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