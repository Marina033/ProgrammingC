#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

enum { FAIL = 42 };

int
main(int argc, char **argv)
{
    pid_t p = fork();
    if (p > 0) {
        int pstatus = 0;
        wait(&pstatus);
        printf("%d\n", pstatus);
    } else if (p == 0) {
        int in = open(argv[2], O_RDONLY);
        if (in == -1) {
            return FAIL;
        }
        int out = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (out == -1) {
            return FAIL;
        }
        int err = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (err == -1) {
            return FAIL;
        }

        if (dup2(in, 0) == -1) {
            return FAIL;
        }
        if (dup2(out, 1) == -1) {
            return FAIL;
        }
        if (dup2(err, 2) == -1) {
            return FAIL;
        }

        if (close(in) == -1) {
            return FAIL;
        }
        if (close(out) == -1) {
            return FAIL;
        }
        if (close(err) == -1) {
            return FAIL;
        }

        execlp(argv[1], argv[1], NULL);
        return FAIL;
    }
    return 0;
}
