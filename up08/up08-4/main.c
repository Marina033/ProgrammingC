#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(void)
{
    int n;
    scanf("%d", &n);
    int first_p = getpid();
    for (int i = 1; i < n; i++) {
        printf("%d ", i);
        pid_t p = fork();
        if (p) {
            wait(NULL);
        }
    }
    if (getpid() == first_p) {
        printf("%d\n", n);
    }
    _exit(0);
}
