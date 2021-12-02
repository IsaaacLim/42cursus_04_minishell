# hi world



typedef struct s_command
{
char \*str;
char pipe;
} t_command;

Example
typedef struct s_command`
{
char \*str = "echo -n hi";
char pipe = 1;
} t_command;

s_command \*commands = malloc(sizeof(5 + 1));
commands[5] = NULL;

3. heredoc & executing,

- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)


Minor

- Handle "", e.g. if user enters "", remove it? for export?

$ unset Z="asljdfl"
bash: unset: `Z=asljdfl': not a valid identifier
