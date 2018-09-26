#ifndef NODE_H
#define NODE_H

#include "../variables/value.h"
#include "../variables/environment.h"

#define ID_SIZE 100
#define MAX_CHILDREN 3

/* a tree node definition */
struct Node {
  int type;
  struct Value* value;

  /* the id of the node (used for identifiers only) */
  char id[ID_SIZE];

  /* at most three children nodes */
  int num_children;
  struct Node* children[MAX_CHILDREN];
};

// Abstract Syntax Tree Functions
struct Node* make_node(int type, struct Value* value, char* id);
void attach_node(struct Node* parent, struct Node* child);
void print_tree(struct Node* node, int tabs);
void delete_tree(struct Node* node);

// Interpreting AST
void eval_statement(struct Node* node, struct Environment* env);
struct Value* eval_expression(struct Node* node, struct Environment* env);

#endif
