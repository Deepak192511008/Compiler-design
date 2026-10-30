#include <stdio.h>
#include <string.h>

int main(void)
{
    int ch, vowels = 0;
    while ((ch = getchar()) != EOF)
        if (strchr("aeiouAEIOU", ch) != NULL) vowels++;
    printf("Number of vowels: %d\n", vowels);
    return 0;
}
