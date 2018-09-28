#include <iostream>
#include <string>
#include "node.hpp"
#include "operators.hpp"
#include "../constants.hpp"
#include "../parser/parser.tab.h"
#include "../variables/value.hpp"
#include "../variables/variable.hpp"

/* attach an existing node onto a parent */
void attach_node(struct Node* parent, struct Node* child) {
  /* connect it */
  parent->children[parent->num_children] = child;
  parent->num_children++;
  if (parent->num_children > MAX_CHILDREN) { std::cerr << "Error, max children attached to a node" << std::endl; }
}

void check_num_nodes(struct Node* node, uint num_children, std::string error) {
  if (node && node->num_children != num_children) {
    std::cerr << "Error, " << error << std::endl;
  }
}

void print_tree(struct Node* node, uint tabs) {
  uint i;
  /* base case */
  if(!node) {
    std::cerr << "NO TREE STRUCTURE" << std::endl;
    return;
  }

  /* print leading tabs */
  for(i = 0; i < tabs; i++) {
    std::cout << "    ";
  }

  switch(node->type) {
    case IDENTIFIER: std::cout << "IDENTIFIER: " << node->id << std::endl; break;
    case PLUS: std::cout << "PLUS:" << std::endl; break;
    case MINUS: std::cout << "MINUS:" << std::endl; break;
    case DIVIDE: std::cout << "DIVIDE:" << std::endl; break;
    case TIMES: std::cout << "TIMES:" << std::endl; break;
    case LESS: std::cout << "LESS THAN:" << std::endl; break;
    case GREATER: std::cout << "GREATER:" << std::endl; break;
    case LESSEQ: std::cout << "LESS EQUAL:" << std::endl; break;
    case GREATEREQ: std::cout << "GREATER EQUAL:" << std::endl; break;
    case EQUALS: std::cout << "EQUAL:" << std::endl; break;
    case NEQUALS: std::cout << "NOT EQUAL:" << std::endl; break;
    case AND: std::cout << "AND:" << std::endl; break;
    case OR: std::cout << "OR:" << std::endl; break;
    case NOT: std::cout << "NOT:" << std::endl; break;
    case ASSIGN: std::cout << "ASSIGN:" << std::endl; break;
    case IF: std::cout << "IF:" << std::endl; break;
    case WHILE: std::cout << "WHILE:" << std::endl; break;
    case PRINT: std::cout << "PRINT:" << std::endl; break;
    case INPUT: std::cout << "INPUT:" << std::endl; break;
    case LAMBDA: std::cout << "LAMBDA:" << std::endl; break;
    case CALLFUNC: std::cout << "FUNCCALL:" << std::endl; break;
    case STATEMENT: std::cout << "STATEMENT:" << std::endl; break;
    case VALUE: 
      std::cout << "VALUE: ";
      print_value(node->value);
      std::cout << std::endl;
     break;
    default:
      std::cerr << "Error, " << node->type << " is not a valid node type." << std::endl;
      exit(1);
  }

  /* print all children nodes underneath */
  for(i = 0; i < node->num_children; i++) {
    print_tree(node->children[i], tabs + 1);
  }
}


struct Value* eval_expression(struct Node* node, struct Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return 0;
  }

  // Needed if we are going to take input from the user
  double temp;
  struct Variable* var = nullptr;
  struct Environment* local_env = nullptr;
  struct Node* tempNode = nullptr;
  struct Value* tempVal = nullptr;

  // Evaluate subexpressions if existent and node is not a lambda expression
  struct Value* val1 = nullptr;
  struct Value* val2 = nullptr;
  // struct Value* val3 = nullptr;
  if (node->num_children > 0 && node->type != LAMBDA) {
    val1 = eval_expression(node->children[0], env);
    if (node->num_children > 1) {
      val2 = eval_expression(node->children[1], env);
      // if (node->num_children > 2) {
        // val3 = eval_expression(node->children[2], env);
      // }
    }
  }

  switch(node->type) {
    case LAMBDA: return make_expression(node); break;
    case CALLFUNC:
      check_num_nodes(node, 2, "cannot have more than two nodes for a function call.");
      tempNode = get_expression(get_value(find_variable(env, node->children[0]->id)));
      local_env = new Environment();
      add_variable(local_env, 
        new Variable(tempNode->children[0]->id, // Get the name of the variable needed for the lambda expression
          eval_expression(node->children[1], env)));
      tempVal =  eval_expression(tempNode->children[1], local_env);
      delete_environment(local_env);
      // delete local_env;
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
      // Look into deleting possible values...?
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


void eval_statement(struct Node* node, struct Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return;
  }

  struct Value* tempVal;

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
      print_value(tempVal);
      printf("\n");
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
