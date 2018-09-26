#ifndef OPERATORS_H
#define OPERATORS_H

struct Value* add(struct Value* x, struct Value* y);
struct Value* subtract(struct Value* x, struct Value* y);
struct Value* division(struct Value* x, struct Value* y);
struct Value* multiplication(struct Value* x, struct Value* y);
struct Value* less(struct Value* x, struct Value* y);
struct Value* greater(struct Value* x, struct Value* y);
struct Value* less_equal(struct Value* x, struct Value* y);
struct Value* greater_equal(struct Value* x, struct Value* y);
struct Value* equals(struct Value* x, struct Value* y);
struct Value* not_equals(struct Value* x, struct Value* y);
struct Value* and(struct Value* x, struct Value* y);
struct Value* or(struct Value* x, struct Value* y);
struct Value* not(struct Value* x);

#endif
