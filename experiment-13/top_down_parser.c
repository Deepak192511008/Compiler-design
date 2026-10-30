#include <stdio.h>
#include <string.h>

static const char *text;
static int position;

/* Grammar: S -> a S b | epsilon */
static int parse_s(void)
{
    if (text[position] == 'a') {
        position++;
        if (!parse_s() || text[position] != 'b') return 0;
        position++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    char input[256];
    if (argc > 1) text = argv[1];
    else { printf("Input string: "); if (!fgets(input, sizeof(input), stdin)) return 1;
           input[strcspn(input, "\r\n")] = '\0'; text = input; }
    position = 0;
    printf("%s\n", parse_s() && text[position] == '\0' ? "String accepted" : "String rejected");
    return 0;
}
