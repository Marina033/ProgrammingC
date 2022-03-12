#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

enum { RET_VALUE_OFFSET = 128 };

int
mysys (const char *str)
{
    pid_t p = fork();
    if (p == -1) {
        return -1;
    } else if (p == 0) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int status;
        wait4(p, &status, 0, NULL);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return RET_VALUE_OFFSET + WTERMSIG(status);
        }
    }
}
