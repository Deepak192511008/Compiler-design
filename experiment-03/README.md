# Experiment 3: Lexer That Ignores Whitespace and Comments

This C lexical analyzer ignores redundant spaces, tabs, newlines, `//`
comments, and `/* ... */` comments. It prints the remaining lexical units as
a single space-separated token stream. Text inside string and character
literals is preserved, including comment-like text inside those literals.

## Compile and run

```text
gcc whitespace_comment_lexer.c -o whitespace_comment_lexer
./whitespace_comment_lexer sample.c
```

On Windows with MinGW:

```text
gcc whitespace_comment_lexer.c -o whitespace_comment_lexer.exe
whitespace_comment_lexer.exe sample.c
```

The expected token stream for `sample.c` is in `output.txt`.
