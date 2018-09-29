#ifndef NODE_H
#define NODE_H

#include <string>
#include <array>
#include <iostream>
#include "../variables/value.hpp"
#include "../variables/environment.hpp"

#define MAX_CHILDREN 3

class Value;
class Environment;

/* a tree node definition */
class Node {
  public:
  int type;
  Value* value;

  /* the id of the node (used for identifiers only) */
  std::string id;

  /* at most three children nodes */
  uint num_children;
  std::array<Node*, MAX_CHILDREN> children;

  friend std::ostream & operator << (std::ostream &out, const Node* n);

  std::string toString(void) const;

  Node(int t, Value* v, std::string s) {
    type = t;
    value = v;
    id = s;
    num_children = 0;
    for (uint i = 0; i < MAX_CHILDREN; i++) {
      children[i] = nullptr;
    }
  }
  ~Node() {
    // delete value;
    for (uint i = 0; i < num_children; i++) {
      delete children[i];
    }
  }
};

// Abstract Syntax Tree Functions
// struct Node* make_node(int type, struct Value* value, std::string id);
void attach_node(Node* parent, Node* child);
std::string tree_string(const Node* node, uint tabs);

// Interpreting AST
void eval_statement(Node* node, Environment* env);
Value* eval_expression(Node* node, Environment* env);

#endif
