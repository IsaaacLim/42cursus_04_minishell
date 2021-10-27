# Minishell

## Project Structure
1. File structure
- Headers are in `includes`, source files are in `src`, Makefile is in the root dir.
- libft has it's own separate, but similar structure.
2. Header file
- functions are arranged alphabetically of their function **name**, not function **type**. *(let me know your preference)*
3. Libft functions
- I try to work with the original libft as much as possible.
- I only include functions that are being used for the project so that it'll be less clustered.
- Currently all libft functions unmodified. If I modify any, I'll add a "_bonus" to the file and function name. *(let me know your preference)*
4. Minishell functions
- Functions name are as concise as my creativity allows it.
> Currently for clarity purposes, I'll make it as long as it's required.
- Functions under the same functionality are grouped under the same file name.
> Currently for clarity purposes, I won't purposely design them to be compact, but rather create many functions that does one task; "//temporary" are noted on features will likely be relocated.
- Static functions are created to 
