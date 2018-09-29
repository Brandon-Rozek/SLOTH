#include <iostream>
#include "operators.hpp"
#include "../variables/value.hpp"

Value* add(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in add." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot add a boolean." << std::endl; }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot add a string with another data type." << std::endl;
  }
  
  Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_long(get_long(x) + get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_double(get_long(x) + get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_double(get_double(x) + get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_string(get_string(x) + get_string(y));  
  } else { // Both are DOUBLE
    ans = make_double(get_double(x) + get_double(y));
  }

  return ans;
}

Value* subtract(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in subtract." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot subtract a boolean." << std::endl; }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot subtract a string." << std::endl; }
  
  Value* ans;

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

Value* division(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in divide." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot divide a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot division a string." << std::endl;  }
  
  Value* ans;

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

Value* multiplication(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in multiply." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot multiply a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot multiply a string." << std::endl;  }
  
  Value* ans;

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

Value* less(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) < get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) < get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) < get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) < 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) < get_double(y));
  }

  return ans;
}

Value* greater(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in greater." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) > get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) > get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) > get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) > 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) > get_double(y));
  }

  return ans;
}

Value* less_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) <= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) <= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) <= get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) <= 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) <= get_double(y));
  }

  return ans;
}

Value* greater_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in >=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_boolean(get_long(x) >= get_long(y));
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_boolean(get_long(x) >= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_boolean(get_double(x) >= get_long(y));
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) >= 0);
  } else { // Both are DOUBLE
    ans = make_boolean(get_double(x) >= get_double(y));
  }

  return ans;
}

Value* equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ==." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  Value* ans = nullptr;

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
    ans = make_boolean(get_string(x).compare(get_string(y)) == 0);
  } else { // Type is a mix between boolean and another type
    std::cerr << "Error, cannot compare a boolean with another type." << std::endl; 
  }

  return ans;
}

Value* not_equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in !=." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  Value* ans= nullptr;

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
    ans = make_boolean(get_string(x).compare(get_string(y)) != 0);
  } else { // Type is a mix between boolean and another type
    std::cerr << "Error, cannot compare a boolean with another type." << std::endl; 
  }

  return ans;
}

Value* and_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in &&." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and AND operation with a non-boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot AND a string." << std::endl;  }

  return make_boolean(get_long(x) && get_long(y));
}

Value* or_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ||." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and OR operation with a non-boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot OR a string." << std::endl;  }

  return make_boolean(get_long(x) || get_long(y));
}

Value* not_value(Value* x) {
  if (!x) { std::cerr << "Error, uninitialized values being used in !." << std::endl;  }
  if (x->type != BOOLEAN) { std::cerr << "Error, cannot NOT a non-boolean." << std::endl;  }
  if (x->type == STRING) { std::cerr << "Error, cannot negate a string." << std::endl;  }

  return make_boolean(!get_long(x));
}
