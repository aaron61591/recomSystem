/*************************************************************************
    > File Name: sigcommon.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月12日 星期三 14时46分16秒
 ************************************************************************/

#include <signal.h>

typedef void sigfunc(int);

sigfunc *signal(int signo, sigfunc *func) {

    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}

void sig_chld(int signo) {

    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)
) > 0){
        printf("child %d terminated\n", pid);
    }
    return;
}

