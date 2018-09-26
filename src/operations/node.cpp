#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include "node.hpp"
#include "operators.hpp"
#include "../constants.hpp"
#include "../parser/parser.tab.h"
#include "../variables/value.hpp"
#include "../variables/variable.hpp"

/* creates a new node and returns it */
struct Node* make_node(int type, struct Value* value, std::string id) {
  int i;

  /* allocate space */
  struct Node* node = new Node();

  /* set properties */
  node->type = type;
  node->value = value;
  id.copy(node->id, id.length(), 0);
  node->num_children = 0;
  for(i = 0; i < MAX_CHILDREN; i++) {
    node->children[i] = NULL;
  }

  /* return new node */
  return node;
}

/* attach an existing node onto a parent */
void attach_node(struct Node* parent, struct Node* child) {
  /* connect it */
  parent->children[parent->num_children] = child;
  parent->num_children++;
  assert(parent->num_children <= MAX_CHILDREN);
}

void check_num_nodes(struct Node* node, int num_children, std::string error) {
  if (node && node->num_children != num_children) {
    std::cerr << "Error, " << error << std::endl;
  }
}

void print_tree(struct Node* node, int tabs) {
  int i;
  /* base case */
  if(!node) {
    fprintf(stderr, "NO TREE STRUCTURE\n");
    return;
  }

  /* print leading tabs */
  for(i = 0; i < tabs; i++) {
    printf("    ");
  }

  switch(node->type) {
    case IDENTIFIER: printf("IDENTIFIER: %s\n", node->id); break;
    case PLUS: printf("PLUS:\n"); break;
    case MINUS: printf("MINUS:\n"); break;
    case DIVIDE: printf("DIVIDE:\n"); break;
    case TIMES: printf("TIMES:\n"); break;
    case LESS: printf("LESS THAN:\n"); break;
    case GREATER: printf("GREATER:\n"); break;
    case LESSEQ: printf("LESS EQUAL:\n"); break;
    case GREATEREQ: printf("GREATER EQUAL:\n"); break;
    case EQUALS: printf("EQUALS:\n"); break;
    case NEQUALS: printf("NOT EQUALS:\n"); break;
    case AND: printf("AND:\n"); break;
    case OR: printf("OR:\n"); break;
    case NOT: printf("NOT:\n"); break;
    case ASSIGN: printf("ASSIGN:\n"); break;
    case IF: printf("IF:\n"); break;
    case WHILE: printf("WHILE:\n"); break;
    case PRINT: printf("PRINT:\n"); break;
    case INPUT: printf("INPUT:\n"); break;
    case LAMBDA: printf("LAMBDA:\n"); break;
    case CALLFUNC: printf("FUNCTIONCALL:\n"); break;
    case STATEMENT: printf("STATEMENT:\n"); break;
    case VALUE: 
      printf("VALUE: ");
      print_value(node->value);
      printf("\n");
     break;
    default:
      printf("Error, %d not a valid node type.\n", node->type);
      exit(1);
  }

  /* print all children nodes underneath */
  for(i = 0; i < node->num_children; i++) {
    print_tree(node->children[i], tabs + 1);
  }
}

void delete_tree(struct Node* node) {
  if (!node) { return; }
  for(int i = 0; i < node->num_children; i++) {
    delete_tree(node->children[i]);
  }
  free(node);
}



struct Value* eval_expression(struct Node* node, struct Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return 0;
  }

  // Needed if we are going to take input from the user
  double temp;
  struct Variable* var = NULL;
  struct Environment* local_env = NULL;
  struct Node* tempNode = NULL;
  struct Value* tempVal = NULL;

  // Evaluate subexpressions if existent and node is not a lambda expression
  struct Value* val1 = NULL;
  struct Value* val2 = NULL;
  // struct Value* val3 = NULL;
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
      local_env = create_environment();
      add_variable(local_env, 
        make_variable(tempNode->children[0]->id, // Get the name of the variable needed for the lambda expression
          eval_expression(node->children[1], env)));
      tempVal =  eval_expression(tempNode->children[1], local_env);
      delete_environment(local_env);
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
      if (var == NULL) {
        fprintf(stderr, "Error: Symbol %s not found.\n", node->id);
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
        make_variable(node->children[0]->id, 
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
