#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDENTIFIER 128

static const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

static int is_keyword(const char *identifier)
{
    size_t count = sizeof(keywords) / sizeof(keywords[0]);
    size_t index;

    for (index = 0; index < count; index++) {
        if (strcmp(identifier, keywords[index]) == 0)
            return 1;
    }
    return 0;
}

static int is_valid_identifier(const char *identifier)
{
    size_t index;

    if (identifier[0] == '\0' || is_keyword(identifier))
        return 0;
    if (!isalpha((unsigned char)identifier[0]) && identifier[0] != '_')
        return 0;

    for (index = 1; identifier[index] != '\0'; index++) {
        if (!isalnum((unsigned char)identifier[index]) && identifier[index] != '_')
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char identifier[MAX_IDENTIFIER];

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [identifier]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        if (strlen(argv[1]) >= sizeof(identifier)) {
            printf("%s: INVALID IDENTIFIER (maximum length is %d)\n",
                   argv[1], MAX_IDENTIFIER - 1);
            return EXIT_SUCCESS;
        }
        strcpy(identifier, argv[1]);
    } else {
        if (fgets(identifier, sizeof(identifier), stdin) == NULL) {
            fprintf(stderr, "No identifier was provided.\n");
            return EXIT_FAILURE;
        }
        identifier[strcspn(identifier, "\r\n")] = '\0';
    }

    if (is_valid_identifier(identifier))
        printf("%s: VALID IDENTIFIER\n", identifier);
    else if (is_keyword(identifier))
        printf("%s: INVALID IDENTIFIER (reserved keyword)\n", identifier);
    else
        printf("%s: INVALID IDENTIFIER\n", identifier);

    return EXIT_SUCCESS;
}
