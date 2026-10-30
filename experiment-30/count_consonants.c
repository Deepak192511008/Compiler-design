#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int ch, consonants = 0;
    while ((ch = getchar()) != EOF) {
        ch = tolower((unsigned char)ch);
        if (isalpha((unsigned char)ch) && !strchr("aeiou", ch)) consonants++;
    }
    printf("Number of consonants: %d\n", consonants);
    return 0;
}
