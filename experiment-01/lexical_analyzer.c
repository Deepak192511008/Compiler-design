#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEXEME 256

static void print_token(const char *type, const char *lexeme, int line)
{
    printf("%-14s %-20s line %d\n", type, lexeme, line);
}

static int is_identifier_start(int ch)
{
    return isalpha((unsigned char)ch) || ch == '_';
}

static int is_identifier_part(int ch)
{
    return isalnum((unsigned char)ch) || ch == '_';
}

static void read_identifier(FILE *source, int first, int *line)
{
    char lexeme[MAX_LEXEME];
    size_t length = 0;
    int ch = first;

    do {
        if (length < sizeof(lexeme) - 1)
            lexeme[length++] = (char)ch;
        ch = fgetc(source);
    } while (ch != EOF && is_identifier_part(ch));

    lexeme[length] = '\0';
    if (ch != EOF)
        ungetc(ch, source);
    print_token("IDENTIFIER", lexeme, *line);
}

static void read_number(FILE *source, int first, int *line)
{
    char lexeme[MAX_LEXEME];
    size_t length = 0;
    int ch = first;
    int has_decimal = 0;

    do {
        if (length < sizeof(lexeme) - 1)
            lexeme[length++] = (char)ch;
        ch = fgetc(source);
        if (ch == '.' && !has_decimal)
            has_decimal = 1;
    } while (ch != EOF && (isdigit((unsigned char)ch) || ch == '.'));

    lexeme[length] = '\0';
    if (ch != EOF)
        ungetc(ch, source);
    print_token("CONSTANT", lexeme, *line);
}

static void read_quoted(FILE *source, int quote, int *line)
{
    char lexeme[MAX_LEXEME];
    size_t length = 0;
    int ch;

    lexeme[length++] = (char)quote;
    while ((ch = fgetc(source)) != EOF) {
        if (length < sizeof(lexeme) - 1)
            lexeme[length++] = (char)ch;
        if (ch == '\\') {
            ch = fgetc(source);
            if (ch == EOF)
                break;
            if (length < sizeof(lexeme) - 1)
                lexeme[length++] = (char)ch;
        } else if (ch == quote) {
            break;
        } else if (ch == '\n') {
            (*line)++;
            break;
        }
    }

    lexeme[length] = '\0';
    print_token(quote == '"' ? "STRING CONSTANT" : "CHAR CONSTANT", lexeme, *line);
}

static void read_operator(FILE *source, int first, int *line)
{
    char lexeme[3] = {(char)first, '\0', '\0'};
    int next = fgetc(source);

    if ((first == '=' || first == '!' || first == '<' || first == '>') && next == '=') {
        lexeme[1] = (char)next;
    } else if ((first == '+' && (next == '+' || next == '=')) ||
               (first == '-' && (next == '-' || next == '=')) ||
               (first == '*' && next == '=') ||
               (first == '/' && next == '=') ||
               (first == '%' && next == '=') ||
               (first == '&' && next == '&') ||
               (first == '|' && next == '|')) {
        lexeme[1] = (char)next;
    } else if (next != EOF) {
        ungetc(next, source);
    }

    print_token("OPERATOR", lexeme, *line);
}

static void analyze(FILE *source)
{
    int ch;
    int line = 1;

    while ((ch = fgetc(source)) != EOF) {
        if (isspace((unsigned char)ch)) {
            if (ch == '\n')
                line++;
            continue;
        }

        if (ch == '/') {
            int next = fgetc(source);
            if (next == '/') {
                while ((ch = fgetc(source)) != EOF && ch != '\n')
                    ;
                if (ch == '\n')
                    line++;
                continue;
            }
            if (next == '*') {
                int previous = 0;
                while ((ch = fgetc(source)) != EOF) {
                    if (ch == '\n')
                        line++;
                    if (previous == '*' && ch == '/')
                        break;
                    previous = ch;
                }
                continue;
            }
            if (next != EOF)
                ungetc(next, source);
            read_operator(source, ch, &line);
        } else if (is_identifier_start(ch)) {
            read_identifier(source, ch, &line);
        } else if (isdigit((unsigned char)ch)) {
            read_number(source, ch, &line);
        } else if (ch == '"' || ch == '\'') {
            read_quoted(source, ch, &line);
        } else if (strchr("=<>!+-*%&|", ch) != NULL) {
            read_operator(source, ch, &line);
        } else {
            char lexeme[2] = {(char)ch, '\0'};
            print_token("SPECIAL SYMBOL", lexeme, line);
        }
    }
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

    printf("%-14s %-20s %s\n", "TOKEN TYPE", "LEXEME", "LOCATION");
    printf("--------------------------------------------------------\n");
    analyze(source);

    if (source != stdin)
        fclose(source);
    return EXIT_SUCCESS;
}
