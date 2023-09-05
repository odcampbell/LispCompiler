#pragma once
//move into seperate file with header include
enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, FALSE, FOR, IF, NIL, OR,
  DEFINE, RETURN, TRUE, SET, CONS, COND, CAR, CDR,
  SYMBOL, LIST, EQ, 

  BEOF
};