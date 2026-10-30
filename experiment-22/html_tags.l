%option noyywrap
%{
#include <stdio.h>
%}
%%
<[^>]+>       { printf("HTML TAG: %s\n", yytext); }
.|\n          ;
%%
int main(int argc, char **argv)
{
    if (argc == 2) { yyin = fopen(argv[1], "r"); if (!yyin) return 1; }
    yylex(); return 0;
}
