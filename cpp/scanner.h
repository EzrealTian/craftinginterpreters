#if !defined(LOX_SCANNER_H_)
#define LOX_SCANNER_H_

#include <vector>
#include "util.h"
#include "token.h"

namespace lox {
class Scanner {
 public:
  Scanner(std::string source) : source_(source) {}

  // scan to the end of input to get a list of Token
  std::vector<Token> scanTokens();

 private:
  // whether or not at the end of file
  bool isAtEnd() const;

  // scan single token
  void scanToken();

  // get current character and move forward
  char advance();

  void addToken(TokenType type);

  void addToken(TokenType type, Value literal);

  // check current character, if match then move forward
  bool match(char expected);

  bool isDigit(char ch) const;

  bool isAlpha(char ch) const;

  bool isAlphaNum(char ch) const;

  // get current character
  char peek() const;

  // get next character
  char peekNext() const;

  void string();

  void number();

  void identifier();

  void blockComment();

 private:
  std::string source_;
  std::vector<Token> tokens_;

  int start_ = 0;
  int current_ = 0;
  int line_ = 1;
};
}  // namespace lox

#endif  // LOX_SCANNER_H_
