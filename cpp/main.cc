#include <iostream>
#include <cstdlib>
#include "lox.h"
#include "expr.h"
#include "token.h"
#include <memory>

int main(int argc, char const *argv[]) {
  lox::Lox lox;
  if (argc > 2) {
    std::cout << "Usage: cpplox [script]" << std::endl;
    exit(64);
  } else if (argc == 2) {
    lox.runFile(argv[1]);
  } else {
    lox.runPrompt();
  }
  return 0;
}
