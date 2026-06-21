# putchar

`int putchar(int c);`

## What does this function do?

Writes 1 character to standard output (terminal or redirected to file)

## When would you use this function?

1. When you need to write a simple character for formatting, such as a space, tab, newline, etc. to separate the output of other output functions like printf or fwrite.
2. To print a specific range of characters in a loop.

## Where in your program would you call it?

Any place where you need a character to separate data or you are unsure of the value of a byte and need to debug something. This is especially true in loops to identify where bugs are.

## Why is this function better or worse than alternatives?

putchar is simpler to use than printf and only requires one argument: the character number.

## How can you use it?

