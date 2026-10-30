#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[128], result[32], left[32], op, right[32];
    puts("Enter three-address statements (result=left op right), one per line; type END to stop:");
    while (fgets(line, sizeof(line), stdin) && strncmp(line, "END", 3) != 0) {
        if (sscanf(line, " %31[^=]=%31s %c %31s", result, left, &op, right) == 4) {
            printf("MOV R0, %s\n", left);
            if (op == '+') printf("ADD R0, %s\n", right);
            else if (op == '-') printf("SUB R0, %s\n", right);
            else if (op == '*') printf("MUL R0, %s\n", right);
            else if (op == '/') printf("DIV R0, %s\n", right);
            else { puts("Unsupported operator"); continue; }
            printf("MOV %s, R0\n", result);
        } else puts("Invalid three-address statement");
    }
    return 0;
}
