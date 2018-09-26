#ifndef VALUE_H
#define VALUE_H

#include <string>

enum TypeTag { DOUBLE, LONG, BOOLEAN, STRING, LAMBDA };

union TypeVal {
  long num;
  double dec;
  struct Node* expr;
  std::string str;
  TypeVal() {} 
  // TypeVal(const std::string& s) : str(s) {} // Construct Point object using initializer list.
  // TypeVal& operator=(const std::string& s) { new(&str) std::string(s); return *this; } // Assign Point object using placement 'new'.
  ~TypeVal() {}
};

struct Value {
  enum TypeTag type;
  TypeVal value;
};

// Constructors
struct Value* make_value(int type, long num, double dec, struct Node* expr, std::string str);
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
