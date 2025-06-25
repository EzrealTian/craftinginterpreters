#include <iostream>
#include <cstdlib>
#include "lox.h"
#include "expr.h"
#include "token.h"
#include <memory>

void testExprToString() {
  auto expr = std::make_shared<lox::Binary>(
    std::make_shared<lox::Grouping>(
      std::make_shared<lox::Binary>(
        std::make_shared<lox::Literal>(1),
        lox::Token(lox::TokenType::PLUS, "+", nullptr, 1),
        std::make_shared<lox::Literal>(2)
      )
    ),
    lox::Token(lox::TokenType::STAR, "*", nullptr, 1),
    std::make_shared<lox::Grouping>(
      std::make_shared<lox::Binary>(
        std::make_shared<lox::Literal>(4),
        lox::Token(lox::TokenType::MINUS, "-", nullptr, 1),
        std::make_shared<lox::Literal>(3)
      )
    )
  );
  std::cout << expr->exprToString() << std::endl;
}

void testExprToRPN() {
  auto expr = std::make_shared<lox::Binary>(
    std::make_shared<lox::Grouping>(
      std::make_shared<lox::Binary>(
        std::make_shared<lox::Literal>(1),
        lox::Token(lox::TokenType::PLUS, "+", nullptr, 1),
        std::make_shared<lox::Literal>(2)
      )
    ),
    lox::Token(lox::TokenType::STAR, "*", nullptr, 1),
    std::make_shared<lox::Grouping>(
      std::make_shared<lox::Binary>(
        std::make_shared<lox::Literal>(4),
        lox::Token(lox::TokenType::MINUS, "-", nullptr, 1),
        std::make_shared<lox::Literal>(3)
      )
    )
  );
  std::cout << expr->convertToRPN() << std::endl;
}