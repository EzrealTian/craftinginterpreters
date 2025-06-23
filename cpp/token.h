#if !defined(LOX_TOKEN_H_)
#define LOX_TOKEN_H_

#include <string>
#include "util.h"

namespace lox {
class Token {
 public:
  Token(TokenType type, std::string lexeme, Value literal, int line)
      : type_(type), lexeme_(lexeme), literal_(literal), line_(line) {}

  std::string to_string() const;

  std::string getLexeme() const { return lexeme_; }

  Value getLiteral() const { return literal_; }

 private:
  std::string literalToString() const;

 private:
  TokenType type_;
  std::string lexeme_;
  Value literal_;
  int line_;
};
}  // namespace lox

#endif  // LOX_TOKEN_H_
