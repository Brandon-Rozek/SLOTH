#include <iostream>
#include <string>
#include "variable.hpp"

Value* get_value(const Variable* var) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return 0; }
  return new Value(*var->value);
}