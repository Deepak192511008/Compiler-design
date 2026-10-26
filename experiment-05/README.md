# Experiment 5: Whitespace and Newline Counter

This C lexical analyzer counts whitespace characters and newline characters in
an input file. Spaces, tabs, carriage returns, form feeds, and vertical tabs
are counted as whitespace. Newlines are counted separately and are not added
to the whitespace total.

## Compile and run

```text
gcc whitespace_newline_counter.c -o whitespace_newline_counter
./whitespace_newline_counter sample.txt
```

On Windows with MinGW:

```text
gcc whitespace_newline_counter.c -o whitespace_newline_counter.exe
whitespace_newline_counter.exe sample.txt
```

The expected output for `sample.txt` is in `output.txt`.
