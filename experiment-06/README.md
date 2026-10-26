# Experiment 6: Identifier Validator

This C lexical analyzer tests whether a given identifier follows C naming
rules:

- The first character must be an alphabetic character or underscore.
- Remaining characters must be alphabetic characters, digits, or underscores.
- Reserved C keywords are rejected.
- Identifiers are limited to 127 characters by this implementation.

## Compile and run

```text
gcc identifier_validator.c -o identifier_validator
./identifier_validator compiler_2026
```

Or provide an identifier through standard input:

```text
echo compiler_2026 | ./identifier_validator
```

On Windows with MinGW:

```text
gcc identifier_validator.c -o identifier_validator.exe
identifier_validator.exe compiler_2026
```

The expected output for `sample.txt` is in `output.txt`.
