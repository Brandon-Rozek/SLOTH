#include <iostream>
#include <string>
#include "variable.hpp"

void set_value(Variable* var, Value* value) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return; }
  var->value = value;
}

Value* get_value(const Variable* var) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return 0; }
  return var->value;
}