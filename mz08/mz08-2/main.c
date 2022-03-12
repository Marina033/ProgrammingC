#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void)
{
    pid_t p1 = fork();
    if (p1) {
        wait(NULL);
        printf("1\n");
    } else {
        pid_t p2 = fork();
        if (p2) {
            wait(NULL);
            printf("2 ");
        } else {
            printf("3 ");
        }
    }
    return 0;
}
