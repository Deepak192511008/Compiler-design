#include <stdio.h>
#include <stdlib.h>

static void count_characters(FILE *source)
{
    int ch;
    long whitespace_count = 0;
    long newline_count = 0;
    long space_count = 0;
    long tab_count = 0;

    while ((ch = fgetc(source)) != EOF) {
        switch (ch) {
        case '\n':
            newline_count++;
            break;
        case ' ':
            whitespace_count++;
            space_count++;
            break;
        case '\t':
            whitespace_count++;
            tab_count++;
            break;
        case '\r':
        case '\f':
        case '\v':
            whitespace_count++;
            break;
        default:
            break;
        }
    }

    printf("Whitespace characters (excluding newlines): %ld\n", whitespace_count);
    printf("Newline characters: %ld\n", newline_count);
    printf("Spaces: %ld\n", space_count);
    printf("Tabs: %ld\n", tab_count);
}

int main(int argc, char *argv[])
{
    FILE *source = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [source-file]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        source = fopen(argv[1], "rb");
        if (source == NULL) {
            perror("Unable to open source file");
            return EXIT_FAILURE;
        }
    }

    count_characters(source);

    if (source != stdin)
        fclose(source);
    return EXIT_SUCCESS;
}
