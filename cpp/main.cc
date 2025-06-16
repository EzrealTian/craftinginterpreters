#include <iostream>
#include <cstdlib>
#include "lox.h"

int main(int argc, char const *argv[]) {
  Lox::Lox lox;
  if (argc > 2) {
    std::cout << "Usage: cpplox [script]" << std::endl;
    exit(64);
  } else if (argc == 2) {
    // TODO: runfile(argv[0])
    lox.runFile(argv[1]);
  } else {
    // TODO: runPrompt()
    lox.runPrompt();
  }

  return 0;
}
