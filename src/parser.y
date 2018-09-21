%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "node.h"

int yywrap( );
int yylex( );
void yyerror(const char* str);

/* the result variable */
struct Node* result;

%}

/* declare type possibilities of symbols */
%union {
  struct Node* value;
}

/* declare tokens (default is typeless) */
%token <value> IDENTIFIER   
%token <value> VALUE
%token PLUS         
%token MINUS        
%token DIVIDE       
%token TIMES     
%token LESS 
%token GREATER  
%token LESSEQ    
%token GREATEREQ 
%token EQUALS      
%token NEQUALS     
%token AND          
%token OR           
%token NOT          
%token SEMICOLON    
%token ASSIGN       
%token OPENPAREM    
%token ENDPAREM     
%token BEGINTOK     
%token END          
%token IF           
%token THEN         
%token ELSE         
%token WHILE        
%token DO           
%token PRINT        
%token <value> INPUT        
%token COMMENT            
%token WHITESPACE   
%token DONE

/* declare non-terminals */
%type <value> program statement assignment if-statement if-else-statement while print statements substatements expression subexpression term subterm factor atom identvalue ident

/* give us more detailed errors */
%error-verbose

%%
program: substatements {result = $1; return 0;}
       | ""            {return 0;}
 
statement: assignment { $$ = $1; }
         | if-statement { $$ = $1; }
         | if-else-statement { $$ = $1; }
         | while { $$ = $1; }
         | print { $$ = $1; }
         | statements { $$ = $1; } 

assignment: ident ASSIGN expression SEMICOLON {
    $$ = make_node(ASSIGN, NULL, "");
    attach_node($$, $1);
    attach_node($$, $3);
}

if-statement: IF expression THEN statement {
    $$ = make_node(IF, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

if-else-statement: IF expression THEN statement ELSE statement {
    $$ = make_node(IF, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
    attach_node($$, $6);
}

while: WHILE expression DO statement {
    $$ = make_node(WHILE, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

print: PRINT expression SEMICOLON {
    $$ = make_node(PRINT, NULL, "");
    attach_node($$, $2);
}


statements: BEGINTOK substatements END { $$ = $2; }
          | BEGINTOK END {}

substatements: statement substatements {$$ = make_node(STATEMENT, NULL, ""); attach_node($$, $1); attach_node($$, $2); }
              | statement  {$$ = make_node(STATEMENT, NULL, ""); attach_node($$, $1); }

expression : expression OR subexpression { $$ = make_node(OR, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | expression AND subexpression { $$ = make_node(AND, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression { $$ = $1; }

subexpression: subexpression LESS term { $$ = make_node(LESS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression LESSEQ term { $$ = make_node(LESSEQ, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATER term { $$ = make_node(GREATER, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATEREQ term { $$ = make_node(GREATEREQ, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression EQUALS term { $$ = make_node(EQUALS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression NEQUALS term { $$ = make_node(NEQUALS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | term { $$ = $1; }

term : term PLUS subterm { $$ = make_node(PLUS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | term MINUS subterm { $$ = make_node(MINUS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subterm { $$ = $1; }

subterm: subterm TIMES factor { $$ = make_node(TIMES, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
       | subterm DIVIDE factor { $$ = make_node(DIVIDE, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
       | factor { $$ = $1; }

factor : MINUS factor { $$ = make_node(MINUS, NULL, ""); attach_node($$, $2); }
       | NOT factor { $$ = make_node(NOT, NULL, ""); attach_node($$, $2); }
       | atom { $$ = $1; }

atom: OPENPAREM expression ENDPAREM { $$ = $2; }
    | identvalue { $$ = $1; }

ident: IDENTIFIER { $$ = $1; }

identvalue: IDENTIFIER { $$ = $1; }
          | VALUE { $$ = $1; }
          | INPUT { $$ = make_node(INPUT, NULL , ""); }



%%


int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error on line %d: '%s'.\n", linenum, str);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Incorrect number of arguments passed. Expected %d, got %d.\n", 1, argc - 1);
    printf("Usage: lexer [program_name].sl\n");
    exit(-1);
  }
  /* save stdin */
  FILE* orig_stdin = stdin;
  stdin = fopen(argv[1], "r");
  
  yyparse( );

  /* restore stdin */
  fclose(stdin);
  stdin = orig_stdin;

  // Interpret the AST
  // print_tree(result, 0);
  struct Environment* env = create_environment();
  eval_statement(result, env);
  delete_environment(env);
  delete_tree(result);
  return 0;
}






/* creates a new node and returns it */
struct Node* make_node(int type, struct Value* value, char* id) {
  int i;

  /* allocate space */
  struct Node* node = malloc(sizeof(struct Node));

  /* set properties */
  node->type = type;
  node->value = value;
  strcpy(node->id, id);
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
    case STATEMENT: printf("STATEMENT:\n"); break;
    case VALUE: 
      if (node->value->type == LONG) {
        printf("VALUE: %li\n", get_long(node->value));
      } else { // Assume double
        printf("VALUE: %lf\n", get_double(node->value));
      }
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

/* creates a new variable and returns it */
struct Variable* make_variable(char* id, struct Value* value) {
  /* allocate space */
  struct Variable* var = malloc(sizeof(struct Variable));

  /* set properties */
  strcpy(var->id, id);
  var->value = value;

  /* return new variable */
  return var;
}

void set_value(struct Variable* var, struct Value* value) {
  if (!var) { fprintf(stderr, "Error: Invalid Variable\n"); return; }
  var->value = value;
}

struct Value* get_value(struct Variable* var) {
  if (!var) { fprintf(stderr, "Error: Invalid Variable\n"); return 0; }
  return var->value;
}

struct Environment* create_environment(void) {
  struct Environment* env = malloc(sizeof(struct Environment));
  env->num_vars = 0;
  for(int i = 0; i < MAX_VARIABLES; i++) {
    env->vars[i] = NULL;
  }
  return env;
}

struct Variable* find_variable(struct Environment* env, char* id) {
  for (int i = 0; i < env->num_vars; i++) {
    if (strcmp(env->vars[i]->id, id) == 0) {
      return env->vars[i];
    }
  }
  return NULL;
}

void add_variable(struct Environment* env, struct Variable* var) {
  if (env->num_vars >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Maximum number of variables reached.\n");
    return;
  }

  // If variable exists, replace it
  struct Variable* temp_var = find_variable(env, var->id);
  if (temp_var != NULL) {
    temp_var->value = var->value;
    free(var);
    return;
  }

  // If not, add variable to environment
  env->vars[env->num_vars] = var;
  env->num_vars += 1;
}

void delete_environment(struct Environment* env) {
  for (int i = 0; i < env->num_vars; i++) {
    free(env->vars[i]);
  }
  free(env);
}

void check_num_nodes(struct Node* node, int num_children, char* error) {
  if (node && node->num_children != num_children) {
    fprintf(stderr, "%s%s%s", "Error, ", error, "\n");
  }
}

struct Value* make_value(int type, long num, double dec) {
    /* allocate space */
  struct Value* val = malloc(sizeof(struct Value));

  /* set properties */
  val->type = type;
  if (type == LONG) {
    val->value.num = num;
  } else { // Assume DOUBLE
    val->value.dec = dec;
  }

  /* return new variable */
  return val;
}
void delete_value(struct Value* val) {
  free(val);
}
long get_long(struct Value* val) {
  return val->value.num;
}
double get_double(struct Value* val) {
  return val->value.dec;
}
void set_long(struct Value* val, long num) {
  val->type = LONG;
  val->value.num = num;
}
void set_double(struct Value* val, double dec) {
  val->type = DOUBLE;
  val->value.dec = dec;
}
struct Value* add(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in add.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) + get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) + get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) + get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) + get_double(y));
  }

  return ans;
}

struct Value* subtract(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in subtract.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) - get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) - get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) - get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) - get_double(y));
  }

  return ans;
}

struct Value* division(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in divide.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) / get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) / get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) / get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) / get_double(y));
  }

  return ans;
}

struct Value* multiplication(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in multiply.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) * get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) * get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) * get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) * get_double(y));
  }

  return ans;
}

struct Value* less(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in <.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) < get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) < get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) < get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) < get_double(y));
  }

  return ans;
}

struct Value* greater(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in greater.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) > get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) > get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) > get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) > get_double(y));
  }

  return ans;
}

struct Value* less_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in <=.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) <= get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) <= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) <= get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) <= get_double(y));
  }

  return ans;
}

struct Value* greater_equal(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in >=.\n"); }
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) >= get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) >= get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) >= get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) >= get_double(y));
  }

  return ans;
}

struct Value* equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ==.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) == get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) == get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) == get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) == get_double(y));
  }

  return ans;
}

struct Value* not_equals(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in !=.\n"); }
  
  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) != get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) != get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) != get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) != get_double(y));
  }

  return ans;
}

struct Value* and(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in &&.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) && get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) && get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) && get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) && get_double(y));
  }

  return ans;
}

struct Value* or(struct Value* x, struct Value* y) {
  if (!x || !y) { fprintf(stderr, "Error, uninitialized values being used in ||.\n"); }

  struct Value* ans;

  // Destruct all four cases
  if (x->type == LONG && y->type == LONG) {
    ans = make_value(LONG, get_long(x) || get_long(y), 0);
  } else if (x->type == LONG && y->type == DOUBLE) {
    ans = make_value(DOUBLE, 0, get_long(x) || get_double(y));
  } else if (x->type == DOUBLE && y->type == LONG) {
    ans = make_value(DOUBLE, 0, get_double(x) || get_long(y));
  } else { // Both are DOUBLE
    ans = make_value(DOUBLE, 0, get_double(x) || get_double(y));
  }

  return ans;
}

struct Value* not(struct Value* x) {
  if (!x) { fprintf(stderr, "Error, uninitialized values being used in !.\n"); }

  struct Value* ans;

  // Destruct all two cases
  if (x->type == LONG) {
    ans = make_value(LONG, !get_long(x), 0);
  } else { // Assume it's a double
    ans = make_value(DOUBLE, 0, !get_double(x));
  }

  return ans;
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

  // Evaluate subexpressions if existent
  struct Value* val1 = NULL;
  struct Value* val2 = NULL;
  struct Value* val3 = NULL;
  if (node->num_children > 0) {
    val1 = eval_expression(node->children[0], env);
    if (node->num_children > 1) {
      val2 = eval_expression(node->children[1], env);
      if (node->num_children > 2) {
        val3 = eval_expression(node->children[2], env);
        // delete_value(val3); // No code below uses val3 for now...
      }
    }
  }

  switch(node->type) {
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
      return and(val1, val2);
      // return val1 && val2;
      break;
    //----------
    case OR:
      check_num_nodes(node, 2, "cannot perform logical operators on more than two expressions.");
      return or(val1, val2);
      // return val1 || val2;
      break;
    //----------
    case NOT:
      check_num_nodes(node, 1, "cannot negate more than one expressions.");
      return not(val1);
      // return !val1;
      break;
    //----------
    case INPUT: // We're only going to support reading in doubles
      // Look into deleting possible values...?
      scanf("%lf", &temp);
      return make_value(DOUBLE, 0, temp);
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
      if (tempVal->type == LONG) {
        if (get_long(tempVal)) {
          eval_statement(node->children[1], env);
        } else if (node->num_children == 3) {
        eval_statement(node->children[2], env);
        }
      } else { // Assume DOUBLE
        if (get_double(tempVal)) {
          eval_statement(node->children[1], env);
        } else if (node->num_children == 3) {
        eval_statement(node->children[2], env);
        }
      }
      break;
    //------------
    case WHILE:
      check_num_nodes(node, 2, "the format of a while statement is: while expression statement(s)");
      tempVal = eval_expression(node->children[0], env);
      if (tempVal->type == LONG) {
        while (get_long(tempVal)) {
          eval_statement(node->children[1], env);
          tempVal = eval_expression(node->children[0], env);
        }
      } else { // Assume DOUBLE
        while (get_double(tempVal)) {
          eval_statement(node->children[1], env);
          tempVal = eval_expression(node->children[0], env);
        }
      }

      break;
    //------------
    case PRINT:
      check_num_nodes(node, 1, "can only print out one expression at a time.");
      tempVal = eval_expression(node->children[0], env);
      if (tempVal->type == LONG) {
        printf("%li\n", get_long(tempVal));
      } else {
        printf("%lf\n", get_double(tempVal));
      }
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
