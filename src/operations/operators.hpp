#ifndef OPERATORS_H
#define OPERATORS_H
#include "../variables/value.hpp"

Value* add(Value* x, Value* y);
Value* subtract(Value* x, Value* y);
Value* division(Value* x, Value* y);
Value* multiplication(Value* x, Value* y);
Value* less(Value* x, Value* y);
Value* greater(Value* x, Value* y);
Value* less_equal(Value* x, Value* y);
Value* greater_equal(Value* x, Value* y);
Value* equals(Value* x, Value* y);
Value* not_equals(Value* x, Value* y);
Value* and_value(Value* x, Value* y);
Value* or_value(Value* x, Value* y);
Value* not_value(Value* x);

#endif
