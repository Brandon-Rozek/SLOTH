#include <iostream>
#include <algorithm>
#include "operators.hpp"
#include "../variables/value.hpp"

// TODO: Now replace every single operation with vector equivalent

Value* add(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in add." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot add a boolean." << std::endl; }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot add a string with another data type." << std::endl;
  }
  
  Value* ans;
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::plus<long>());
    ans = make_long(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::plus<>());
    ans = make_double(doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::plus<>());
    ans = make_double(doubleResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_string(get_string(x) + get_string(y));  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::plus<double>());
    ans = make_double(doubleResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* subtract(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in subtract." << std::endl; }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot subtract a boolean." << std::endl; }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot subtract a string." << std::endl; }
  
  Value* ans;
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::minus<long>());
    ans = make_long(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::minus<>());
    ans = make_double(doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::minus<>());
    ans = make_double(doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::minus<double>());
    ans = make_double(doubleResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* division(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in divide." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot divide a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot division a string." << std::endl;  }
  
  Value* ans;
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::divides<long>());
    ans = make_long(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::divides<>());
    ans = make_double(doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::divides<>());
    ans = make_double(doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::divides<double>());
    ans = make_double(doubleResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* multiplication(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in multiply." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot multiply a boolean." << std::endl;  }
  if (x->type == STRING || y->type == STRING) { std::cerr << "Error, cannot multiply a string." << std::endl;  }
  
  Value* ans;
  std::vector<long> longResult;
  std::vector<double> doubleResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::multiplies<long>());
    ans = make_long(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(doubleResult), std::multiplies<>());
    ans = make_double(doubleResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(doubleResult), std::multiplies<>());
    ans = make_double(doubleResult);
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    doubleResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(doubleResult), std::multiplies<double>());
    ans = make_double(doubleResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* less(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::less<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) < 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::less<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* greater(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in greater." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::greater<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) > 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::greater<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* less_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in <=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less_equal<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::less_equal<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::less_equal<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) <= 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::less_equal<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* greater_equal(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in >=." << std::endl;  }
  if (x->type == BOOLEAN || y->type == BOOLEAN) { std::cerr << "Error, cannot numerically compare a boolean." << std::endl;  }
    if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
      std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }

  Value* ans;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater_equal<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::greater_equal<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::greater_equal<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) >= 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::greater_equal<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ==." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  Value* ans = nullptr;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::equal_to<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::equal_to<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::equal_to<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) == 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::equal_to<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* not_equals(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in !=." << std::endl;  }
  if ((x->type == STRING || y->type == STRING) && (x->type != STRING || y->type != STRING)) {
    std::cerr << "Error, cannot compare a string with another data type." << std::endl; 
  }
  
  Value* ans= nullptr;
  std::vector<long> longResult;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    std::vector<long> x_long = get_long(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                    std::back_inserter(longResult), std::not_equal_to<long>());
    ans = make_booleans(longResult);
  } else if (x->type == LONG && y->type == DOUBLE) {
    std::vector<long> x_long = get_long(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_long.size());
    std::transform(x_long.begin(), x_long.end(), y_double.begin(),
                    std::back_inserter(longResult), std::not_equal_to<>());
    ans = make_booleans(longResult);
  } else if (x->type == DOUBLE && y->type == LONG) {
    std::vector<double> x_double = get_double(x);
    std::vector<long> y_long = get_long(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_long.begin(),
                    std::back_inserter(longResult), std::not_equal_to<>());
    ans = make_booleans(longResult);
  } else if (x->type == STRING && y->type == STRING) {
    ans = make_boolean(get_string(x).compare(get_string(y)) != 0);  
  } else { // Both are DOUBLE
    std::vector<double> x_double = get_double(x);
    std::vector<double> y_double = get_double(y);
    longResult.reserve(x_double.size());
    std::transform(x_double.begin(), x_double.end(), y_double.begin(), 
                    std::back_inserter(longResult), std::not_equal_to<double>());
    ans = make_booleans(longResult);
  }

  delete x;
  delete y;

  return ans;
}

Value* and_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in &&." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and AND operation with a non-boolean." << std::endl;  }
  
  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::vector<long> y_long = get_long(y);
  std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                  std::back_inserter(longResult), std::logical_and<>());

  delete x;
  delete y;

  return make_booleans(longResult);
}

Value* or_value(Value* x, Value* y) {
  if (!x || !y) { std::cerr << "Error, uninitialized values being used in ||." << std::endl;  }
  if (x->type != BOOLEAN || y->type != BOOLEAN) { std::cerr << "Error, cannot use and OR operation with a non-boolean." << std::endl;  }

  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::vector<long> y_long = get_long(y);
  std::transform(x_long.begin(), x_long.end(), y_long.begin(),
                  std::back_inserter(longResult), std::logical_or<>());

  delete x;
  delete y;

  return make_booleans(longResult);
}

Value* not_value(Value* x) {
  if (!x) { std::cerr << "Error, uninitialized values being used in !." << std::endl;  }
  if (x->type != BOOLEAN) { std::cerr << "Error, cannot NOT a non-boolean." << std::endl;  }

  std::vector<long> longResult;
  std::vector<long> x_long = get_long(x);
  std::transform(x_long.begin(), x_long.end(), std::back_inserter(longResult), std::logical_not<>());

  delete x;

  return make_booleans(longResult);
}
