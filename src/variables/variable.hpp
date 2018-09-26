#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "../operations/node.hpp"

struct Variable {
  std::string id;
  struct Value* value;
};

// Variable Functions
struct Variable* make_variable(std::string id, struct Value* value);
void set_value(struct Variable* var, struct Value* value);
struct Value* get_value(struct Variable* var);
struct Value* make_long(long num);
struct Value* make_double(double dec);
struct Value* make_true();
struct Value* make_false();
struct Value* make_boolean(int x);
struct Value* make_expression(struct Node* expr);

#endif
// /* creates a new variable and returns it */
// struct Variable* make_variable(char* id, struct Value* value) {
//   /* allocate space */
//   struct Variable* var = new Variable();

//   /* set properties */
//   strcpy(var->id, id);
//   var->value = value;

//   /* return new variable */
//   return var;
// }