#include <stdlib.h>
#include "value.hpp"
#include <string>
#include <iostream>
#include <variant>
#include "../parser/parser.tab.h"

Value* make_long(long num) {
  return new Value(LONG, num, 0, nullptr, "");
}
Value* make_double(double dec) {
  return new Value(DOUBLE, 0, dec, nullptr, "");
}
Value* make_true() {
  return new Value(BOOLEAN, 1, 0, nullptr, "");
}
Value* make_false() {
  return new Value(BOOLEAN, 0, 0, nullptr, "");
}
Value* make_boolean(int x) {
  return (x)? make_true() : make_false();
}
Value* make_expression(Node* expr) {
  return new Value(LAMBDA, 0, 0, expr, "");
}
Value* make_string(std::string str) {
  return new Value(STRING, 0, 0, nullptr, str);
}

void delete_value(Value* val) {
  free(val);
}

long get_long(Value* val) {
  // return val->value.num;
  return std::get<long>(val->val);
}
double get_double(Value* val) {
  // return val->value.dec;
  return std::get<double>(val->val);
}
Node* get_expression(Value* val) {
  // return val->value.expr;
  return std::get<Node*>(val->val);
}
std::string get_string(Value* val) {
  // return val->value.str;
  return std::get<std::string>(val->val);
}

void set_long(Value* val, long num) {
  val->type = LONG;
  // val->value.num = num;
  val->val = num;
}
void set_double(Value* val, double dec) {
  val->type = DOUBLE;
  // val->value.dec = dec;
  val->val = dec;
}
void set_expression(Value* val, Node* expr) {
  val->type = LAMBDA;
  // val->value.expr = expr;
  val->val = expr;
}
void set_sring(Value* val, std::string str) {
  val->type = STRING;
  // val->value.str = str;
  val->val = str;
}

void print_value(Value* val) {
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
