#include <stdio.h>

int main(void)
{
    printf("Original grammar:\n");
    printf("S -> (L) | a\nL -> L,S | S\n\n");
    printf("Grammar after eliminating left recursion:\n");
    printf("S  -> (L) | a\n");
    printf("L  -> S L'\n");
    printf("L' -> , S L' | epsilon\n");
    return 0;
}
