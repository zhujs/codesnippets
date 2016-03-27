#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

static void sig_hup(int signo)
{
    printf("SIGHUP received, pid = %d\n", getpid());
}

static void sig_cont(int signo)
{
    printf("SIGCONT received, pid = %d\n", getpid());
}

static void sig_usr1(int signo)
{
    printf("SIGUSR1 received, pid = %d\n", getpid());
}

static void pr_ids(char *name)
{
    printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
    name, getpid(), getppid(), getpgrp(), tcgetpgrp(0));
}

int main(void){
    char c;
    pid_t pid;
    pr_ids("parent");

    /* establish signal handler */
    //signal(SIGHUP, sig_hup);
    signal(SIGCONT, sig_cont);
    signal(SIGUSR1, sig_usr1);

    // 暂停的进程将在重新启动时才对信号进行响应（除了SIGKILL，SIGKILL信号就直接杀死进程）
    // 貌似暂停的进程重新启动时，若已收到多个信号，系统会按照紧急程度排序。例如若没能捕捉SIGHUP信号，而进程收到了SIGHUP及SIGUSR1信号，这时进程总是会直接hangup。
    /* stop ourself */
    kill(getpid(), SIGTSTP);
    exit(0);
}
