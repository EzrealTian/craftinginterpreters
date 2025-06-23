#if !defined(LOX_EXPR_H_)
#define LOX_EXPR_H_

#include <any>
#include <string>
#include <initializer_list>
#include <memory>
#include "token.h"

namespace lox {
class Expr {
 public:
  virtual std::string exprToString() const = 0;
  virtual ~Expr() = default;

 protected:
  std::string parenthesize(
      std::string name,
      std::initializer_list<std::shared_ptr<Expr>> exprs) const;
};

class Binary : public Expr {
 public:
  Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
      : left_(left), op_(op), right_(right) {}

  std::string exprToString() const override;

 private:
  std::shared_ptr<Expr> left_;
  Token op_;
  std::shared_ptr<Expr> right_;
};

class Grouping : public Expr {
 public:
  Grouping(std::shared_ptr<Expr> expression) : expression_(expression) {}

  std::string exprToString() const override;

 private:
  std::shared_ptr<Expr> expression_;
};

class Literal : public Expr {
 public:
  Literal(Value value) : value_(value) {}
  explicit Literal(int value) : value_(static_cast<double>(value)) {}
  explicit Literal(double value) : value_(value) {}

  std::string exprToString() const override;

 private:
  Value value_;
};

class Unary : public Expr {
 public:
  Unary(Token op, std::shared_ptr<Expr> right) : op_(op), right_(right) {}

  std::string exprToString() const override;

 private:
  Token op_;
  std::shared_ptr<Expr> right_;
};

}  // namespace lox

#endif  // LOX_EXPR_H_
