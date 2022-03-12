#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>

volatile int32_t cnt;

void
hndlr(int signo)
{
    if (signo == SIGUSR1) {
        cnt = (uint32_t) cnt + 5;
        printf("%d %"PRId32"\n", SIGUSR1, cnt);
        fflush(stdout);
    }
    if (signo == SIGUSR2) {
        cnt = (uint32_t) cnt - 4;
        printf("%d %"PRId32"\n", SIGUSR2, cnt);
        fflush(stdout);
    }
    if (cnt < 0) {
        exit(0);
    }
}

int
main(void)
{
    sigset_t mask, oldmask;
    sigemptyset(&oldmask);
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = hndlr;
    sa.sa_mask = mask;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        sigprocmask(SIG_BLOCK, &mask, &oldmask);
        sigsuspend(&oldmask);
        sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
    }
}