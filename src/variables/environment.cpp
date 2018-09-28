#include <iostream>
#include <string>
#include "environment.hpp"
#include "variable.hpp"

struct Environment* create_environment(void) {
  struct Environment* env = new Environment();
  return env;
}

struct Variable* find_variable(struct Environment* env, std::string id) {
  for (uint i = 0; i < size(env->vars); i++) {
    if (id.compare(env->vars[i]->id) == 0) {
      return env->vars[i];
    }
  }
  return nullptr;
}

void add_variable(struct Environment* env, struct Variable* var) {
  // If variable exists, replace it
  struct Variable* temp_var = find_variable(env, var->id);
  if (temp_var != nullptr) {
    temp_var->value = var->value;
    free(var);
    return;
  }

  // If not, add variable to environment
  env->vars.push_back(var);
}

void delete_environment(struct Environment* env) {
  for (uint i = 0; i < size(env->vars); i++) {
    free(env->vars[i]);
  }
  free(env);
}
