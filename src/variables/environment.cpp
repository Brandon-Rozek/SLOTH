#include <iostream>
#include <string>
#include "environment.hpp"
#include "variable.hpp"

struct Environment* create_environment(void) {
  struct Environment* env = new Environment();
  env->num_vars = 0;
  for(int i = 0; i < MAX_VARIABLES; i++) {
    env->vars[i] = nullptr;
  }
  return env;
}

struct Variable* find_variable(struct Environment* env, std::string id) {
  for (int i = 0; i < env->num_vars; i++) {
    if (id.compare(env->vars[i]->id) == 0) {
      return env->vars[i];
    }
  }
  return nullptr;
}

void add_variable(struct Environment* env, struct Variable* var) {
  if (env->num_vars >= MAX_VARIABLES) {
    std::cerr << "Error: Maximum number of variables reached." << std::endl;
    return;
  }

  // If variable exists, replace it
  struct Variable* temp_var = find_variable(env, var->id);
  if (temp_var != nullptr) {
    temp_var->value = var->value;
    free(var);
    return;
  }

  // If not, add variable to environment
  env->vars[env->num_vars] = var;
  env->num_vars += 1;
}

void delete_environment(struct Environment* env) {
  for (int i = 0; i < env->num_vars; i++) {
    free(env->vars[i]);
  }
  free(env);
}
