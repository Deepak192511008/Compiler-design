%option noyywrap
%{
#include <stdio.h>
int line_number = 1;
%}
%%
.*\n       { printf("%4d  %s", line_number++, yytext); }
.*        { if (yytext[0]) printf("%4d  %s\n", line_number++, yytext); }
%%
int main(int argc, char **argv)
{
    if (argc == 2) { yyin = fopen(argv[1], "r"); if (!yyin) return 1; }
    yylex(); return 0;
}
