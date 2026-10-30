#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file; int ch, in_word = 0; long characters = 0, words = 0, lines = 0;
    if (argc != 2) { fprintf(stderr, "Usage: %s file\n", argv[0]); return 1; }
    file = fopen(argv[1], "rb"); if (!file) { perror(argv[1]); return 1; }
    while ((ch = fgetc(file)) != EOF) {
        characters++; if (ch == '\n') lines++;
        if (isspace((unsigned char)ch)) in_word = 0;
        else if (!in_word) { words++; in_word = 1; }
    }
    fclose(file);
    printf("Characters: %ld\nWords: %ld\nLines: %ld\n", characters, words, lines);
    return 0;
}
