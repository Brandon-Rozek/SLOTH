#include <stdlib.h>
#include "value.h"
#include <string>
#include <iostream>
#include "../parser/parser.tab.h"


struct Value* make_value(TypeTag type, long num, double dec, struct Node* expr, std::string str) {
    /* allocate space */
  struct Value* val = new Value();

  /* set properties */
  val->type = type;
  if (type == LONG || type == BOOLEAN) {
    val->value.num = num;
  } else if (type == DOUBLE){ // Assume DOUBLE
    val->value.dec = dec;
  } else if (type == STRING) {
    val->value.str = str;  
  } else { // Assume lambda expression
    val->value.expr = expr;
  }

  /* return new variable */
  return val;
}

struct Value* make_long(long num) {
  return make_value(LONG, num, 0, NULL, "");
}
struct Value* make_double(double dec) {
  return make_value(DOUBLE, 0, dec, NULL, "");
}
struct Value* make_true() {
  return make_value(BOOLEAN, 1, 0, NULL, "");
}
struct Value* make_false() {
  return make_value(BOOLEAN, 0, 0, NULL, "");
}
struct Value* make_boolean(int x) {
  return (x)? make_true() : make_false();
}
struct Value* make_expression(struct Node* expr) {
  return make_value(LAMBDA, 0, 0, expr, "");
}
struct Value* make_string(std::string str) {
  return make_value(STRING, 0, 0, NULL, str);
}

void delete_value(struct Value* val) {
  free(val);
}

long get_long(struct Value* val) {
  return val->value.num;
}
double get_double(struct Value* val) {
  return val->value.dec;
}
struct Node* get_expression(struct Value* val) {
  return val->value.expr;
}
std::string get_string(struct Value* val) {
  return val->value.str;
}

void set_long(struct Value* val, long num) {
  val->type = LONG;
  val->value.num = num;
}
void set_double(struct Value* val, double dec) {
  val->type = DOUBLE;
  val->value.dec = dec;
}
void set_expression(struct Value* val, struct Node* expr) {
  val->type = LAMBDA;
  val->value.expr = expr;
}
void set_sring(struct Value* val, std::string str) {
  val->type = STRING;
  val->value.str = str;
}

void print_value(struct Value* val) {
  if (val->type == BOOLEAN) {
    if (get_long(val)) {
      std::cout << "true";
    } else {
      std::cout << "false";
    }
  } else if (val->type == LONG) {
    std::cout << get_long(val);
  } else if (val->type == STRING) {
    std::cout << get_string(val);
  } else if (val->type == DOUBLE) {
    std::cout << get_double(val);
  } else { // Assume lambda expression
    std::cout << "<LambdaExpression>";
  }
}
