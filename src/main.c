#include <stdio.h>
#include <stdlib.h>
#include "sloth.h"

/* the result variable */
struct Node* result;

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
