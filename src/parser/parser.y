%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.hpp"
#include "../operations/node.hpp"
#include "../constants.hpp"

%}

/* declare type possibilities of symbols */
%union {
  Node* value;
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
%token OPENVECTOR
%token CLOSEVECTOR 
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
%token COMMA

/* declare non-terminals */
%type <value> program statement assignment if-statement if-else-statement while print statements substatements callfunc vector vectorlist exprlambda expression subexpression term subterm factor atom identvalue ident

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

assignment: ident ASSIGN vector SEMICOLON {
    $$ = new Node(ASSIGN, NULL, "");
    attach_node($$, $1);
    attach_node($$, $3);
}

if-statement: IF expression THEN statement {
    $$ = new Node(IF, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

if-else-statement: IF expression THEN statement ELSE statement {
    $$ = new Node(IF, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
    attach_node($$, $6);
}

while: WHILE expression DO statement {
    $$ = new Node(WHILE, NULL, "");
    attach_node($$, $2);
    attach_node($$, $4);
}

print: PRINT vector SEMICOLON {
    $$ = new Node(PRINT, NULL, "");
    attach_node($$, $2);
}


statements: BEGINTOK substatements END { $$ = $2; }
          | BEGINTOK END {}

substatements: statement substatements {$$ = new Node(STATEMENT, NULL, ""); attach_node($$, $1); attach_node($$, $2); }
              | statement  {$$ = new Node(STATEMENT, NULL, ""); attach_node($$, $1); }

vector: OPENVECTOR CLOSEVECTOR { $$ = new Node(VECTOR, std::unique_ptr<Value>(nullptr), ""); /*Empty vector*/ } 
        | OPENVECTOR vectorlist CLOSEVECTOR { $$ = new Node(VECTOR, std::unique_ptr<Value>(nullptr), ""); attach_node($$, $2); }
        | exprlambda { $$ = $1; }

vectorlist: exprlambda COMMA vectorlist {$$ = $1; attach_node($$, $3); }
            | exprlambda { $$ = $1; }

exprlambda: LAMBDATAG ident COLON expression { 
              // Only supports one argument functions for now
              $$ = new Node(LAMBDATAG, NULL, "");
              attach_node($$, $2);
              attach_node($$, $4); }
        | expression { $$ = $1; }

expression: expression OR subexpression { $$ = new Node(OR, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | expression AND subexpression { $$ = new Node(AND, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression { $$ = $1; }

subexpression: subexpression LESS term { $$ = new Node(LESS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression LESSEQ term { $$ = new Node(LESSEQ, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATER term { $$ = new Node(GREATER, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression GREATEREQ term { $$ = new Node(GREATEREQ, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression EQUALS term { $$ = new Node(EQUALS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subexpression NEQUALS term { $$ = new Node(NEQUALS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | term { $$ = $1; }

term : term PLUS subterm { $$ = new Node(PLUS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | term MINUS subterm { $$ = new Node(MINUS, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
     | subterm { $$ = $1; }

subterm: subterm TIMES factor { $$ = new Node(TIMES, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
       | subterm DIVIDE factor { $$ = new Node(DIVIDE, NULL, ""); attach_node($$, $1); attach_node($$, $3);}
       | factor { $$ = $1; }

factor : MINUS factor { $$ = new Node(MINUS, NULL, ""); attach_node($$, $2); }
       | NOT factor { $$ = new Node(NOT, NULL, ""); attach_node($$, $2); }
       | atom { $$ = $1; }

callfunc: ident OPENPAREM expression ENDPAREM { $$ = new Node(CALLFUNC, NULL, ""); attach_node($$, $1); attach_node($$, $3); }

atom: OPENPAREM expression ENDPAREM { $$ = $2; }
    | callfunc { $$ = $1; }
    | identvalue { $$ = $1; }

ident: IDENTIFIER { $$ = $1; }

identvalue: ident { $$ = $1; }
          | VALUE { $$ = $1; }
          | INPUT { $$ = new Node(INPUT, NULL , ""); }
          | OPENVECTOR identvalue CLOSEVECTOR { $$ = new Node(OPENVECTOR, NULL, ""); attach_node($$, $2); }




%%


int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error on line %d: '%s'.\n", linenum, str);
  exit(1);
}
