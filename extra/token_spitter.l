%{
#include <stdio.h>
#define IDENTIFIER   100
#define VALUE        101
#define PLUS         102
#define MINUS        103
#define DIVIDE       104
#define TIMES        105
#define LESS         106
#define GREATER      107
#define LESSEQ       108
#define GREATEREQ    109
#define EQUALS       110
#define NEQUALS      111
#define AND          112
#define OR           113
#define NOT          114
#define SEMICOLON    115
#define ASSIGN       116
#define OPENPAREM    117
#define ENDPAREM     118
#define BEGINTOK     119
#define END          120
#define IF           121
#define THEN         122
#define ELSE         123
#define WHILE        124
#define DO           125
#define PRINT        126
#define INPUT        127
#define COMMENT      128
#define ERROR        129
#define WHITESPACE   130
%}
ALPHA [a-zA-Z]
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
%.*\n                   {return COMMENT;}
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
{DIGIT}*"."?{DIGIT}+    {return VALUE;}
[_a-zA-Z][_a-zA-Z0-9]*  {return IDENTIFIER;}
[ \n\t\r]+              {return WHITESPACE;}
.                       {printf("Syntax Error! Received: %s\n", yytext); return ERROR;}

%%
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments passed. Expected %d, got %d.\n", 1, argc - 1);
        printf("Usage: lexer [program_name].sl\n");
        exit(-1);
    }
    stdin = fopen(argv[1], "r");
    int token;

    do {
        token = yylex();
        if (token == ERROR) {
            exit(-1);
        }
        // Ignore Comments and Whitespace
        if (token != COMMENT && token != WHITESPACE) {
            printf("%d\n", token);
        }
    } while(token != 0);

    return 0;
}