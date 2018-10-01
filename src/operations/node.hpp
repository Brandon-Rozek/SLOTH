#ifndef NODE_H
#define NODE_H

#include <string>
#include <array>
#include <iostream>
#include <memory>
#include "../variables/value.hpp"
#include "../variables/environment.hpp"

#define MAX_CHILDREN 3

class Value;
class Environment;

/* a tree node definition */
class Node {
  public:
  int type;
  std::unique_ptr<Value> value;

  /* the id of the node (used for identifiers only) */
  std::string id;

  /* at most three children nodes */
  uint num_children;
  std::array<Node*, MAX_CHILDREN> children;

  friend std::ostream & operator << (std::ostream &out, const Node* n);

  std::string toString(void) const;

  Node(int t, std::unique_ptr<Value> v, std::string s) : value(std::move(v)) {
    type = t;
    id = s;
    num_children = 0;
    std::fill(children.begin(), children.end(), nullptr);
  }
  ~Node() {
    for (uint i = 0; i < num_children; i++) {
      delete children[i];
    }
  }
};

// Abstract Syntax Tree Functions
void attach_node(Node* parent, Node* child);
std::string tree_string(const Node* node, uint tabs);

// Interpreting AST
void eval_statement(Node* node, Environment* env);
Value* eval_expression(Node* node, Environment* env);

#endif
