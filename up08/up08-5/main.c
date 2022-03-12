#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(void)
{
    int x;
    pid_t first_pid = getpid();
    while (scanf("%d", &x) == 1) {
        pid_t p = fork();
        if (p > 0) {
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                printf("%d\n", x);
                exit(0);
            } else {
                if (getpid() == first_pid) {
                    exit(0);
                }
                exit(-1);
            }
        } else if (p == -1) {
            printf("-1\n");
            exit(-1);
        }
    }
    return 0;
}
