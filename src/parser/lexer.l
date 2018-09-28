%{
#include <stdio.h>
#include <string.h>
#include "../operations/node.hpp"
#include "../variables/value.hpp"
#include "parser.tab.h"
#include "../string.h"

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
"true"                  {yylval.value = new Node(VALUE, make_true(), ""); return VALUE;}
"false"                 {yylval.value = new Node(VALUE, make_false(), ""); return VALUE;}
\".*\"                   {yylval.value = new Node(VALUE, make_string(substring(yytext, 1, strlen(yytext) - 1)), ""); return VALUE; }
{DIGIT}                 {yylval.value = new Node(VALUE, make_long(atoi(yytext)), ""); return VALUE;}
{DIGIT}*"."?{DIGIT}+    {yylval.value = new Node(VALUE, make_double(atof(yytext)), ""); return VALUE;}
[_a-zA-Z][_a-zA-Z0-9]*  {yylval.value = new Node(IDENTIFIER,  nullptr, strdup(yytext)); return IDENTIFIER;}
[\n]                    {linenum++;} 
[ \t\r]+                {}
.                       {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
