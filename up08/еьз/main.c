#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int
main(void)
{
    int x;
    pid_t first = getpid();
    while (scanf("%d", &x) == 1) {
        pid_t p = fork();
        if (p > 0) {
            int status;
            wait(&status);
            if (WEXITSTATUS(status) != 1) {
                printf("%d\n", x);
                return 0;
            }
            if (getpid() == first) {
                printf("-1\n");
                return 0;
            }
            return 1;
        } else if (p == -1) {
            return 1;
        }
    }
}
