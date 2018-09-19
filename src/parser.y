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
    $$ = make_node(ASSIGN, 0, "");
    attach_node($$, $1);
    attach_node($$, $3);
}

if-statement: IF expression THEN statement {
    $$ = make_node(IF, 0, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

if-else-statement: IF expression THEN statement ELSE statement {
    $$ = make_node(IF, 0, "");
    attach_node($$, $2);
    attach_node($$, $4);
    attach_node($$, $6);
}

while: WHILE expression DO statement {
    $$ = make_node(WHILE, 0, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

print: PRINT expression SEMICOLON {
    $$ = make_node(PRINT, 0, "");
    attach_node($$, $2);
}


statements: BEGINTOK substatements END { $$ = $2; }
          | BEGINTOK END {}

substatements: statement substatements {$$ = make_node(STATEMENT, 0, ""); attach_node($$, $1); attach_node($$, $2); }
              | statement  {$$ = make_node(STATEMENT, 0, ""); attach_node($$, $1); }

expression : expression OR subexpression { $$ = make_node(OR, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | expression AND subexpression { $$ = make_node(AND, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression { $$ = $1; }

subexpression: subexpression LESS term { $$ = make_node(LESS, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression LESSEQ term { $$ = make_node(LESSEQ, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATER term { $$ = make_node(GREATER, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATEREQ term { $$ = make_node(GREATEREQ, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression EQUALS term { $$ = make_node(EQUALS, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression NEQUALS term { $$ = make_node(NEQUALS, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | term { $$ = $1; }

term : term PLUS subterm { $$ = make_node(PLUS, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | term MINUS subterm { $$ = make_node(MINUS, 0, ""); attach_node($$, $1); attach_node($$, $3);}
     | subterm { $$ = $1; }

subterm: subterm TIMES factor { $$ = make_node(TIMES, 0, ""); attach_node($$, $1); attach_node($$, $3);}
       | subterm DIVIDE factor { $$ = make_node(DIVIDE, 0, ""); attach_node($$, $1); attach_node($$, $3);}
       | factor { $$ = $1; }

factor : MINUS factor { $$ = make_node(MINUS, 0, ""); attach_node($$, $2); }
       | NOT factor { $$ = make_node(NOT, 0, ""); attach_node($$, $2); }
       | atom { $$ = $1; }

atom: OPENPAREM expression ENDPAREM { $$ = $2; }
    | identvalue { $$ = $1; }

ident: IDENTIFIER { $$ = $1; }

identvalue: IDENTIFIER { $$ = $1; }
          | VALUE { $$ = $1; }
          | INPUT { $$ = make_node(INPUT, 0 , ""); }



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
struct Node* make_node(int type, double value, char* id) {
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
    case VALUE: printf("VALUE: %lf\n", node->value); break;
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
struct Variable* make_variable(char* id, double value) {
  /* allocate space */
  struct Variable* var = malloc(sizeof(struct Variable));

  /* set properties */
  strcpy(var->id, id);
  var->value = value;

  /* return new variable */
  return var;
}

void set_value(struct Variable* var, double value) {
  if (!var) { fprintf(stderr, "Error: Invalid Variable\n"); return; }
  var->value = value;
}
double get_value(struct Variable* var) {
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


double eval_expression(struct Node* node, struct Environment* env) {
  /* base case */
  if(!node) {
    fprintf(stderr, "Error: No tree structure to evaluate\n");
    return 0;
  }
  int nodeNotValid = !(
    node->type == IDENTIFIER ||
    node->type == VALUE ||
    node->type == INPUT ||
    node->type == PLUS ||
    node->type == MINUS ||
    node->type == DIVIDE ||
    node->type == TIMES ||
    node->type == LESS ||
    node->type == GREATER ||
    node->type == LESSEQ ||
    node->type == GREATEREQ ||
    node->type == EQUALS ||
    node->type == NEQUALS ||
    node->type == AND ||
    node->type == OR ||
    node->type == NOT 
  );

  if (nodeNotValid) {
    fprintf(stderr,"Error, %d not a valid expression type.\n", node->type);
    return 0;
  }

  // Needed if we are going to take input from the user
  double temp;
  struct Variable* var = NULL;

  switch(node->type) {
    case PLUS:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot add more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) + eval_expression(node->children[1], env);
      break;
    //----------
    case MINUS:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot subtract more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) - eval_expression(node->children[1], env);
      break;
    //----------
    case DIVIDE:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot divide more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) / eval_expression(node->children[1], env);
      break;
    //----------
    case TIMES:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot multiply more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) * eval_expression(node->children[1], env);
      break;
    //----------
    case LESS:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) < eval_expression(node->children[1], env);
      break;
    //----------
    case GREATER:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) > eval_expression(node->children[1], env);
      break;
    //----------
    case LESSEQ:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) <= eval_expression(node->children[1], env);
      break;
    //----------
    case GREATEREQ:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) >= eval_expression(node->children[1], env);
      break;
    //----------
    case EQUALS:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) == eval_expression(node->children[1], env);
      break;
    //----------
    case NEQUALS:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot compare more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) != eval_expression(node->children[1], env);
      break;
    //----------
    case AND:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot perform logical operators on more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) && eval_expression(node->children[1], env);
      break;
    //----------
    case OR:
      if (node->num_children != 2) { fprintf(stderr, "Error, cannot perform logical operators on more than two expressions.\n"); } 
      return eval_expression(node->children[0], env) || eval_expression(node->children[1], env);
      break;
    //----------
    case NOT:
      if (node->num_children != 1) { fprintf(stderr, "Error, cannot negate more than one expressions.\n"); } 
      return !eval_expression(node->children[0], env);
      break;
    //----------
    case INPUT:
      scanf("%lf", &temp);
      return temp;
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

  switch(node->type) {
    case ASSIGN:
      if (node->num_children != 2) { fprintf(stderr, "Error: Cannot make an assignment without an identifier and a value.\n"); }
      add_variable(env, 
        make_variable(node->children[0]->id, 
          eval_expression(node->children[1], env)));
      break;
    case IF:
      if (node->num_children != 2 && node->num_children != 3) { 
        fprintf(stderr, "Error: The format of an if-statement is if expression statement with an optional else.\n"); 
      }
      if (eval_expression(node->children[0], env)) {
        eval_statement(node->children[1], env);
      } else if (node->num_children == 3) {
        eval_statement(node->children[2], env);
      }
      break;
    case WHILE:
      if (node->num_children != 2) { fprintf(stderr, "Error: The format of a while statement is while expression statement(s)\n"); }
      while (eval_expression(node->children[0], env)) {
        eval_statement(node->children[1], env);
      }
      break;
    case PRINT:
      if (node->num_children != 1) { fprintf(stderr, "Error: Can only print out one expression at a time.\n"); }
      printf("%lf\n", eval_expression(node->children[0], env));
      break;
    case STATEMENT: // Can have a maximum of two children statement nodes
      if (node->num_children > 0) {
        eval_statement(node->children[0], env);
      }
      if (node->num_children > 1) {
        eval_statement(node->children[1], env);
      }
      break;
    default:
      printf("Error, %d not a valid node type.\n", node->type);
      return;
  }
}
