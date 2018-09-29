#include <iostream>
#include <string>
#include "node.hpp"
#include "operators.hpp"
#include "../constants.hpp"
#include "../parser/parser.tab.h"
#include "../variables/value.hpp"
#include "../variables/variable.hpp"

/* attach an existing node onto a parent */
void attach_node(Node* parent, Node* child) {
  /* connect it */
  parent->children[parent->num_children] = child;
  parent->num_children++;
  if (parent->num_children > MAX_CHILDREN) { std::cerr << "Error, max children attached to a node" << std::endl; }
}

void check_num_nodes(Node* node, uint num_children, std::string error) {
  if (node && node->num_children != num_children) {
    std::cerr << "Error, " << error << std::endl;
  }
}

std::ostream & operator << (std::ostream &out, const Node* n) { 
  out << n->toString();
  return out;
}

std::string Node::toString() const {
  return tree_string(this, 0);
}

std::string tree_string(const Node* node, uint tabs) {
  std::string result = "";
  uint i;
  /* base case */
  if(!node) {
    result += "NO TREE STRUCTURE\n";
    return result;
  }

  /* print leading tabs */
  for(i = 0; i < tabs; i++) {
    result += "    ";
  }

  switch(node->type) {
    case IDENTIFIER: result += "IDENTIFIER: " + node->id + "\n"; break;
    case PLUS: result += "PLUS:\n"; break;
    case MINUS: result += "MINUS:\n"; break;
    case DIVIDE: result += "DIVIDE:\n"; break;
    case TIMES: result += "TIMES:\n"; break;
    case LESS: result += "LESS THAN:\n"; break;
    case GREATER: result += "GREATER:\n"; break;
    case LESSEQ: result += "LESS EQUAL:\n"; break;
    case GREATEREQ: result += "GREATER EQUAL:\n"; break;
    case EQUALS: result += "EQUAL:\n"; break;
    case NEQUALS: result += "NOT EQUAL:\n"; break;
    case AND: result += "AND:\n"; break;
    case OR: result += "OR:\n"; break;
    case NOT: result += "NOT:\n"; break;
    case ASSIGN: result += "ASSIGN:\n"; break;
    case IF: result += "IF:\n"; break;
    case WHILE: result += "WHILE:\n"; break;
    case PRINT: result += "PRINT:\n"; break;
    case INPUT: result += "INPUT:\n"; break;
    case LAMBDATAG: result += "LAMBDA:\n"; break;
    case CALLFUNC: result += "FUNCCALL:\n"; break;
    case STATEMENT: result += "STATEMENT:\n"; break;
    case VALUE: result += "VALUE: " + node->value->toString() + "\n"; break;
    default:
      std::cerr << "Error, " << node->type << " is not a valid node type." << std::endl;
      exit(1);
  }

  /* print all children nodes underneath */
  for(i = 0; i < node->num_children; i++) {
    result += tree_string(node->children[i], tabs + 1);
  }

  return result;
}

Value* eval_expression(Node* node, Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return 0;
  }

  // Needed if we are going to take input from the user
  double temp;
  Variable* var = nullptr;
  Environment* local_env = nullptr;
  Node* tempNode = nullptr;
  Value* tempVal = nullptr;

  // Evaluate subexpressions if existent and node is not a lambda expression
  Value* val1 = nullptr;
  Value* val2 = nullptr;
  // struct Value* val3 = nullptr;
  if (node->num_children > 0 && node->type != LAMBDATAG) {
    val1 = eval_expression(node->children[0], env);
    if (node->num_children > 1) {
      val2 = eval_expression(node->children[1], env);
      // if (node->num_children > 2) {
        // val3 = eval_expression(node->children[2], env);
      // }
    }
  }

  switch(node->type) {
    case LAMBDATAG: return make_expression(node); break;
    case CALLFUNC:
      check_num_nodes(node, 2, "cannot have more than two nodes for a function call.");
      tempNode = get_expression(get_value(find_variable(env, node->children[0]->id)));
      local_env = new Environment();
      add_variable(local_env, 
        new Variable(tempNode->children[0]->id, // Get the name of the variable needed for the lambda expression
          eval_expression(node->children[1], env)));
      tempVal =  eval_expression(tempNode->children[1], local_env);
      delete local_env;
      return tempVal;
      break;
    case PLUS:
      check_num_nodes(node, 2, "cannot add more than two expressions.");
      return add(val1, val2);
      // return val1 + val2;
      break;
    //----------
    case MINUS:
      check_num_nodes(node, 2, "cannot subtract more than two expressions.");
      return subtract(val1, val2);
      // return val1 - val2;
      break;
    //----------
    case DIVIDE:
      check_num_nodes(node, 2, "cannot divide more than two expressions.");
      return division(val1, val2);
      // return val1 / val2;
      break;
    //----------
    case TIMES:
      check_num_nodes(node, 2, "cannot multiply more than two expressions.");
      return multiplication(val1, val2);
      // return val1 * val2;
      break;
    //----------
    case LESS:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return less(val1, val2);
      // return val1 < val2;
      break;
    //----------
    case GREATER:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      return greater(val1, val2);
      // return val1 > val2;
      break;
    //----------
    case LESSEQ:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      return less_equal(val1, val2);
      // return val1 <= val2;
      break;
    //----------
    case GREATEREQ:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      return greater_equal(val1, val2);
      // return val1 >= val2;
      break;
    //----------
    case EQUALS:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      return equals(val1, val2);
      // return val1 == val2;
      break;
    //----------
    case NEQUALS:
      check_num_nodes(node, 2, "cannot compare more than two expressions.");
      return not_equals(val1, val2);
      // return val1 != val2;
      break;
    //----------
    case AND:
      check_num_nodes(node, 2, "cannot perform logical operators on more than two expressions.");
      return and_value(val1, val2);
      // return val1 && val2;
      break;
    //----------
    case OR:
      check_num_nodes(node, 2, "cannot perform logical operators on more than two expressions.");
      return or_value(val1, val2);
      // return val1 || val2;
      break;
    //----------
    case NOT:
      check_num_nodes(node, 1, "cannot negate more than one expressions.");
      return not_value(val1);
      // return !val1;
      break;
    //----------
    case INPUT: // We're only going to support reading in doubles
      scanf("%lf", &temp);
      return make_double(temp);
      break;
    //----------
    case IDENTIFIER:
      var = find_variable(env, node->id);
      if (var == nullptr) {
        std::cerr << "Error: Symbol " << node->id << " not found." << std::endl;
        return 0;
      }
      return get_value(var);
      break;
    //----------
    case VALUE: 
      return node->value;
      break;
    //----------
    default:
      fprintf(stderr,"Error, %d not a valid expression type.\n", node->type);
      return 0;
  }

}


void eval_statement(Node* node, Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return;
  }

  Value* tempVal;

  switch(node->type) {
    case ASSIGN:
      check_num_nodes(node, 2, "cannot make an assignment without an identifier and a value.");
      add_variable(env, 
        new Variable(node->children[0]->id, 
          eval_expression(node->children[1], env)));
      break;
    //------------
    case IF:
      if (node->num_children != 2 && node->num_children != 3) { 
        fprintf(stderr, "Error: The format of an if-statement is if expression statement with an optional else.\n"); 
      }
      tempVal = eval_expression(node->children[0], env);
      if (tempVal->type == BOOLEAN) {
        if (get_long(tempVal)) {
          eval_statement(node->children[1], env);
        } else if (node->num_children == 3) {
        eval_statement(node->children[2], env);
        }
      } else {
        fprintf(stderr, "Error, a non-boolean was in the condition of an if statement.\n");
      }
      break;
    //------------
    case WHILE:
      check_num_nodes(node, 2, "the format of a while statement is: while expression statement(s)");
      tempVal = eval_expression(node->children[0], env);
      if (tempVal->type == BOOLEAN) {
        while (get_long(tempVal)) {
          eval_statement(node->children[1], env);
          tempVal = eval_expression(node->children[0], env);
        }
      } else {
        fprintf(stderr, "Error, a non-boolean was in the condition of the while loop.\n");
      }

      break;
    //------------
    case PRINT:
      check_num_nodes(node, 1, "can only print out one expression at a time.");
      tempVal = eval_expression(node->children[0], env);
      std::cout << tempVal << std::endl;
      break;
    //------------
    case STATEMENT: // Can have a maximum of two children statement nodes
      if (node->num_children > 0) {
        eval_statement(node->children[0], env);
      }
      if (node->num_children > 1) {
        eval_statement(node->children[1], env);
      }
      break;
    //------------
    default:
      printf("Error, %d not a valid statement type.\n", node->type);
      return;
  }
}
