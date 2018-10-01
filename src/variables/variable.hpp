#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <memory>
#include "../variables/value.hpp"

class Value;
class Node;

class Variable {
  public:
  std::string id;
  std::unique_ptr<Value> value;

  Variable(std::string s, Value* val) : value(std::move(val)) {
    id = s;
  }
  ~Variable() {

  }
};

// Variable Functions
Value* get_value(const Variable* var);

#endif
