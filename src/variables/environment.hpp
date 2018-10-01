#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "variable.hpp"
#include <string>
#include <vector>

class Variable;

class Environment {
  public:
  std::vector<Variable*> vars;
  Environment() {  }
  ~Environment();
};

// Variable Lookup Functions
Variable* find_variable(Environment* env, std::string id);
void add_variable(Environment* env, Variable* var);

#endif
