#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_arithmetic_operator(int ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int is_other_operator(int ch)
{
    return ch == '=' || ch == '%' || ch == '!' || ch == '<' || ch == '>' ||
           ch == '&' || ch == '|';
}

static void scan(FILE *source)
{
    int ch;
    int line = 1;
    int counts[4] = {0, 0, 0, 0};
    int total = 0;

    printf("%-8s %-12s %s\n", "LINE", "STATUS", "OPERATOR");
    printf("----------------------------------\n");

    while ((ch = fgetc(source)) != EOF) {
        int index;

        if (ch == '\n') {
            line++;
            continue;
        }
        if (isspace((unsigned char)ch))
            continue;

        index = is_arithmetic_operator(ch) ?
                (int)(ch == '+' ? 0 : ch == '-' ? 1 : ch == '*' ? 2 : 3) : -1;
        if (index >= 0) {
            printf("%-8d %-12s %c\n", line, "VALID", ch);
            counts[index]++;
            total++;
        } else if (is_other_operator(ch)) {
            printf("%-8d %-12s %c\n", line, "INVALID", ch);
        }
    }

    printf("\nOperator count\n");
    printf("+ : %d\n", counts[0]);
    printf("- : %d\n", counts[1]);
    printf("* : %d\n", counts[2]);
    printf("/ : %d\n", counts[3]);
    printf("Total valid arithmetic operators: %d\n", total);

}

int main(int argc, char *argv[])
{
    FILE *source = stdin;

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

    scan(source);

    if (source != stdin)
        fclose(source);
    return EXIT_SUCCESS;
}
