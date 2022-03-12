#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>

volatile int cur_prime;
volatile int cnt;

int
isprime(int x)
{
    if (x <= 1) {
        return 0;
    }
    for (int i = 2; i * i < x; i++)     
    {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

void
printprime(int s)
{
    if (++cnt == 4) {
        _exit(0);
    }
    printf("%d\n", cur_prime);
    fflush(stdout);
}

void
term(int s)
{
    _exit(0);
}

int
main(void)
{
    int low, high;
    scanf("%d%d", &low, &high);

    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = printprime;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = term;
    sigaction(SIGTERM, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    for (int i = low; i < high; i++) {
        if (isprime(i)) {
            cur_prime = i;
        }
    }
    
    printf("-1\n");
    fflush(stdout);
    return 0;
}
