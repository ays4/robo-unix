//
// Created by Anton Shvab on 2019-03-23.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char ** environ;

#define CMDSIZE 80
#define MAXPATH 300
#define CD 1
#define ECHO 2
#define EXEC 3
#define PROGRAM 1000

// TODO: implement parse_command
int parse_command(char *cmdbuf, char *path, char **arguments);

main()
{
    char cmd[CMDSIZE];
    int command;
    int cmdsize;
    int pid;
    int stat_loc;
    char **args;
    char cmdpath[MAXPATH];

    while (1)
    {
        write(1, "$", 2);

        cmdsize = read(0, cmd, CMDSIZE);
        cmd[cmdsize-1] = '\0';
        command = parse_command(cmd, cmdpath, args);

        switch(command)
        {
            case(CD): chdir(args[0]); break;
            case(ECHO):
                write(1, args[0], strlen(args[0]));
                break;
            case(EXEC):
                execve(cmdpath, args, environ);
                write(2, "shell: cannot execute", 21);
                break;
            case(PROGRAM):
                pid = fork();
                if (pid < 0)
                    write(2, "shell: cannot fork", 18);
                else if (pid == 0)
                {
                    execve(cmdpath, args, environ);
                    write(2, "shell: cannot execute", 21);
                }
                else
                    wait(&stat_loc);
                break;
        }

    }
}
