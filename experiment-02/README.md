# Experiment 2: Comment Identifier in C

This program checks whether each input line is a comment. It recognizes:

- Single-line comments beginning with `//`.
- Block comments beginning with `/*` and ending with `*/`.
- Block comments that continue across multiple lines.

Leading spaces, tabs, and carriage returns are ignored while classifying a
line. The expected output for `sample.txt` is in `output.txt`.

## Compile and run

```text
gcc comment_identifier.c -o comment_identifier
./comment_identifier sample.txt
```

On Windows with MinGW:

```text
gcc comment_identifier.c -o comment_identifier.exe
comment_identifier.exe sample.txt
```
