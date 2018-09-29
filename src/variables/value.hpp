#ifndef VALUE_H
#define VALUE_H

#include "../operations/node.hpp"
#include <iostream>
#include <string>
#include <variant>

class Node;

enum TypeTag { DOUBLE, LONG, BOOLEAN, STRING, LAMBDA };

class Value {
  public:
    enum TypeTag type;
    std::variant<long, double, Node*, std::string> val;

    Value(TypeTag t, long n, double d, Node* e, std::string s) {
      /* set properties */
      type = t;
      
      if (type == LONG || type == BOOLEAN) {
        val = n;
      } else if (type == DOUBLE){ // Assume DOUBLE
        val = d;
      } else if (type == STRING) {
        val = s;  
      } else { // Assume lambda expression
        val = e;
      }
    }

  ~Value() {  
    std::cout << "VALUE DESTROYED" << std::endl;
  }
};

// Constructors
struct Value* make_long(long num);
struct Value* make_double(double dec);
struct Value* make_true();
struct Value* make_false();
struct Value* make_boolean(int x);
struct Value* make_expression(struct Node* expr);
struct Value* make_string(std::string str);

// Destructor
void delete_value(struct Value* val);

// Getters
long get_long(struct Value* val);
double get_double(struct Value* val);
struct Node* get_expression(struct Value* val);
std::string get_string(struct Value* val);

// Setters
void set_long(struct Value* val, long num);
void set_double(struct Value* val, double dec);
void set_expression(struct Value* val, struct Node* node);
void set_string(struct Value* val, std::string str);

void print_value(struct Value* val);

#endif
