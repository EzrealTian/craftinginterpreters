#include "lox.h"
#include "scanner.h"
#include <string>
#include <fstream>
#include <iostream>

namespace Lox {
bool Lox::has_error_ = false;

void Lox::runFile(std::string path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) throw std::runtime_error("Cannot open file: " + path);

  // 使用迭代器读取全部内容
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  run(content);

  if (has_error_) exit(65);
}

void Lox::runPrompt() {
  std::string line;
  for (;;) {
    std::cout << "> ";
    if (!getline(std::cin, line)) {
      break;
    }
    run(line);
    has_error_ = false;
  }
}

void Lox::run(std::string source) { 
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  
  for (auto token : tokens) {
    std::cout << token.to_string() << std::endl;
  }
}

void Lox::error(int line, std::string msg) { report(line, "", msg); }

void Lox::report(int line, std::string where, std::string msg) {
  std::cerr << "[line " << line << "] Error" << where << ": " << msg
            << std::endl;
  has_error_ = true;
}
}  // namespace Lox