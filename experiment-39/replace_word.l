%option noyywrap
%{
#include <stdio.h>
#include <string.h>
char old_word[128], new_word[128];
%}
%%
[A-Za-z]+ { if (strcmp(yytext, old_word) == 0) fputs(new_word, yyout); else ECHO; }
.|\n      ECHO;
%%
int main(int argc, char **argv)
{
    if (argc != 3) { fprintf(stderr, "Usage: %s old new < input\n", argv[0]); return 1; }
    strncpy(old_word, argv[1], sizeof(old_word) - 1); old_word[sizeof(old_word) - 1] = '\0';
    strncpy(new_word, argv[2], sizeof(new_word) - 1); new_word[sizeof(new_word) - 1] = '\0';
    yyout = stdout; yylex(); return 0;
}
