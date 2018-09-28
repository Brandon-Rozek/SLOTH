#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "../operations/node.hpp"

struct Variable {
  std::string id;
  struct Value* value;

  Variable(std::string s, struct Value* val) {
    id = s;
    value = val;
  }
};

// Variable Functions
void set_value(struct Variable* var, struct Value* value);
struct Value* get_value(struct Variable* var);
struct Value* make_long(long num);
struct Value* make_double(double dec);
struct Value* make_true();
struct Value* make_false();
struct Value* make_boolean(int x);
struct Value* make_expression(struct Node* expr);

#endif
