#if !defined(LOX_TOKEN_H_)
#define LOX_TOKEN_H_

#include <any>
#include <string>
#include "util.h"

namespace Lox {
class Token {
 public:
  Token(TokenType type, std::string lexeme, std::any literal, int line)
      : type_(type), lexeme_(lexeme), literal_(literal), line_(line) {}

  std::string to_string() const;

 private:
  std::string literalToString() const;

 private:
  TokenType type_;
  std::string lexeme_;
  std::any literal_;
  int line_;
};
}  // namespace Lox

#endif  // LOX_TOKEN_H_
