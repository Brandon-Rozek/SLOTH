#include <iostream>
#include <string>
#include "variable.hpp"

void set_value(struct Variable* var, struct Value* value) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return; }
  var->value = value;
}

struct Value* get_value(struct Variable* var) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return 0; }
  return var->value;
}