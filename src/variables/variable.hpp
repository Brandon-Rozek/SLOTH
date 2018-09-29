#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "../variables/value.hpp"

class Value;
class Node;

class Variable {
  public:
  std::string id;
  Value* value;

  Variable(std::string s, Value* val) {
    id = s;
    value = val;
  }
  ~Variable() {
    delete value;
  }
};

// Variable Functions
void set_value(Variable* var, Value* value);
Value* get_value(const Variable* var);

#endif
