# hi world

1. display,
   - A working history
   - Show a prompt when waiting for a new command ??
2. expanding (reading environment variable?) & parsing,
   - Environment variables expansion
   - Not interpret unclosed quotes or unspecified special characters like \ or ;
     - handle undefined
   - Single and double quote support
   - $? should expand to the exit status of the most recently executed foreground pipeline.
3. signals

   - Signals :
     - ctrl-C print a new prompt on a newline
     - ctrl-D exit the shell.
     - ctrl-\ do nothing

4. built-ins,
   - Builtins:
     - cd with relative or absolute path
     - echo with -n
     - pwd
     - export
     - unset
     - env
     - exit
5. piping & redirection,

   - Redirections :
     - `<` should redirect input
     - `>` should redirect output
     - `<<` read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
     - `>>` should redirect output with append mode
     - Piping `|`
   - Combos
     1. \> (replace), >> (append)
        - creates file
        - edge cases?
     2. < , <<
        - 2 versions (probably handle it in parsing)
          - cat < notes.md
          - < notes.md cat
     3. |
        - pipe

6. Files

typedef struct s_command
{
char \*str;
char pipe;
} t_command;

Example
typedef struct s_command
{
char \*str = "echo -n hi";
char pipe = 1;
} t_command;

s_command \*commands = malloc(sizeof(5 + 1));
commands[5] = NULL;

3. heredoc & executing,

- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)

TBD

1. heredoc?
2. files how to pass in

Random

- Not use more than one global variable

Minor

- Handle "", e.g. if user enters "", remove it? for export?

$ unset Z="asljdfl"
bash: unset: `Z=asljdfl': not a valid identifier

Isaac's To Do:

- test cd with many paths + ~
- move `export` to built-ins; remove `env` & `export` from processes
- remove char \*\*envp away from parent_process
- clean up ft_error and ft_perror
- double check expansion of ~ with my ft_cd
- heredoc ignores all signals, but character is displayed on screen. Registers as one new line
