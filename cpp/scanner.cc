#include "scanner.h"
#include "util.h"
#include "lox.h"
#include <string>
#include <iostream>

namespace Lox {

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start_ = current_;
    scanToken();
  }

  tokens_.emplace_back(TokenType::EEOF, "", nullptr, line_);
  return tokens_;
}

void Scanner::scanToken() {
  char ch = advance();
  switch (ch) {
    case '(':
      addToken(TokenType::LEFT_PAREN);
      break;
    case ')':
      addToken(TokenType::RIGHT_PAREN);
      break;
    case '{':
      addToken(TokenType::LEFT_BRACE);
      break;
    case '}':
      addToken(TokenType::RIGHT_BRACE);
      break;
    case ',':
      addToken(TokenType::COMMA);
      break;
    case '.':
      addToken(TokenType::DOT);
      break;
    case '-':
      addToken(TokenType::MINUS);
      break;
    case '+':
      addToken(TokenType::PLUS);
      break;
    case ';':
      addToken(TokenType::SEMICOLONS);
      break;
    case '*':
      addToken(TokenType::STAR);
      break;
    case '!':
      addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? TokenType::GREATER_QUAL : TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      ++line_;
      break;
    case '"':
      string();
      break;
    default:
      if (isDigit(ch)) {
        number();
      } else if (isAlpha(ch)) {
        identifier();
      } else {
        Lox::error(line_, "Unexpected character.");
      }
      break;
  }
}

bool Scanner::isAtEnd() const { return current_ >= source_.size(); }

char Scanner::advance() { return source_[current_++]; }

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source_[current_] != expected) return false;

  ++current_;
  return true;
}

char Scanner::peek() const {
  if (isAtEnd()) return '\0';
  return source_[current_];
}

char Scanner::peekNext() const {
  if (current_ + 1 >= source_.size()) return '\0';
  return source_[current_ + 1];
}

void Scanner::addToken(TokenType type) { addToken(type, nullptr); }

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source_.substr(start_, current_ - start_);
  tokens_.emplace_back(type, text, literal, line_);
}

bool Scanner::isDigit(char ch) const { return ch >= '0' && ch <= '9'; }

bool Scanner::isAlpha(char ch) const {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch =='_';
}

bool Scanner::isAlphaNum(char ch) const {
  return isAlpha(ch) || isDigit(ch);
}

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') ++line_;
    advance();
  }

  if (isAtEnd()) {
    Lox::error(line_, "Unterminated string.");
    return;
  }

  // closed "
  advance();

  std::string str = source_.substr(start_ + 1, current_ - start_ - 2);
  addToken(TokenType::STRING, str);
}

void Scanner::number() {
  while (isDigit(peek())) advance();

  // look for fractional part
  if (peek() == '.' && isDigit(peekNext())) {
    // consume .
    advance();
    while (isDigit(peek())) advance();
  }
  addToken(TokenType::NUMBER,
           std::stod(source_.substr(start_, current_ - start_)));
}

void Scanner::identifier() {
  while (isAlphaNum(peek())) advance();

  std::string text = source_.substr(start_, current_ - start_);
  for (int i = 0; i < sizeof(kKeywords) / sizeof(std::pair<std::string, TokenType>); i++) {
    if (text == kKeywords[i].first) {
      addToken(kKeywords[i].second);
      return;
    }
  }
  addToken(TokenType::IDENTIFIER, text);
}

}  // namespace Lox
