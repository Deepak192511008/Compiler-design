#include <stdio.h>

int main(void)
{
    printf("Original grammar:\n");
    printf("S -> iEtS | iEtSeS | a\nE -> b\n\n");
    printf("Grammar after left factoring:\n");
    printf("S  -> iEtS S' | a\n");
    printf("S' -> eS | epsilon\n");
    printf("E  -> b\n");
    return 0;
}
