# Experiment 4: Arithmetic Operator Lexical Analyzer

This C program scans an input expression and recognizes the regular arithmetic
operators `+`, `-`, `*`, and `/`. It reports each recognized operator with its
line number, counts each operator, and reports other operator symbols such as
`=` as invalid for this experiment.

## Compile and run

```text
gcc arithmetic_operator_lexer.c -o arithmetic_operator_lexer
./arithmetic_operator_lexer sample.txt
```

On Windows with MinGW:

```text
gcc arithmetic_operator_lexer.c -o arithmetic_operator_lexer.exe
arithmetic_operator_lexer.exe sample.txt
```

The expected output for `sample.txt` is in `output.txt`.
