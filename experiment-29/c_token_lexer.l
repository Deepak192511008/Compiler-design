%option noyywrap
%{
#include <stdio.h>
%}
%%
"//"[^\n]*                         ;
"/*"([^*]|\*+[^*/])*"*/"           ;
\"([^\\\n]|\\.)*\"                 { printf("STRING CONSTANT: %s\n", yytext); }
[A-Za-z_][A-Za-z0-9_]*              { printf("IDENTIFIER: %s\n", yytext); }
[0-9]+(\.[0-9]+)?                   { printf("CONSTANT: %s\n", yytext); }
"+"|"-"|"*"|"/"|"="|"=="|"<"|">"  { printf("OPERATOR: %s\n", yytext); }
[(){}\[\],;.]                       { printf("SPECIAL SYMBOL: %s\n", yytext); }
[ \t\r\n]+                         ;
.                                   { printf("UNKNOWN: %s\n", yytext); }
%%
int main(int argc, char **argv)
{
    if (argc == 2) { yyin = fopen(argv[1], "r"); if (!yyin) return 1; }
    yylex(); return 0;
}
