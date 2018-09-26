%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "../operations/node.h"
#include "../constants.h"

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
%token <value> LAMBDATAG
%token COLON

/* declare non-terminals */
%type <value> program statement assignment if-statement if-else-statement while print statements substatements callfunc exprlambda expression subexpression term subterm factor atom identvalue ident

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

assignment: ident ASSIGN exprlambda SEMICOLON {
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

print: PRINT exprlambda SEMICOLON {
    $$ = make_node(PRINT, NULL, "");
    attach_node($$, $2);
}


statements: BEGINTOK substatements END { $$ = $2; }
          | BEGINTOK END {}

substatements: statement substatements {$$ = make_node(STATEMENT, NULL, ""); attach_node($$, $1); attach_node($$, $2); }
              | statement  {$$ = make_node(STATEMENT, NULL, ""); attach_node($$, $1); }

exprlambda: LAMBDATAG ident COLON expression { 
              // Only supports one argument functions for now
              $$ = make_node(LAMBDATAG, NULL, "");
              attach_node($$, $2);
              attach_node($$, $4); }
        | expression { $$ = $1; }

expression: expression OR subexpression { $$ = make_node(OR, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
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

callfunc: ident OPENPAREM expression ENDPAREM { $$ = make_node(CALLFUNC, NULL, ""); attach_node($$, $1); attach_node($$, $3); }

atom: OPENPAREM expression ENDPAREM { $$ = $2; }
    | callfunc { $$ = $1; }
    | identvalue { $$ = $1; }

ident: IDENTIFIER { $$ = $1; }

identvalue: ident { $$ = $1; }
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
