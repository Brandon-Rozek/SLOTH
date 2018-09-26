#include <stdlib.h>
#include "value.h"
#include "../parser/parser.tab.h"


struct Value* make_value(int type, long num, double dec, struct Node* expr) {
    /* allocate space */
  struct Value* val = malloc(sizeof(struct Value));

  /* set properties */
  val->type = type;
  if (type == LONG || type == BOOLEAN) {
    val->value.num = num;
  } else if (type == DOUBLE){ // Assume DOUBLE
    val->value.dec = dec;
  } else { // Assume lambda expression
    val->value.expr = expr;
  }

  /* return new variable */
  return val;
}

struct Value* make_long(long num) {
  return make_value(LONG, num, 0, NULL);
}
struct Value* make_double(double dec) {
  return make_value(DOUBLE, 0, dec, NULL);
}
struct Value* make_true() {
  return make_value(BOOLEAN, 1, 0, NULL);
}
struct Value* make_false() {
  return make_value(BOOLEAN, 0, 0, NULL);
}
struct Value* make_boolean(int x) {
  return (x)? make_true() : make_false();
}
struct Value* make_expression(struct Node* expr) {
  return make_value(LAMBDA, 0, 0, expr);
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
