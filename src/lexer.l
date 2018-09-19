%{
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "parser.tab.h"

/* Keep track of line numbers for error reporting */
int linenum = 0;
%}

DIGIT [0-9]
%option noyywrap
%%

"+"                     {return PLUS; }
"-"                     {return MINUS;}
"/"                     {return DIVIDE;}
"*"                     {return TIMES;}
"!"                     {return NOT;}
"("                     {return OPENPAREM;}
")"                     {return ENDPAREM;}
";"                     {return SEMICOLON;}
%.*\n                   {} // Comments
"<"                     {return LESS;}
">"                     {return GREATER;}
"<="                    {return LESSEQ;}
">="                    {return GREATEREQ;}
"=="                    {return EQUALS;}
"!="                    {return NEQUALS;}
"&&"                    {return AND;}
"||"                    {return OR;}
":="                    {return ASSIGN;}
"if"                    {return IF;}
"do"                    {return DO;}
"end"                   {return END;}
"then"                  {return THEN;}
"else"                  {return ELSE;}
"begin"                 {return BEGINTOK;}
"while"                 {return WHILE;}
"print"                 {return PRINT;}
"input"                 {return INPUT;}
{DIGIT}*"."?{DIGIT}+    {yylval.value = make_node(VALUE, atof(yytext), ""); return VALUE;}
[_a-zA-Z][_a-zA-Z0-9]*  {yylval.value = make_node(IDENTIFIER,  0, strdup(yytext)); return IDENTIFIER;}
[\n]                    {linenum++;} 
[ \t\r]+                {}
.                       {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
