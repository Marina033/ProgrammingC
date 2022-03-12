#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);

        if (!fork()) { //cmd1
            int file1 = open(argv[4], O_RDONLY, 0600);
            if (file1 == -1) exit(1);
            dup2(file1, 0);
            close(file1);

            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }

        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            if (fork()) { //cmd2
                execlp(argv[2], argv[2], NULL);
                _exit(1);
            }
            wait(NULL);
        }

        return 0;
    }

    if (!fork()) { //cmd3
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);

        int file2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND);
        dup2(file2, 1);
        close(file2);

        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
