run "make" command in the terminal,to get "prompt" as output.
main.c - takes input from termianl and using strtok it passes the tokens to function cmd.It also checks whether a process is bg or fg.
cmd.c - according to token given. It executes the command.
extract.c - it extracts the text after '$'and uses it to get value of the environment variable
abo_chil.c - this is used to get the pid of the bg process , when it exits.
This shell can executes commands like ls,cd,pwd,echo... with flags included and can run a process in bg and foreground and also gives the pinfo of process. 