#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#define MAX_VARIABLES 200

struct Environment {
  int num_vars;
  struct Variable* vars[MAX_VARIABLES];
};

// Variable Lookup Functions
struct Environment* create_environment(void);
void delete_environment(struct Environment* env);
struct Variable* find_variable(struct Environment* env, std::string id);
void add_variable(struct Environment* env, struct Variable* var);

#endif
