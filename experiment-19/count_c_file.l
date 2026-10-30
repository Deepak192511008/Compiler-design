%option noyywrap
%{
#include <stdio.h>
long characters = 0, words = 0, lines = 0;
%}
%x COMMENT
%%
"//"[^\n]*                         ;
"/*"                                BEGIN(COMMENT);
<COMMENT>"*/"                       BEGIN(INITIAL);
<COMMENT>\n                         lines++;
<COMMENT>.                          ;
\n                                  { characters++; lines++; }
[ \t\r\f\v]+                        { characters += yyleng; }
[A-Za-z_][A-Za-z0-9_]*              { characters += yyleng; words++; }
.                                   { characters++; }
%%
int main(int argc, char **argv)
{
    if (argc == 2) { yyin = fopen(argv[1], "r"); if (!yyin) return 1; }
    yylex();
    printf("Characters: %ld\nLines: %ld\nWords: %ld\n", characters, lines, words);
    return 0;
}
