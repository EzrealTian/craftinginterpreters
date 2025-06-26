#if !defined(LOX_PARSER_H_)
#define LOX_PARSER_H_

#include <vector>
#include <memory>
#include "token.h"
#include "util.h"
#include "expr.h"
#include <stdexcept>

/**
 * expression     → equality ;
 * equality       → comparison ( ( "!=" | "==" ) comparison )* ;
 * comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
 * term           → factor ( ( "-" | "+" ) factor )* ;
 * factor         → unary ( ( "/" | "*" ) unary )* ;
 * unary          → ( "!" | "-" ) unary | primary ;
 * primary        → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
 */


namespace lox
{
class Parser {
using sptr_expr = std::shared_ptr<Expr>;
public:
  Parser(std::vector<Token> tokens) : tokens_(tokens), current_(0) {}
  sptr_expr parse();

private:
  sptr_expr expression();
  sptr_expr equality();
  sptr_expr comparison();
  sptr_expr term();
  sptr_expr factor();
  sptr_expr unary();
  sptr_expr primary();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  Token consume(TokenType type, std::string msg);
  void synchronize();

  class ParserError : public std::runtime_error {
    public:
      explicit ParserError(const std::string& msg) : std::runtime_error(msg) {}
  };

  ParserError error(Token token, std::string msg);

private:
  std::vector<Token> tokens_;
  int current_;
};
} // namespace lox



#endif // LOX_PARSER_H_
