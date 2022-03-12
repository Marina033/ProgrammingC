#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <stdint.h>

int
main (void)
{
    int fd[2], fdp[2];
    if (pipe(fd) == -1) {
        return 0;
    }
    if (pipe(fdp) == -1) {
        return 0;
    }
    int dummy = 42;
    if (write(fdp[1], &dummy, sizeof(dummy)) != sizeof(dummy)) {
        return 0;
    }
    int pid = fork();
    if (pid == -1) {
        return 0;
    }
    if (pid) {
        close(fd[0]);
        read(fdp[0], &dummy, sizeof(dummy));
        int32_t x;
        while (scanf("%"SCNd32, &x) == 1) {
            if (write(fd[1], &x, sizeof(x)) != sizeof(x)) {
                return 0;
            }
        }
        write(fdp[1], &dummy, sizeof(dummy));
        close(fd[1]);
        close(fdp[0]);
        close(fdp[1]);
        wait(NULL);
    } else {
        close(fd[1]);
        pid = fork();
        if (pid == -1) {
            return -1;
        }
        if (!pid) {
            int32_t x, sum;
            int flag = 1;
            while (flag) {
                read(fdp[0], &dummy, sizeof(dummy));
                if (read(fd[0], &x, sizeof(x)) == -1) {
                    write(fdp[0], &dummy, sizeof(dummy));
                } else {
                    flag = 0;
                }
            }
            close(fdp[0]);
            close(fdp[1]);
            sum = x;
            while (read(fd[0], &x, sizeof(x)) == sizeof(x)) {
                sum += x;
            }
            close(fd[0]);
            printf("%"PRId32"\n", sum);
        } else {
            close(fd[0]);
            close(fdp[0]);
            close(fdp[1]);
            wait(NULL);
        }
    }
    return 0;
}







