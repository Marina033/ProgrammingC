#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

unsigned long long max, x;
int num;
pid_t pid, other_pid;
int fd[2];

void
hndlr(int s)
{
}

void
term(void)
{
    close(fd[0]);
    close(fd[1]);
    kill(other_pid, SIGUSR1);
    _exit(0);
}

void
pingpong(void)
{
    while (1) {
        read(fd[0], &x, sizeof(x));
    if (x == max) {
        close(fd[0]);
            close(fd[1]);
            _exit(0);
    }
        printf("%d %llu\n", num, x);
    fflush(stdout);
        x++;
        if (x == max) {
            term();
        }
    write(fd[1], &x, sizeof(x));
        kill(other_pid, SIGUSR1);
        pause();
    }
}

int 
main(int argc, char **argv)
{
    struct sigaction sa;
    sa.sa_handler = hndlr;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    
    sscanf(argv[1], "%llu", &max);
    pipe(fd);
    
    if (!fork()) { //child1
        pid = getpid();
        write(fd[1], &pid, sizeof(pid));
        pause();
        
        read(fd[0], &other_pid, sizeof(other_pid));

        num = 1;
    x = 1;
    if (x == max) {
        term();
    }
    printf("%d %llu\n", num, x);
    fflush(stdout);
        x++;
    if (x == max) {
        term();
    }
    write(fd[1], &x, sizeof(x));
    kill(other_pid, SIGUSR1);
    pause();

        pingpong();
    }
    
    if (!fork()) { //child2 
        read(fd[0], &other_pid, sizeof(other_pid));
        pid = getpid();
        write(fd[1], &pid, sizeof(pid));
        kill(other_pid, SIGUSR1);
        pause();
  
        num = 2;
        
        pingpong();
    }
    
    close(fd[0]);
    wait(NULL); 
    write(fd[1], &max, sizeof(max));
    close(fd[1]);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}