#include "parser.h"
#include "lox.h"
#include <vector>


namespace lox
{
Parser::sptr_expr Parser::parse() {
  try {
    return expression();
  } catch(ParserError err) {
    return nullptr;
  }
}
  
Parser::sptr_expr Parser::expression(){
  return equality();
}

Parser::sptr_expr Parser::equality(){
  sptr_expr expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    Token op = previous();
    sptr_expr right = comparison();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Parser::sptr_expr Parser::comparison(){
  sptr_expr expr = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
    Token op = previous();
    sptr_expr right = term();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Parser::sptr_expr Parser::term(){
  sptr_expr expr = factor();

  while (match({TokenType::MINUS, TokenType::PLUS})) {
    Token op = previous();
    sptr_expr right = factor();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Parser::sptr_expr Parser::factor(){
  sptr_expr expr = unary();

  while (match({TokenType::SLASH, TokenType::STAR})) {
    Token op = previous();
    sptr_expr right = unary();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Parser::sptr_expr Parser::unary(){
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token op = previous();
    sptr_expr right = unary();
    return std::make_shared<Unary>(op, right);
  }
  return primary();
}

Parser::sptr_expr Parser::primary(){
  if (match({TokenType::FALSE}))
    return std::make_shared<Literal>(false);
  if (match({TokenType::TRUE}))
    return std::make_shared<Literal>(true);
  if (match({TokenType::NIL}))
    return std::make_shared<Literal>(nullptr);
  
  if (match({TokenType::NUMBER, TokenType::STRING}))
    return std::make_shared<Literal>(previous().getLiteral());
  
  if (match({TokenType::LEFT_PAREN})) {
    sptr_expr expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_shared<Grouping>(expr);
  }
  throw error(peek(), "Expect expression.");
}

bool Parser::match(std::initializer_list<TokenType> types){
  for (auto type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

bool Parser::check(TokenType type){
  if (isAtEnd())
    return false;
  return peek().getType() == type;
}

Token Parser::advance(){
  if (!isAtEnd())
    ++current_;
  return previous();
}

bool Parser::isAtEnd(){
  return peek().getType() == TokenType::EEOF;
}

Token Parser::peek(){
  return tokens_.at(current_);
}

Token Parser::previous(){
  return tokens_.at(current_ - 1);
}

Token Parser::consume(TokenType type, std::string msg) {
  if (check(type))
    return advance();
  
  throw error(peek(), msg);
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().getType() == TokenType::SEMICOLONS)
      return;
    
    switch (peek().getType()) {
      case TokenType::CLASS:
      case TokenType::FUN:
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
      case TokenType::PRINT:
      case TokenType::RETURN:
        return;
      default:
        break;
    }

    advance();
  }
}

Parser::ParserError Parser::error(Token token, std::string msg) {
  Lox::error(token, msg);
  return ParserError("");
}
} // namespace lox


