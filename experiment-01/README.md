# Experiment 1: Lexical Analyzer in C

The analyzer ignores redundant spaces, tabs, newlines, and both `//` and
`/* ... */` comments. It identifies identifiers, numeric/string/character
constants, operators, and special symbols.

## Compile and run

```text
gcc lexical_analyzer.c -o lexical_analyzer
./lexical_analyzer sample.c
```

On Windows with MinGW:

```text
gcc lexical_analyzer.c -o lexical_analyzer.exe
lexical_analyzer.exe sample.c
```

The expected output for the supplied sample is in `output.txt`.
