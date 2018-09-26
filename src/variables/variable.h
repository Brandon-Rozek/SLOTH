#ifndef VARIABLE_H
#define VARIABLE_H

#include "../operations/node.h"

struct Variable {
  char id[ID_SIZE];
  struct Value* value;
};

// Variable Functions
struct Variable* make_variable(char* id, struct Value* value);
void set_value(struct Variable* var, struct Value* value);
struct Value* get_value(struct Variable* var);
struct Value* make_long(long num);
struct Value* make_double(double dec);
struct Value* make_true();
struct Value* make_false();
struct Value* make_boolean(int x);
struct Value* make_expression(struct Node* expr);

#endif
