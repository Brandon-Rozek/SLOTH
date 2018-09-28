#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "variable.hpp"
#include <string>
#include <vector>

struct Environment {
  std::vector<struct Variable*> vars;
  Environment() {  }
  // ~Environment() { 
  //   for (uint i = 0; i < size(vars); i++) {
  //       delete vars[i];
  //   }
  // }
};

// Variable Lookup Functions
void delete_environment(struct Environment* env);
struct Variable* find_variable(struct Environment* env, std::string id);
void add_variable(struct Environment* env, struct Variable* var);

#endif
