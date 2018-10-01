#include <stdlib.h>
#include "value.hpp"
#include <string>
#include <iostream>
#include <variant>
#include <algorithm>
#include "../parser/parser.tab.h"

Value* make_long(std::vector<long> nums) {
  std::vector<double> decs;
  return new Value(LONG, nums, decs, nullptr, "");
}
Value* make_double(std::vector<double> decs) {
  std::vector<long> nums;
  return new Value(DOUBLE, nums, decs, nullptr, "");
}
Value* make_true() {
  std::vector<long> nums = {1};  
  std::vector<double> decs;
  return new Value(BOOLEAN, nums, decs, nullptr, "");
}
Value* make_false() {
  std::vector<long> nums = {0};
  std::vector<double> decs;
  return new Value(BOOLEAN, nums, decs, nullptr, "");
}

Value* make_boolean(int x) {
  return (x) ? make_true() : make_false();
}

Value* make_booleans(std::vector<long> x) {
  std::vector<double> decs;

  std::vector<long> result;
  std::transform(x.begin(), x.end(), std::back_inserter(result), 
    [] (long n) {
      return n != 0;
  });
  return new Value(BOOLEAN, result, decs, nullptr, "");
}
Value* make_expression(Node* expr) {
  std::vector<long> nums;
  std::vector<double> decs;
  return new Value(LAMBDA, nums, decs, expr, "");
}
Value* make_string(std::string str) {
  std::vector<long> nums;
  std::vector<double> decs;
  return new Value(STRING, nums, decs, nullptr, str);
}

void delete_value(Value* val) {
  free(val);
}

std::vector<long> get_long(const Value* val) {
  return std::get<std::vector<long>>(val->val);
}
std::vector<double> get_double(const Value* val) {
  return std::get<std::vector<double>>(val->val);
}
Node* get_expression(const Value* val) {
  return std::get<Node*>(val->val);
}
std::string get_string(const Value* val) {
  return std::get<std::string>(val->val);
}

void set_long(Value* val, std::vector<long> num) {
  val->type = LONG;
  val->val = num;
}
void set_boolean(Value* val, int x) {
  val->type = BOOLEAN;
  std::vector<long> result;
  if (x) { result.push_back(1); } else { result.push_back(0); }
  val->val = result;
}
void set_booleans(Value* val, std::vector<long> num) {
  val->type = BOOLEAN;
  val->val = num;
}
void set_double(Value* val, std::vector<double> dec) {
  val->type = DOUBLE;
  // val->value.dec = dec;
  val->val = dec;
}
void set_expression(Value* val, Node* expr) {
  val->type = LAMBDA;
  val->val = expr;
}
void set_string(Value* val, std::string str) {
  val->type = STRING;
  val->val = str;
}

std::string Value::toString() const {
  std::string result = "";
  if (this->type == BOOLEAN) {
    std::vector<long> longVec = get_long(this);
    if (longVec.size() == 1) {
      result += (longVec[0]) ? "true" : "false";
    } else {
      result += "[";
      for (uint i = 0; i < longVec.size() - 1; i++) {
        result += (longVec[i]) ? "true" : "false";
        result += ", ";
      }
      result += (longVec[longVec.size() - 1]) ? "true" : "false";
      result += "]";
    }
  } else if (this->type == LONG) {
    std::vector<long> longVec = get_long(this);
    if (longVec.size() == 1) {
      result += std::to_string(longVec[0]);
    } else {
      result += "[";
      for (uint i = 0; i < longVec.size() - 1; i++) {
        result += std::to_string(longVec[i]);
        result += ", ";
      }
      result += std::to_string(longVec[longVec.size() - 1]);
      result += "]";
    }
  } else if (this->type == STRING) {
    result += get_string(this);
  } else if (this->type == DOUBLE) {
    std::vector<double> longVec = get_double(this);
    if (longVec.size() == 1) {
      result += std::to_string(longVec[0]);
    } else {
      result += "[";
      for (uint i = 0; i < longVec.size() - 1; i++) {
        result += std::to_string(longVec[i]);
        result += ", ";
      }
      result += std::to_string(longVec[longVec.size() - 1]);
      result += "]";
    }
  } else { // Assume lambda expression
    result += "<LambdaExpression>";
  }

  return result; 
}

std::ostream & operator << (std::ostream &out, const Value* val) { 
  out << val->toString();
  return out; 
} 
  
