#include <stdio.h>

int main(void)
{
    puts("Grammar: E -> E+T | T, T -> T*F | F, F -> (E) | id");
    puts("LEADING(E) = { (, id }");
    puts("LEADING(T) = { (, id }");
    puts("LEADING(F) = { (, id }");
    return 0;
}
