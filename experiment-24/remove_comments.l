%option noyywrap
%x COMMENT
%{
#include <stdio.h>
int comment_lines = 0;
%}
%%
"//"[^\n]*                 { comment_lines++; }
"/*"                        { comment_lines++; BEGIN(COMMENT); }
<COMMENT>"*/"              { BEGIN(INITIAL); }
<COMMENT>\n                 { comment_lines++; fputc('\n', yyout); }
<COMMENT>.                  ;
\n                          ECHO;
.                           ECHO;
%%
int main(int argc, char **argv)
{
    if (argc != 3) { fprintf(stderr, "Usage: %s input.c output.c\n", argv[0]); return 1; }
    yyin = fopen(argv[1], "r"); yyout = fopen(argv[2], "w");
    if (!yyin || !yyout) return 1;
    yylex(); fclose(yyin); fclose(yyout);
    fprintf(stderr, "Comment lines removed: %d\n", comment_lines);
    return 0;
}
