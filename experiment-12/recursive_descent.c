#include <ctype.h>
#include <stdio.h>
#include <string.h>

static const char *input;
static int position;

static void spaces(void) { while (isspace((unsigned char)input[position])) position++; }
static int accept(char expected)
{
    spaces();
    if (input[position] == expected) { position++; return 1; }
    return 0;
}

static int expression(void);

static int factor(void)
{
    spaces();
    if (isalpha((unsigned char)input[position])) {
        while (isalnum((unsigned char)input[position]) || input[position] == '_') position++;
        return 1;
    }
    if (accept('(') && expression() && accept(')')) return 1;
    return 0;
}

static int term(void)
{
    if (!factor()) return 0;
    while (accept('*')) if (!factor()) return 0;
    return 1;
}

static int expression(void)
{
    if (!term()) return 0;
    while (accept('+')) if (!term()) return 0;
    return 1;
}

int main(int argc, char **argv)
{
    char buffer[256];
    if (argc > 1) input = argv[1];
    else { printf("Expression: "); if (!fgets(buffer, sizeof(buffer), stdin)) return 1; input = buffer; }
    position = 0;
    printf("%s\n", expression() && (spaces(), input[position] == '\0') ?
           "Accepted" : "Rejected");
    return 0;
}
