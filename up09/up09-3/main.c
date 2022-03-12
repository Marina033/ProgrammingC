#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int
create_process(char *cmd)
{
    if (!fork()) {
        execlp(cmd, cmd, NULL);
        exit(1);
    }

    int status;
    if (wait(&status) == -1) {
        exit(1);
    }
    if (WIFEXITED(status)) {
        return !WEXITSTATUS(status);
    }
    return 0;
}

int
main(int argc, char **argv)
{
    int success1 = create_process(argv[1]);
    int success2 = 0;
    if (!success1) {
        success2 = create_process(argv[2]);
    }
    int success3 = 0;
    if (success1 || success2) {
        success3 = create_process(argv[3]);
    }

    if ((success1 || success2) && success3) {
        return 0;
    }
    return 1;
}
