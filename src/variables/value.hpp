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

    // << Overload
    friend std::ostream & operator << (std::ostream &out, const Value* val);
    std::string toString() const;

    // Constructor
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

  // Destructor
  ~Value() {  
    std::cout << "VALUE DESTROYED" << std::endl;
  }
};

// Constructors
Value* make_long(long num);
Value* make_double(double dec);
Value* make_true();
Value* make_false();
Value* make_boolean(int x);
Value* make_expression(Node* expr);
Value* make_string(std::string str);

// Destructor
void delete_value(Value* val);

// Getters
long get_long(const Value* val);
double get_double(const Value* val);
Node* get_expression(const Value* val);
std::string get_string(const Value* val);

// Setters
void set_long(Value* val, long num);
void set_double(Value* val, double dec);
void set_expression(Value* val, Node* node);
void set_string(Value* val, std::string str);

#endif
