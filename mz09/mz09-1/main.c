#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    if (fork()) {
        int pstatus = 0;
        wait(&pstatus);
        printf("%d\n", pstatus);
    } else {

        int in = open(argv[2], O_RDONLY);
        if (in == -1) {
            return 42;
        }
        int out = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (out == -1) {
            return 42;
        }
        int err = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (err == -1) {
            return 42;
        }

        if (dup2(0, in) == -1) {
            return 42;
        }
        if (dup2(1, out) == -1) {
            return 42;
        }
        if (dup2(2, err) == -1) {
            return 42;
        }

        execlp(argv[1], argv[1], NULL);
    }
    return 0;
}
