#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    int count, modulo;
    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &modulo);
    char *prog = argv[3];
    int fd12[2], fd24[2];
    pipe(fd12);
    pipe(fd24);
    
    if (!fork()) { //p1
        close(fd24[0]);
        if (!fork()) { //p2
            close(fd12[1]);
            dup2(fd12[0], 0);
            close(fd12[0]);
            dup2(fd24[1], 1);
            close(fd24[1]);
            execlp(prog, prog, NULL);
        }
        close(fd24[1]);
        close(fd12[0]);
        for (int i = 1; i <= count; i++) {
            int x = (long long) i * i % modulo;
            write(fd12[1], &x, sizeof(x));
        }
        close(fd12[1]);
        return 0;
    }
    close(fd12[0]);
    close(fd12[1]);
    close(fd24[1]);
    
    if (!fork()) { //p3
        if (!fork()) { //p4
            dup2(fd24[0], 0);
            close(fd24[0]);
            char c;
            while (scanf("%c", &c) == 1) {
                if (c == ' ') c = '\n';
                putchar(c);
            }
            return 0;
        }
        close(fd24[0]);
        return 0;
    }
    
    wait(NULL);
    wait(NULL);
    printf("0\n");
    return 0;
}