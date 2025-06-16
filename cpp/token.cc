#include "token.h"
#include <string>
#include <typeinfo>
#include <any>

namespace Lox {
std::string Token::to_string() const {
  return tokenTypeToString(type_) + " " + lexeme_ + " " + literalToString();
}

std::string Token::literalToString() const {
  if (literal_.type() == typeid(std::string)) {
    return std::any_cast<std::string>(literal_);
  } else if (literal_.type() == typeid(double)) {
    return std::to_string(std::any_cast<double>(literal_));
  } else {
    return "";
  }
}
}  // namespace Lox
