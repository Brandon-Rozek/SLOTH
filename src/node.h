#ifndef NODE_H
#define NODE_H

#define ID_SIZE 100
#define MAX_CHILDREN 3
#define STATEMENT 200
#define MAX_VARIABLES 200

// Share the line number between files
extern int linenum;

/* a tree node definition */
struct Node {
  int type;
  double value;

  /* the id of the node (used for identifiers only) */
  char id[ID_SIZE];

  /* at most three children nodes */
  int num_children;
  struct Node* children[MAX_CHILDREN];
};

// Abstract Syntax Tree Functions
struct Node* make_node(int type, double value, char* id);
void attach_node(struct Node* parent, struct Node* child);
void print_tree(struct Node* node, int tabs);
void delete_tree(struct Node* node);


struct Variable {
  char id[ID_SIZE];
  double value;
};

// Variable Functions
struct Variable* make_variable(char* id, double value);
void set_value(struct Variable* var, double value);
double get_value(struct Variable* var);

struct Environment {
  int num_vars;
  struct Variable* vars[MAX_VARIABLES];
};

// Variable Lookup Functions
struct Environment* create_environment(void);
void delete_environment(struct Environment* env);
struct Variable* find_variable(struct Environment* env, char* id);
void add_variable(struct Environment* env, struct Variable* var);


// Interpreting AST
void eval_statement(struct Node* node, struct Environment* env);
double eval_expression(struct Node* node, struct Environment* env);

#endif
