#ifndef PARSER_H
#define PARSER_H

int yywrap( );
int yylex( );
void yyerror(const char* str);

#endif
