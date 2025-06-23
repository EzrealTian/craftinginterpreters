

out_path = "./"


type_list = [
  "Binary   : Expr left, Token op, Expr right",
  "Grouping : Expr expression",
  "Literal  : std::any value",
  "Unary    : Token op, Expr right"
]

def define_type(file, class_name, fields):
  field_list = fields.split(", ")
  file.write(f"class {class_name}: public Expr {{\n")
  file.write(f"public:\n")
  file.write(f"  {class_name}({fields}) : ")
  for idx, field in enumerate(field_list):
    if idx > 0:
      file.write(", ")
    file.write(f"{field.split()[1]}_({field.split()[1]})")
  file.write("{}\n")

  file.write("\n  void visitExpr() override;\n")

  file.write("\nprivate:\n")
  for field in field_list:
    file.write(f"  {field.split()[0]} {field.split()[1]}_;\n")
  file.write(f"}};\n\n")

def define_ast(base_name, types):
  out_file = out_path + base_name + ".h"
  with open(out_file, 'w', encoding='utf-8') as file:
    file.write("#if !defined(LOX_EXPR_H_)\n")
    file.write("#define LOX_EXPR_H_\n\n")
    file.write("#include <any>\n")
    file.write("#include \"token.h\"\n\n")
    file.write("namespace lox\n{\n")

    file.write("class Expr {\n  virtual void visitExpr();\n};\n\n")

    for t in type_list:
      class_name = t.split(":")[0].strip()
      fields = t.split(" : ")[1].strip()
      define_type(file, class_name, fields)

    file.write("} // namespace lox\n\n")
    file.write("#endif // LOX_EXPR_H_\n")

define_ast("expr", None)