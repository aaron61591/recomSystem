/*************************************************************************
    > File Name: init.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月14日 星期一 16时18分22秒
 ************************************************************************/

#include "init.h"

char fpath[50] = {0};
char pidpath[50] = {0};
char logpath[50] = {0};

void run_lock() {

    FILE *fp;
    int pid = getpid();
    char pstr[5];
    memset(pstr, 0, sizeof(pstr));
    sprintf(pstr, "%d", pid);
    if ((fp = fopen(pidpath, "w")) == NULL)
        err_exit("create pid file failed!");
    fwrite(pstr, sizeof(pstr), 1, fp);
    fclose(fp);
}

void run_check() {

    if (file_exist(pidpath) == 0)
        err_exit("aprs is already running now!");
}

void path_init() {

    /* get pid file path */
    getcwd(fpath, sizeof(fpath));
    strcpy(pidpath, fpath);
    strcat(pidpath, "/pid");
    strcpy(logpath, fpath);
    strcat(logpath, "/log");
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

void aprs_init(int *run_mode) {

    path_init();

    /* run lock */
    run_check();

    /* daemon running */
    if(daemon_init("[aprs server]", LOG_DAEMON) != 0)
        err_exit("deamon init failed!");
    run_lock();

    /* log initialize */
    log_init(logpath);
    set_log(get_log_fp());
    log_info("log initialized!");

    /* recom initialize */
    recom_init();
    log_info("recommand initialized!");

    /* handle son process */
    signal(SIGCHLD, sig_chld);

    /* running type */
    if (argc == 1) {
        *run_mode = 0;
    } else {
        switch(argv[1]) {
            case "-mp":
                *run_mode = 1;
                break;
            case "-mt":
                *run_mode = 2;
                break;
            default:
                *run_mode = 0;
        }
    }
}

