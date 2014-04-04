/*************************************************************************
    > File Name: mydaemon.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月04日 星期五 17时13分49秒
 ************************************************************************/

#include "mydaemon.h"

int daemon_init(const char *pname, int facility) {

    int i;
    pid_t pid;

    if ((pid = fork()) < 0)
        return(-1);
    else if (pid)
        exit(0);

    /* running in background */

    if (setsid() < 0)
        return -1;

    /* have a new session, drop all teminals */

    if ((pid = fork()) < 0)
        return(-1);
    else if (pid)
        exit(0);

    /* do not be the header of session */

    chdir("/");

    /* close off file descriptors */
    for (i = 0; i < MAXFD; ++i)
        close(i);

    /* redirect stdin, stdout, and stderr to /dev/null */
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    openlog(pname, LOG_PID, facility);

    /* change log */
    daemon_proc = 1;

    return(0);
}
