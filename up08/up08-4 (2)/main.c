#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (i < n) {
            printf("%d ", i);
        } else {
            printf("%d\n", n);
            fflush(stdout);
            pid_t p = fork();
            if (p > 0) {
                wait(NULL);
                exit(0);
            }
        }
    }
    return 0;
}
