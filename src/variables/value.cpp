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

long get_long(const Value* val) {
  return std::get<long>(val->val);
}
double get_double(const Value* val) {
  return std::get<double>(val->val);
}
Node* get_expression(const Value* val) {
  return std::get<Node*>(val->val);
}
std::string get_string(const Value* val) {
  return std::get<std::string>(val->val);
}

void set_long(Value* val, long num) {
  val->type = LONG;
  val->val = num;
}
void set_double(Value* val, double dec) {
  val->type = DOUBLE;
  // val->value.dec = dec;
  val->val = dec;
}
void set_expression(Value* val, Node* expr) {
  val->type = LAMBDA;
  val->val = expr;
}
void set_sring(Value* val, std::string str) {
  val->type = STRING;
  val->val = str;
}

std::string Value::toString() const {
  std::string result = "";
  if (this->type == BOOLEAN) {
    if (get_long(this)) {
      result += "true";
    } else {
      result += "false";
    }
  } else if (this->type == LONG) {
    result += get_long(this);
  } else if (this->type == STRING) {
    result += get_string(this);
  } else if (this->type == DOUBLE) {
    result += get_double(this);
  } else { // Assume lambda expression
    result += "<LambdaExpression>";
  }

  return result; 
}

std::ostream & operator << (std::ostream &out, const Value* val) { 
  out << val->toString();
  return out; 
} 
  
