%option noyywrap
%{
#include <stdio.h>
int macros = 0, headers = 0;
%}
%%
^[ \t]*#[ \t]*define[^\n]*     { macros++; }
^[ \t]*#[ \t]*include[^\n]*    { headers++; }
\"([^\\\n]|\\.)*\"             { printf("STRING CONSTANT: %s\n", yytext); }
[0-9]+(\.[0-9]+)?              { printf("NUMERIC CONSTANT: %s\n", yytext); }
.|\n                            ;
%%
int main(int argc, char **argv)
{
    if (argc == 2) { yyin = fopen(argv[1], "r"); if (!yyin) return 1; }
    yylex();
    printf("Macros defined: %d\nHeaders included: %d\n", macros, headers);
    return 0;
}
