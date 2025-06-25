#include <memory>
#include <string>
#include <initializer_list>
#include "expr.h"

namespace lox {
std::string Expr::parenthesize(
    std::string name,
    std::initializer_list<std::shared_ptr<Expr>> exprs) const {
  std::string result;
  result += "(" + name;
  for (auto expr : exprs) {
    result += " ";
    result += expr->exprToString();
  }
  result += ")";
  return result;
}

std::string Binary::exprToString() const {
  return parenthesize(op_.getLexeme(), {left_, right_});
}

std::string Binary::convertToRPN() const {
  return left_->convertToRPN() + " " + right_->convertToRPN() + " " + op_.getLexeme();
}

std::string Grouping::exprToString() const {
  return parenthesize("group", {expression_});
}

std::string Grouping::convertToRPN() const {
  return expression_->convertToRPN();
}

std::string Literal::exprToString() const {
  if (auto s = std::get_if<std::string>(&value_)) {
    return *s;
  } else if (auto d = std::get_if<double>(&value_)) {
    std::string str = std::to_string(*d);
    str.erase(str.find_last_not_of('0') + 1);
    if (str.back() == '.') {
        str.pop_back();
    }
    return str;
  } else {
    return "nil";
  }
}

std::string Literal::convertToRPN() const {
  return this->exprToString();
}

std::string Unary::exprToString() const {
  return parenthesize(op_.getLexeme(), {right_});
}

std::string Unary::convertToRPN() const {
  return right_->convertToRPN() + " " + op_.getLexeme();
}

}  // namespace lox
