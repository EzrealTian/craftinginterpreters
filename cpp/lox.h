#if !defined(LOX_LOX_H_)
#define LOX_LOX_H_

#include <string>
#include "token.h"

namespace lox {
class Lox {
 public:
  Lox() = default;
  ~Lox() = default;

  // compile from file
  void runFile(std::string path);
  // compile from user input
  void runPrompt();

  // report the compile error, include the reason and the location line
  static void error(int line, std::string msg);
  static void error(Token token, std::string msg);

 private:
  // report message to the console
  static void report(int line, std::string where, std::string msg);

  // core function
  void run(std::string source);

 private:
  static bool has_error_;
};
}  // namespace lox

#endif  // LOX_LOX_H_
