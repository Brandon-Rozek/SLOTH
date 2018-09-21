#ifndef NODE_H
#define NODE_H

#define ID_SIZE 100
#define MAX_CHILDREN 3
#define STATEMENT 200
#define MAX_VARIABLES 200

#define DOUBLE 300
#define LONG 301
#define BOOLEAN 302

// Share the line number between files
extern int linenum;

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


struct Variable {
  char id[ID_SIZE];
  struct Value* value;
};

typedef union typeval {
        long num;
        double dec;
} TypeVal;

struct Value {
  int type;
  TypeVal value;
};

// Value functions
struct Value* make_value(int type, long num, double dec);
void delete_value(struct Value* val);
long get_long(struct Value* val);
double get_double(struct Value* val);
void set_long(struct Value* val, long num);
void set_double(struct Value* val, double dec);

// Variable Functions
struct Variable* make_variable(char* id, struct Value* value);
void set_value(struct Variable* var, struct Value* value);
struct Value* get_value(struct Variable* var);

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
struct Value* eval_expression(struct Node* node, struct Environment* env);

#endif
