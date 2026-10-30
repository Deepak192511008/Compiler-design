#include <stdio.h>

int main(void)
{
    printf("Grammar: S -> AaAb | BbBa, A -> epsilon, B -> epsilon\n");
    printf("FOLLOW(S) = { $ }\n");
    printf("FOLLOW(A) = { a, b }\n");
    printf("FOLLOW(B) = { a, b }\n");
    return 0;
}
