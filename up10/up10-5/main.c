#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

unsigned long long max, x;
int fd[2][2];

int
main(int argc, char **argv)
{
    sscanf(argv[1], "%llu", &max);
    pipe(fd[0]);
    pipe(fd[1]);
    x = 1;
    write(fd[0][1], &x, sizeof(x));

    for (int i = 0; i <= 1; i++) {
        if (!fork()) {
            close(fd[1 - i][0]);
            close(fd[i][1]);
            while (1) {
                read(fd[i][0], &x, sizeof(x));
                if (x == max) {
                    close(fd[i][0]);
                    close(fd[1 - i][1]);
                    exit(0);
                }
                printf("%d %llu\n", i + 1, x);
                fflush(stdout);
                x++;
                if (x == max) {
                    close(fd[i][0]);
                    close(fd[1 - i][1]);
                    exit(0);
                }
                write(fd[1 - i][1], &x, sizeof(x));
            }
        }
    }

    wait(NULL);
    write(fd[0][1], &max, sizeof(max));
    write(fd[1][1], &max, sizeof(max));
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[0][1]);
    close(fd[1][1]);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
