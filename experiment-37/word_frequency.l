%option noyywrap
%{
#include <stdio.h>
#include <string.h>
char target[128]; int frequency = 0;
%}
%%
[A-Za-z]+ { if (strcmp(yytext, target) == 0) frequency++; }
.|\n      ;
%%
int main(int argc, char **argv)
{
    if (argc != 2) { fprintf(stderr, "Usage: %s word < sentence\n", argv[0]); return 1; }
    strncpy(target, argv[1], sizeof(target) - 1); target[sizeof(target) - 1] = '\0';
    yylex(); printf("Frequency of %s: %d\n", target, frequency); return 0;
}
