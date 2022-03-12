#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <sys/wait.h>

int 
main(int argc, char **argv)
{
    int n;
    sscanf(argv[1], "%d", &n);
    for (int i = 2; i <= n + 1; i++) {
        if (i > argc) {
            break;
        }
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            continue;
        }
        char cmd[PATH_MAX];
        fscanf(f, "%s", cmd);
        if (!fork()) {
            execlp(cmd, cmd, NULL);
            exit(1);
        }
    }
    
    int count = 0;
    for (int i = 2; i <= n + 1; i++) {
        int status;
        if (wait(&status) == -1) {
            break;
        }
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                count++;
            }
        }
    }
    
    for (int i = n + 2; i <= argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            continue;
        }
        char cmd[PATH_MAX];
        fscanf(f, "%s", cmd);
        if (!fork()) {
            execlp(cmd, cmd, NULL);
            exit(1);
        }
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                count++;
            }
        }
    }
    printf("%d\n", count);
    fflush(stdout);
    return 0;
}