#include <stdio.h>
#include <stdlib.h>
#include "operators.h"
#include "../variables/value.h"

struct Value* add(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in add.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot add a boolean.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) + get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) + get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) + get_long(y));
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) + get_double(y));
  }

  return ans;
}

struct Value* subtract(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in subtract.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot subtract a boolean.\n"); }
  
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

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) < get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) < get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) < get_long(y));
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) < get_double(y));
  }

  return ans;
}

struct Value* greater(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in greater.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) > get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) > get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) > get_long(y));
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) > get_double(y));
  }

  return ans;
}

struct Value* less_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in <=.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) <= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) <= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) <= get_long(y));
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) <= get_double(y));
  }

  return ans;
}

struct Value* greater_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in >=.\n"); }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { fprintf(stderr, "Error, cannot numerically compare a boolean.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) >= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) >= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) >= get_long(y));
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) >= get_double(y));
  }

  return ans;
}

struct Value* equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ==.\n"); }
  
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
  } else { // Type is a mix between boolean and another type
    fprintf(stderr, "Error, cannot compare a boolean with another type.\n");
  }

  return ans;
}

struct Value* not_equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in !=.\n"); }
  
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
  } else { // Type is a mix between boolean and another type
    fprintf(stderr, "Error, cannot compare a boolean with another type.\n");
  }

  return ans;
}

struct Value* and(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in &&.\n"); }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { fprintf(stderr, "Error, cannot use and AND operation with a non-boolean.\n"); }

  return make_boolean(get_long(x) && get_long(y));
}

struct Value* or(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ||.\n"); }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { fprintf(stderr, "Error, cannot use and OR operation with a non-boolean.\n"); }

  return make_boolean(get_long(x) || get_long(y));
}

struct Value* not(struct Value* x) {
  if (!x) { fprintf(stderr, "Error, uninitialized values being used in !.\n"); }
  if (x->type != BOOLEAN) { fprintf(stderr, "Error, cannot NOT a non-boolean.\n"); }

  return make_boolean(!get_long(x));
}
