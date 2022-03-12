#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

int flag;

void mult(int signo)
{
    flag = 1;
}

void add(int signo)
{
    flag = 0;
}

int
main(void)
{
    signal(SIGQUIT, mult);
    signal(SIGINT, add);
    
    printf("%d\n", getpid());
    fflush(stdout);
    int32_t x;
    int32_t res = 0;
    while (scanf("%"SCNd32, &x) == 1) {
        if (!flag) {
            res = (uint32_t) res + x;
        } else {
            res = (uint32_t) res * x;
        }
        printf("%"PRId32"\n", res);
        fflush(stdout);
    }
    return 0;
}