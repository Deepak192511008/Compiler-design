%option noyywrap
%{
#include <stdio.h>
%}
%%
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while
                    { printf("KEYWORD: %s\n", yytext); }
[A-Za-z_][A-Za-z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
[ \t\r\n]+            ;
.                       ;
%%
int main(void) { yylex(); return 0; }
