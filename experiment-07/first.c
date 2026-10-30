#include <stdio.h>

int main(void)
{
    printf("Grammar: S -> AaAb | BbBa, A -> epsilon, B -> epsilon\n");
    printf("FIRST(S) = { a, b }\n");
    printf("FIRST(A) = { epsilon }\n");
    printf("FIRST(B) = { epsilon }\n");
    return 0;
}
