#include <iostream>
#include <string>
#include <algorithm>
#include "environment.hpp"
#include "variable.hpp"

Variable* find_variable(Environment* env, std::string id) {
  auto result = std::find_if(env->vars.begin(), env->vars.end(), 
    [id](const Variable* element) {
        return element->id == id;
    });

  if (result != env->vars.end()) {
    return *result;
  }

  return nullptr;
}

void add_variable(Environment* env, Variable* var) {
  // If variable exists, replace it
  Variable* temp_var = find_variable(env, var->id);
  if (temp_var != nullptr) {
    temp_var->value = std::unique_ptr<Value>(new Value(*var->value));
    free(var);
    return;
  }

  // If not, add variable to environment
  env->vars.push_back(var);
}

