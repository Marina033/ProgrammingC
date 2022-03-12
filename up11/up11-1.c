#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int cnt;

void 
hndlr(int s)
{
    if (cnt == 5) {
        exit(0);
    }
    printf("%d\n", cnt++);
    fflush(stdout);
}
    
int 
main(void)
{
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigemptyset(&oldmask);
    sigaddset(&mask, SIGHUP);
    
    struct sigaction sa;
    sa.sa_handler = hndlr;
    sa.sa_mask = mask;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGHUP, &sa, NULL);
    
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        sigsuspend(&oldmask);
    }
}