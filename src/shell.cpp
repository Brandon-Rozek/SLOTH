#include <stdio.h>
#include <string.h>
#include "shell.hpp"
#include "parser/parser.hpp"
#include "variables/environment.hpp"
#include "operations/node.hpp"
#include "constants.hpp"


// For keeping track of command history
#ifdef _WIN32 // If we're compiling on windows
#include <string.h>
static char buffer[2048];
// Fake readline function
char* readline(char* prompt) {
        fputs(prompt, stdout);
        fgets(buffer, 2048, stdin);
        char* cpy = malloc(strlen(buffer) + 1);
        strcpy(cpy, buffer);
        cpy[strlen(cpy) - 1] = '\0';
        return cpy;
}
void add_history(char* unused) {}

#else // Otherwise we'll just use the handy readline library
#include <editline/readline.h>
#endif

FILE* stringToFile(char* str) { // Creates a temporary file with the given string as its contents
    int i = 0; 
  
    FILE* tmp = tmpfile(); 
    if (tmp == nullptr) { 
        fprintf(stderr, "Unable to create temp file"); 
        return nullptr; 
    } 
  
    while (str[i] != '\0') { 
        fputc(str[i], tmp); i++; 
    } 
  
    // Set the file pointer to the beginning 
    rewind(tmp); 
    return tmp;
}

void start_shell() {
    printf("Welcome to SLOTH Version 0.0.1\n");
    printf("Press CTRL+C to Exit\n");

    Environment* env = new Environment();
    while (1) {
        // Read line from user and input it into the history
        char* input = readline("sloth> ");
        add_history(input);
        // If user enters "exit" quit the loop
        if (strcmp(input, "exit") == 0) { break; }
        FILE* inputAsFile = stringToFile(input);
        /* save stdin */
        FILE* orig_stdin = stdin;
        stdin = inputAsFile;
  
        yyparse( );

        /* restore stdin */
        fclose(stdin);
        stdin = orig_stdin;

        eval_statement(result, env);
    }

    delete env;
    delete result;
}