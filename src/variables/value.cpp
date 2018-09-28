#include <stdlib.h>
#include "value.hpp"
#include <string>
#include <iostream>
#include "../parser/parser.tab.h"

struct Value* make_long(long num) {
  return new Value(LONG, num, 0, nullptr, "");
}
struct Value* make_double(double dec) {
  return new Value(DOUBLE, 0, dec, nullptr, "");
}
struct Value* make_true() {
  return new Value(BOOLEAN, 1, 0, nullptr, "");
}
struct Value* make_false() {
  return new Value(BOOLEAN, 0, 0, nullptr, "");
}
struct Value* make_boolean(int x) {
  return (x)? make_true() : make_false();
}
struct Value* make_expression(struct Node* expr) {
  return new Value(LAMBDA, 0, 0, expr, "");
}
struct Value* make_string(std::string str) {
  return new Value(STRING, 0, 0, nullptr, str);
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
