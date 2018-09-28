#ifndef NODE_H
#define NODE_H

#include <string>
#include <array>
#include "../variables/value.hpp"
#include "../variables/environment.hpp"

#define MAX_CHILDREN 3

/* a tree node definition */
struct Node {
  int type;
  struct Value* value;

  /* the id of the node (used for identifiers only) */
  std::string id;

  /* at most three children nodes */
  uint num_children;
  std::array<struct Node*, MAX_CHILDREN> children;

  Node(int t, struct Value* v, std::string s) {
    type = t;
    value = v;
    id = s;
    for (uint i = 0; i < MAX_CHILDREN; i++) {
      children[i] = nullptr;
    }
  }
  ~Node() {
    if (value) { delete value; }
    // delete value;
    for (uint i = 0; i < num_children; i++) {
      delete children[i];
    }
  }
};

// Abstract Syntax Tree Functions
// struct Node* make_node(int type, struct Value* value, std::string id);
void attach_node(struct Node* parent, struct Node* child);
void print_tree(struct Node* node, int tabs);

// Interpreting AST
void eval_statement(struct Node* node, struct Environment* env);
struct Value* eval_expression(struct Node* node, struct Environment* env);

#endif
