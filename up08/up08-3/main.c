#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void)
{
    pid_t p1 = fork();
    if (p1 > 0) {
        pid_t p2 = fork();
        if (p2 > 0) {
            pid_t p3 = fork();
            if (p3 > 0) {
                while (wait(NULL) != -1);
            } else {
                char buf[10];
                read(0, buf, 8);
                int x = atoi(buf);
                printf("3 %d\n", x * x);
                exit(0);
            }
        } else {
            char buf[10];
            read(0, buf, 8);
            int x = atoi(buf);
            printf("2 %d\n", x * x);
            exit(0);
        }
    } else {
        char buf[10];
        read(0, buf, 8);
        int x = atoi(buf);
        printf("1 %d\n", x * x);
        exit(0);
    }
    return 0;
}
