#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int fd[3][2];

void
term(pid_t *pids, int n)
{
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][0]);
    close(fd[2][1]);
    for (int i = 1; i <= n; i++) {
        kill(pids[i], SIGKILL);
    }
    exit(1);
}

int
main(int argc, char **argv)
{
    if (argc == 1) {
        return 0;
    }
    if (pipe(fd[0]) == -1) {
        exit(1);
    }
    if (pipe(fd[1]) == -1) {
        exit(1);
    }
    if (pipe(fd[2]) == -1) {
        exit(1);
    }

    for (int i = 0; i < (argc - 1) / 3; i++) {
        int proc_num = 3 * i + 1;
        pids[proc_num] = fork();
        if (pids[proc_num] == -1) {
            term(pids, argc - 1);
        }
        if (!pids[proc_num]) {

            if (i > 0 && dup2(fd[i % 3][0], 0) == -1) {
                exit(1);
            }

            if (proc_num != argc - 1) {
                if (dup2(fd[i % 3 + 1][1], 1) == -1) {
                    exit(1);
                }
            }
            close(fd[1 - (i & 1)][1]);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }

        close(fd[i & 1][0]);
        close(fd[i & 1][1]);
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            term(pids, i);
        }

        if (pipe(fd[i & 1]) == -1) {
            term(pids, i);
        }
    }

    return 0;
}
