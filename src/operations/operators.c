#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operators.h"
#include "../variables/value.h"

struct Value* add(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in add.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot add a boolean.\n"); }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot add a string with another data type.\n");
  }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) + get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) + get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) + get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_string(strcat(get_string(x), get_string(y)));  
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) + get_double(y));
  }

  return ans;
}

struct Value* subtract(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in subtract.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot subtract a boolean.\n"); }
  if (x->type == STRING || y->type == STRING) { fprintf(stderr, "Error, cannot subtract a string.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) - get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) - get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) - get_long(y));
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) - get_double(y));
  }

  return ans;
}

struct Value* division(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in divide.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot divide a boolean.\n"); }
  if (x->type == STRING || y->type == STRING) { fprintf(stderr, "Error, cannot division a string.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) / get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) / get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) / get_long(y));
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) / get_double(y));
  }

  return ans;
}

struct Value* multiplication(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in multiply.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot multiply a boolean.\n"); }
  if (x->type == STRING || y->type == STRING) { fprintf(stderr, "Error, cannot multiply a string.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) * get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) * get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) * get_long(y));
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) * get_double(y));
  }

  return ans;
}

struct Value* less(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in <.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) < get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) < get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) < get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) < 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) < get_double(y));
  }

  return ans;
}

struct Value* greater(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in greater.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) > get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) > get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) > get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) > 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) > get_double(y));
  }

  return ans;
}

struct Value* less_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in <=.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) <= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) <= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) <= get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) <= 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) <= get_double(y));
  }

  return ans;
}

struct Value* greater_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in >=.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) >= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) >= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) >= get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) >= 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) >= get_double(y));
  }

  return ans;
}

struct Value* equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ==.\n"); }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) == get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) == get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) == get_long(y));
  } else if (x->type == DOUBLE && y->type == DOUBLE) {
    ans = make_boolean(get_double(x) == get_double(y));
  } else if (x->type == BOOLEAN && y->type == BOOLEAN) {
    ans = make_boolean(get_long(x) == get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) == 0);
  } else { // Type is a mix between boolean and another type
    fprintf(stderr, "Error, cannot compare a boolean with another type.\n");
  }

  return ans;
}

struct Value* not_equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in !=.\n"); }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    fprintf(stderr, "Error, cannot compare a string with another data type.\n");
  }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) != get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) != get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) != get_long(y));
  } else if (x->type == DOUBLE && y->type == DOUBLE) {
    ans = make_boolean(get_double(x) != get_double(y));
  } else if (x->type == BOOLEAN && y->type == BOOLEAN) {
    ans = make_boolean(get_long(x) != get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(strcmp(get_string(x), get_string(y)) != 0);
  } else { // Type is a mix between boolean and another type
    fprintf(stderr, "Error, cannot compare a boolean with another type.\n");
  }

  return ans;
}

struct Value* and_value(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in &&.\n"); }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { fprintf(stderr, "Error, cannot use and AND operation with a non-boolean.\n"); }
  if (x->type == STRING || y->type == STRING) { fprintf(stderr, "Error, cannot AND a string.\n"); }

  return make_boolean(get_long(x) && get_long(y));
}

struct Value* or_value(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ||.\n"); }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { fprintf(stderr, "Error, cannot use and OR operation with a non-boolean.\n"); }
  if (x->type == STRING || y->type == STRING) { fprintf(stderr, "Error, cannot OR a string.\n"); }

  return make_boolean(get_long(x) || get_long(y));
}

struct Value* not_value(struct Value* x) {
  if (!x) { fprintf(stderr, "Error, uninitialized values being used in !.\n"); }
  if (x->type != BOOLEAN) { fprintf(stderr, "Error, cannot NOT a non-boolean.\n"); }
  if (x->type == STRING) { fprintf(stderr, "Error, cannot negate a string.\n"); }

  return make_boolean(!get_long(x));
}
