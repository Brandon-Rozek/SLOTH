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
"lambda"                {return LAMBDA;}
":"                     {return COLON;}
"true"                  {yylval.value = make_node(VALUE, make_value(BOOLEAN, 1, 0), ""); return VALUE;}
"false"                 {yylval.value = make_node(VALUE, make_value(BOOLEAN, 0, 0), ""); return VALUE;}
{DIGIT}                 {yylval.value = make_node(VALUE, make_value(LONG, atoi(yytext), 0), ""); return VALUE;}
{DIGIT}*"."?{DIGIT}+    {yylval.value = make_node(VALUE, make_value(DOUBLE, 0, atof(yytext)), ""); return VALUE;}
[_a-zA-Z][_a-zA-Z0-9]*  {yylval.value = make_node(IDENTIFIER,  NULL, strdup(yytext)); return IDENTIFIER;}
[\n]                    {linenum++;} 
[ \t\r]+                {}
.                       {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
