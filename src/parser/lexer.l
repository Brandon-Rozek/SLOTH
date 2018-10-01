%{
#include <stdio.h>
#include <string.h>
#include <vector>
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
"["                     {return OPENVECTOR;}
"]"                     {return CLOSEVECTOR;}
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
"lambda"                {return LAMBDATAG;}
":"                     {return COLON;}
"true"                  {yylval.value = new Node(VALUE, std::unique_ptr<Value>(make_true()), ""); return VALUE;}
"false"                 {yylval.value = new Node(VALUE, std::unique_ptr<Value>(make_false()), ""); return VALUE;}
\".*\"                   {yylval.value = new Node(VALUE, std::unique_ptr<Value>(make_string(substring(yytext, 1, strlen(yytext) - 1))), ""); return VALUE; }
{DIGIT}                 {std::vector<long> nums; nums.push_back(atoi(yytext)); yylval.value = new Node(VALUE, std::unique_ptr<Value>(make_long(nums)), ""); return VALUE;}
{DIGIT}*"."?{DIGIT}+    {std::vector<double> decs; decs.push_back(atof(yytext)); yylval.value = new Node(VALUE, std::unique_ptr<Value>(make_double(decs)), ""); return VALUE;}
[_a-zA-Z][_a-zA-Z0-9]*  {yylval.value = new Node(IDENTIFIER, std::unique_ptr<Value>(nullptr), yytext); return IDENTIFIER;}
[\n]                    {linenum++;} 
[ \t\r]+                {}
.                       {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
