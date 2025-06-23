#include "token.h"
#include <string>
#include <typeinfo>
#include <any>

namespace lox {
std::string Token::to_string() const {
  return tokenTypeToString(type_) + " " + lexeme_ + " " + literalToString();
}

std::string Token::literalToString() const {
  if (auto s = std::get_if<std::string>(&literal_)) {
    return *s;
  } else if (auto d = std::get_if<double>(&literal_)) {
    std::string str = std::to_string(*d);
    str.erase(str.find_last_not_of('0') + 1);
    if (str.back() == '.') {
        str.pop_back();
    }
    return str;
  } else {
    return "";
  }
}
}  // namespace lox
