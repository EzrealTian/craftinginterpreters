#if !defined(LOX_UTIL_H_)
#define LOX_UTIL_H_

#include <unordered_map>
#include <string>

namespace Lox {
enum class TokenType {
  // single character tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLONS,
  SLASH,
  STAR,

  // One or two character tokens
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_QUAL,
  LESS,
  LESS_EQUAL,

  // Literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  EEOF
};

const std::unordered_map<TokenType, std::string> TokenTypeToString = {
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::SEMICOLONS, "SEMICOLONS"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},
    {TokenType::BANG, "BANG"},
    {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_QUAL, "GREATER_QUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::AND, "AND"},
    {TokenType::CLASS, "CLASS"},
    {TokenType::ELSE, "ELSE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FUN, "FUN"},
    {TokenType::FOR, "FOR"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::SUPER, "SUPER"},
    {TokenType::THIS, "THIS"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::VAR, "VAR"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::EEOF, "EEOF"},
};

inline std::string tokenTypeToString(TokenType type) {
  auto it = TokenTypeToString.find(type);
  return it != TokenTypeToString.end() ? it->second : "UNKNOWN";
}

const std::pair<std::string, TokenType> kKeywords[] = {
  {"and", TokenType::AND},
  {"class", TokenType::CLASS},
  {"else", TokenType::ELSE},
  {"false", TokenType::FALSE},
  {"for", TokenType::FOR},
  {"fun", TokenType::FUN},
  {"if", TokenType::IF},
  {"nil", TokenType::NIL},
  {"or", TokenType::OR},
  {"print", TokenType::PRINT},
  {"return", TokenType::RETURN},
  {"super", TokenType::SUPER},
  {"this", TokenType::THIS},
  {"true", TokenType::TRUE},
  {"var", TokenType::VAR},
  {"while", TokenType::WHILE},
};
}  // namespace Lox


#endif // LOX_UTIL_H_