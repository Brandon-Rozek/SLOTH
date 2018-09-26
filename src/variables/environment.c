#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "variable.h"

struct Environment* create_environment(void) {
  struct Environment* env = malloc(sizeof(struct Environment));
  env->num_vars = 0;
  for(int i = 0; i < MAX_VARIABLES; i++) {
    env->vars[i] = NULL;
  }
  return env;
}

struct Variable* find_variable(struct Environment* env, char* id) {
  for (int i = 0; i < env->num_vars; i++) {
    if (strcmp(env->vars[i]->id, id) == 0) {
      return env->vars[i];
    }
  }
  return NULL;
}

void add_variable(struct Environment* env, struct Variable* var) {
  if (env->num_vars >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Maximum number of variables reached.\n");
    return;
  }

  // If variable exists, replace it
  struct Variable* temp_var = find_variable(env, var->id);
  if (temp_var != NULL) {
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
