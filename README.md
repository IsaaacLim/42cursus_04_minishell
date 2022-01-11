# Minishell 🐚

#### In Collaboration with: [Jia Ren](https://github.com/jiaaren)

## Project Description

1. Display
   - Show a prompt when waiting for a new commands
   - Have a working history

2. Expanding & Parsing
   - Environment variables expansion
   - Doesn't interpret unclosed quotes or unspecified special characters like `\` or `;`
     - handle undefined
   - Single `'` and double `"` quote support
   - `$?` should expand to the exit status of the most recently executed foreground pipeline.

3. Signals
    - `ctrl-C` print a new prompt on a newline
    - `ctrl-D` exit the shell.
    - `ctrl-\` do nothing

4. Built-ins
    - `cd` with relative or absolute path
    - `echo` with -n
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`

5. Piping & Redirection
    - `<` should redirect input
    - `>` should redirect output
    - `<<` read input from the current source until a line containing only the delimiter is seen
    - `>>` should redirect output with append mode
    - Piping `|`

---
## Resources

1. Executor:

- Creating pipelines between parent and child *(unused)* [jameshfisher](https://jameshfisher.com/2017/02/17/how-do-i-call-a-program-in-c-with-pipes/)
- Creating pipelines between multiple childrens *(used)* [purdue.edu](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

2. Signals:

- ctrl-D / EOF
    - What's with ctrl-D [stack exchange](https://unix.stackexchange.com/questions/110240/why-does-ctrl-d-eof-exit-the-shell)
    - How to handle it [IBM tcsetattr](https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-tcsetattr-set-attributes-terminal#:~:text=FeedbackProduct%20list-,tcsetattr()%20%E2%80%94%20Set%20the%20attributes%20for%20a%20terminal,-Standards)

3. Process exit status

   1. If child process wasn't interupted, WIFEXITED = TRUE and WEXITSTATUS macro returns the exit code specified by the child.
   2. If child process was interupted, WIFEXITED = FALSE and WEXITSTATUS macro has no meaning; If the cause of exit is raised by a signal, WIFSIGNALED = TRUE and WTERMSIG macro is used to determine which signal was raised.

- WIFEXITED [IBM wifexited](https://www.ibm.com/docs/en/ztpf/2020?topic=zca-wifexitedquery-status-see-if-child-process-ended-normally)
- WEXITSTATUS [IBM wexitstatus](https://www.ibm.com/docs/en/ztpf/2020?topic=apis-wexitstatusobtain-exit-status-child-process)
- WIFSIGNALED [IBM wifsignaled](https://www.ibm.com/docs/en/ztpf/2020?topic=zca-wifsignaledquery-status-see-if-child-process-ended-abnormally)
- WTERMSIG [IBM wtermsig](https://www.ibm.com/docs/en/ztpf/2020?topic=zca-wtermsig-determine-which-signal-caused-child-process-exit)
