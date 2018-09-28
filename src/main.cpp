#include <iostream>
#include <stdlib.h>
#include "sloth.hpp"
#include "shell.hpp"

void interpret_file(char* fileName);

/* the result variable */
struct Node* result;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    start_shell();
  } else if (argc == 2) {
    interpret_file(argv[1]);
  } else {
    std::cout << "Incorrect number of arguments passed. Expected " << 0 << " or " << 1 << ", got " << argc - 1 << std::endl; 
    std::cout << "Usage: sloth [program_name]" << std::endl;
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
  struct Environment* env = new Environment();
  eval_statement(result, env);
  delete_environment(env);
  // delete env;

  delete result;
}