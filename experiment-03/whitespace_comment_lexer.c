#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN 256

static void emit_token(const char *token, int *first_token)
{
    if (!*first_token)
        putchar(' ');
    fputs(token, stdout);
    *first_token = 0;
}

static void emit_word(FILE *source, int first, int *first_token)
{
    char token[MAX_TOKEN];
    size_t length = 0;
    int ch = first;

    do {
        if (length < sizeof(token) - 1)
            token[length++] = (char)ch;
        ch = fgetc(source);
    } while (ch != EOF && (isalnum((unsigned char)ch) || ch == '_'));

    token[length] = '\0';
    if (ch != EOF)
        ungetc(ch, source);
    emit_token(token, first_token);
}

static void emit_number(FILE *source, int first, int *first_token)
{
    char token[MAX_TOKEN];
    size_t length = 0;
    int ch = first;

    do {
        if (length < sizeof(token) - 1)
            token[length++] = (char)ch;
        ch = fgetc(source);
    } while (ch != EOF && (isdigit((unsigned char)ch) || ch == '.'));

    token[length] = '\0';
    if (ch != EOF)
        ungetc(ch, source);
    emit_token(token, first_token);
}

static void emit_quoted(FILE *source, int quote, int *first_token)
{
    char token[MAX_TOKEN];
    size_t length = 0;
    int ch;

    token[length++] = (char)quote;
    while ((ch = fgetc(source)) != EOF) {
        if (length < sizeof(token) - 1)
            token[length++] = (char)ch;
        if (ch == '\\') {
            ch = fgetc(source);
            if (ch == EOF)
                break;
            if (length < sizeof(token) - 1)
                token[length++] = (char)ch;
        } else if (ch == quote) {
            break;
        }
    }

    token[length] = '\0';
    emit_token(token, first_token);
}

static void emit_operator_or_symbol(FILE *source, int first, int *first_token)
{
    char token[3] = {(char)first, '\0', '\0'};
    int next = fgetc(source);

    if ((first == '=' || first == '!' || first == '<' || first == '>') && next == '=')
        token[1] = (char)next;
    else if ((first == '+' && (next == '+' || next == '=')) ||
             (first == '-' && (next == '-' || next == '=')) ||
             (first == '&' && next == '&') ||
             (first == '|' && next == '|'))
        token[1] = (char)next;
    else if (next != EOF)
        ungetc(next, source);

    emit_token(token, first_token);
}

static void analyze(FILE *source)
{
    int ch;
    int first_token = 1;

    while ((ch = fgetc(source)) != EOF) {
        if (isspace((unsigned char)ch)) {
            continue;
        }

        if (ch == '/') {
            int next = fgetc(source);
            if (next == '/') {
                while ((ch = fgetc(source)) != EOF && ch != '\n')
                    ;
                continue;
            }
            if (next == '*') {
                int previous = 0;
                while ((ch = fgetc(source)) != EOF) {
                    if (previous == '*' && ch == '/')
                        break;
                    previous = ch;
                }
                continue;
            }
            if (next != EOF)
                ungetc(next, source);
            emit_operator_or_symbol(source, '/', &first_token);
        } else if (isalpha((unsigned char)ch) || ch == '_') {
            emit_word(source, ch, &first_token);
        } else if (isdigit((unsigned char)ch)) {
            emit_number(source, ch, &first_token);
        } else if (ch == '"' || ch == '\'') {
            emit_quoted(source, ch, &first_token);
        } else if (strchr("=<>!+-*&|", ch) != NULL) {
            emit_operator_or_symbol(source, ch, &first_token);
        } else {
            char token[2] = {(char)ch, '\0'};
            emit_token(token, &first_token);
        }
    }

    putchar('\n');
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

    analyze(source);

    if (source != stdin)
        fclose(source);
    return EXIT_SUCCESS;
}
