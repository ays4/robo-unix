//
// Created by Anton Shvab on 2019-03-23.
//

#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <zconf.h>
#include <stdlib.h>

main(int argc, char **argv)
{
    int fd;
    struct rlimit flim;

    if (getppid() != 1)
    {
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
    }

    if (fork() != 0)
        exit(0);

    setsid();

    getrlimit(RLIMIT_NOFILE, &flim);
    for (fd = 0; fd < flim.rlim_max; fd++)
        close(fd);

    chdir("/");

    openlog("Скелет демона", LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Демон начал плодотворную работу...");
    closelog();

    // Do some usefull work here...
}