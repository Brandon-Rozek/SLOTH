#include <stdio.h>
#include <stdlib.h>
#include "sloth.h"
#include "shell.h"

void interpret_file(char* fileName);

/* the result variable */
struct Node* result;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    start_shell();
  } else if (argc == 2) {
    interpret_file(argv[1]);
  } else {
    printf("Incorrect number of arguments passed. Expected %d or %d, got %d.\n", 0, 1, argc - 1);
    printf("Usage: lexer [program_name].sl\n");
    exit(-1);
  }

}


void interpret_file(char* fileName) {
  /* save stdin */
  FILE* orig_stdin = stdin;
  stdin = fopen(fileName, "r");
  
  yyparse( );

  /* restore stdin */
  fclose(stdin);
  stdin = orig_stdin;

  // Interpret the AST
  // print_tree(result, 0); // For debugging
  struct Environment* env = create_environment();
  eval_statement(result, env);
  delete_environment(env);
  delete_tree(result);
}