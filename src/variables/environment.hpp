#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>

struct Environment {
  std::vector<struct Variable*> vars;
};

// Variable Lookup Functions
struct Environment* create_environment(void);
void delete_environment(struct Environment* env);
struct Variable* find_variable(struct Environment* env, std::string id);
void add_variable(struct Environment* env, struct Variable* var);

#endif
