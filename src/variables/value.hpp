#ifndef VALUE_H
#define VALUE_H

#include "../operations/node.hpp"
#include <iostream>
#include <string>
#include <variant>
#include <vector>

class Node;

enum TypeTag { DOUBLE, LONG, BOOLEAN, STRING, LAMBDA };

class Value {
  public:
    enum TypeTag type;
    std::variant<std::vector<long>, std::vector<double>, Node*, std::string> val;

    // << Overload
    friend std::ostream & operator << (std::ostream &out, const Value* val);
    std::string toString() const;

    // Constructor
    Value(TypeTag t, std::vector<long> ns, std::vector<double> ds, Node* e, std::string s) {
      /* set properties */
      type = t;
      
      if (type == LONG || type == BOOLEAN) {
        val = ns;
      } else if (type == DOUBLE){ // Assume DOUBLE
        val = ds;
      } else if (type == STRING) {
        val = s;  
      } else { // Assume lambda expression
        val = e;
      }
    }

    // Copy constructor
    Value(const Value &v) {
      type = v.type;
      val = v.val;
    } 

    // // Copy when assigned
    // Value operator = (const Value &v) {
    //   std::cout << "COPIED" << std::endl;
    //   type = v.type;
    //   val = v.val;
    //   return *this;
    // } 

  // Destructor
  ~Value() {  
    std::cout << "VALUE DESTROYED" << std::endl;
  }
};

// Constructors
Value* make_long(std::vector<long> num);
Value* make_double(std::vector<double> dec);
Value* make_true();
Value* make_false();
Value* make_boolean(int x);
Value* make_booleans(std::vector<long> x);
Value* make_expression(Node* expr);
Value* make_string(std::string str);

// Destructor
void delete_value(Value* val);

// Getters
std::vector<long> get_long(const Value* val);
std::vector<double> get_double(const Value* val);
Node* get_expression(const Value* val);
std::string get_string(const Value* val);

// Setters
void set_long(Value* val, std::vector<long> num);
void set_double(Value* val, std::vector<double> dec);
void set_expression(Value* val, Node* node);
void set_string(Value* val, std::string str);

#endif
