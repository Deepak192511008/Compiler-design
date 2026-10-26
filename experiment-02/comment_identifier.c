#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

static char *skip_whitespace(char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r')
        text++;
    return text;
}

static int classify_line(char *line, int *inside_block_comment)
{
    char *text = skip_whitespace(line);

    if (*inside_block_comment) {
        if (strstr(text, "*/") != NULL)
            *inside_block_comment = 0;
        return 1;
    }

    if (strncmp(text, "//", 2) == 0)
        return 1;

    if (strncmp(text, "/*", 2) == 0) {
        if (strstr(text + 2, "*/") == NULL)
            *inside_block_comment = 1;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *source = stdin;
    char line[MAX_LINE];
    int line_number = 0;
    int inside_block_comment = 0;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [source-file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        source = fopen(argv[1], "r");
        if (source == NULL) {
            perror("Unable to open source file");
            return EXIT_FAILURE;
        }
    }

    printf("%-8s %-15s %s\n", "LINE", "CLASSIFICATION", "TEXT");
    printf("------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), source) != NULL) {
        char display[MAX_LINE];
        int is_comment;

        line_number++;
        strcpy(display, line);
        display[strcspn(display, "\r\n")] = '\0';
        is_comment = classify_line(line, &inside_block_comment);
        printf("%-8d %-15s %s\n", line_number,
               is_comment ? "COMMENT" : "NOT A COMMENT", display);
    }

    if (source != stdin)
        fclose(source);
    return EXIT_SUCCESS;
}
