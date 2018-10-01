#include <iostream>
#include <algorithm>
#include "operators.hpp"
#include "../variables/value.hpp"

// NOTE: Value* x is what is going to be returned for operations, so that we avoid the need for allocating more memory
 
Value* add(Value* x,Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in add." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot add a boolean." << std::endl; }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot add a string with another data type." << std::endl;
  }
  
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::plus<long>());
    set_long(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::plus<>());
    set_double(x, doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::plus<>());
    set_double(x, doubleResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_string(x, get_string(x) + get_string(y));  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::plus<double>());
    set_double(x, doubleResult);
  }

  delete y;

  return x;
}

Value* subtract(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in subtract." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot subtract a boolean." << std::endl; }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot subtract a string." << std::endl; }
  
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::minus<long>());
    set_long(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::minus<>());
    set_double(x, doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::minus<>());
    set_double(x, doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::minus<double>());
    set_double(x, doubleResult);
  }

  delete y;

  return x;
}

Value* division(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in divide." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot divide a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot division a string." << std::endl;  }
  
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::divides<long>());
    set_long(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::divides<>());
    set_double(x, doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::divides<>());
    set_double(x, doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::divides<double>());
    set_double(x, doubleResult);
  }

  delete y;

  return x;
}

Value* multiplication(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in multiply." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot multiply a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot multiply a string." << std::endl;  }
  
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::multiplies<long>());
    set_long(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::multiplies<>());
    set_double(x, doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::multiplies<>());
    set_double(x, doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::multiplies<double>());
    set_double(x, doubleResult);
  }

  delete y;

  return x;
}

Value* less(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less<long>());
    set_booleans(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::less<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_boolean(x, get_string(x).compare(get_string(y)) < 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::less<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

// CONTINUE REPLACING FROM HERE

Value* greater(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in greater." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater<long>());
    set_booleans(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::greater<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {  
    set_boolean(x, get_string(x).compare(get_string(y)) > 0);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::greater<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

Value* less_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less_equal<long>());
    set_long(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::less_equal<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less_equal<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_boolean(x, get_string(x).compare(get_string(y)) <= 0);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::less_equal<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

Value* greater_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in >=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater_equal<long>());
    set_booleans(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::greater_equal<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater_equal<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_boolean(x, get_string(x).compare(get_string(y)) >= 0);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::greater_equal<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

Value* equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ==." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::equal_to<long>());
    set_booleans(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::equal_to<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::equal_to<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_boolean(x, get_string(x).compare(get_string(y)) == 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::equal_to<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

Value* not_equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in !=." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::not_equal_to<long>());
    set_booleans(x, longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::not_equal_to<>());
    set_booleans(x, longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::not_equal_to<>());
    set_booleans(x, longResult);
  } else if (x->type == STRING && y->type == STRING) {
    set_boolean(x, get_string(x).compare(get_string(y)) != 0);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::not_equal_to<double>());
    set_booleans(x, longResult);
  }

  delete y;

  return x;
}

Value* and_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in &&." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and AND operation with a non-boolean." << std::endl;  }
  
  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::vector<long> y_long = get_long(y);
  std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                  std::back_inserter(longResult), std::logical_and<>());

  set_booleans(x, longResult);

  delete y;

  return x;
}

Value* or_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ||." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and OR operation with a non-boolean." << std::endl;  }

  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::vector<long> y_long = get_long(y);
  std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                  std::back_inserter(longResult), std::logical_or<>());

  set_booleans(x, longResult);

  delete y;

  return x;
}

Value* not_value(Value* x) {
  if (!x) { std::cerr << "Error, uninitialized values being used in !." << std::endl;  }
  if (x->type != BOOLEAN) { std::cerr << "Error, cannot NOT a non-boolean." << std::endl;  }

  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::transform(x_long.begin(), x_long.end(), std::back_inserter(longResult), std::logical_not<>());

  set_booleans(x, longResult);

  return x;
}
