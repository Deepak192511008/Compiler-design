#include <stdio.h>

int main(void)
{
    puts("Grammar: E -> E+T | T, T -> T*F | F, F -> (E) | id");
    puts("TRAILING(E) = { ), id }");
    puts("TRAILING(T) = { ), id }");
    puts("TRAILING(F) = { ), id }");
    return 0;
}
