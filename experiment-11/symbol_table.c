#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 50
#define NAME_SIZE 32

typedef struct {
    char name[NAME_SIZE];
    char type[NAME_SIZE];
    int address;
} Symbol;

static Symbol table[MAX_SYMBOLS];
static int count;

static int find_symbol(const char *name)
{
    int i;
    for (i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
            return i;
    return -1;
}

static void insert_symbol(void)
{
    Symbol symbol;
    if (count == MAX_SYMBOLS) { puts("Symbol table is full."); return; }
    printf("Name and type: ");
    scanf("%31s %31s", symbol.name, symbol.type);
    if (find_symbol(symbol.name) >= 0) { puts("Symbol already exists."); return; }
    symbol.address = 1000 + count * 4;
    table[count++] = symbol;
    puts("Symbol inserted.");
}

static void display_table(void)
{
    int i;
    printf("\n%-20s %-15s %s\n", "NAME", "TYPE", "ADDRESS");
    for (i = 0; i < count; i++)
        printf("%-20s %-15s %d\n", table[i].name, table[i].type, table[i].address);
}

static void search_symbol(void)
{
    char name[NAME_SIZE];
    int position;
    printf("Name to search: ");
    scanf("%31s", name);
    position = find_symbol(name);
    if (position < 0) puts("Symbol not found.");
    else printf("Found: %s, %s, address %d\n", table[position].name,
                table[position].type, table[position].address);
}

static void delete_symbol(void)
{
    char name[NAME_SIZE];
    int position, i;
    printf("Name to delete: ");
    scanf("%31s", name);
    position = find_symbol(name);
    if (position < 0) { puts("Symbol not found."); return; }
    for (i = position; i < count - 1; i++) table[i] = table[i + 1];
    count--;
    puts("Symbol deleted.");
}

int main(void)
{
    int choice;
    do {
        printf("\n1.Insert  2.Search  3.Delete  4.Display  5.Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) insert_symbol();
        else if (choice == 2) search_symbol();
        else if (choice == 3) delete_symbol();
        else if (choice == 4) display_table();
    } while (choice != 5);
    return 0;
}
