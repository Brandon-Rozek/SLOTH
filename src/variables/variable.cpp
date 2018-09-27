#include <iostream>
#include <string>
#include "variable.hpp"

/* creates a new variable and returns it */
struct Variable* make_variable(std::string id, struct Value* value) {
  /* allocate space */
  struct Variable* var = new Variable();

  /* set properties */
  var->id = id;
  var->value = value;

  /* return new variable */
  return var;
}

void set_value(struct Variable* var, struct Value* value) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return; }
  var->value = value;
}

struct Value* get_value(struct Variable* var) {
  if (!var) { std::cerr << "Error: Invalid Variable" << std::endl; return 0; }
  return var->value;
}