#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.hpp"

/* creates a new variable and returns it */
struct Variable* make_variable(char* id, struct Value* value) {
  /* allocate space */
  struct Variable* var = new Variable();

  /* set properties */
  strcpy(var->id, id);
  var->value = value;

  /* return new variable */
  return var;
}

void set_value(struct Variable* var, struct Value* value) {
  if (!var) { fprintf(stderr, "Error: Invalid Variable\n"); return; }
  var->value = value;
}

struct Value* get_value(struct Variable* var) {
  if (!var) { fprintf(stderr, "Error: Invalid Variable\n"); return 0; }
  return var->value;
}