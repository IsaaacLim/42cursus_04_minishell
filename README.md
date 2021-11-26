# Minishell

## Project Structure

1. File structure

- Headers are in `includes`, source files are in `src`, Makefile is in the root dir.
- libft has it's own separate, but similar structure.

2. Header file

- Functions are arranged alphabetically according to function **name**, not function **type**. _(let me know your preference)_

3. Libft functions

- I try to work with the original libft as much as possible.
- I only include functions that are being used for the project so that it'll be less clustered.
- Currently all libft functions are unmodified. If modified, I'll append a "\_bonus" to the file and function name. _(let me know your preference)_

4. Minishell functions

- Functions name are as concise as my creativity allows it.
  > But for clarity purposes, I'll make it as long as it's required.
- Static functions are declared for tracability.
- Functions under the same functionality category are grouped under the same file.
  > But for clarity purposes, I won't purposely design each function to be compact, but rather create many functions that does only one task

> "//temporary" are noted on features will that likely be relocated.

- Object files are named according to the general purpose of the functions contained in it.

## Resources

1. Executor:

- (unused) https://jameshfisher.com/2017/02/17/how-do-i-call-a-program-in-c-with-pipes/
- (used) https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
