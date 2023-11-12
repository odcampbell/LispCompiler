#include "reader.hpp"

optional<string> read_form(Reader &reader){ //garbage collection?
    auto token = reader.peek();//scan tokens?

    if(!token){
        return NULL;
    }

    switch(token.lexeme[0]){
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

optional<string> read_lsit(Reader &reader){ //garbage collection?
    return {};
}