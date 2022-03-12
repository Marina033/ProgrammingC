#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    int fd[2];
    pipe(fd);
    pid_t p1 = fork();
    if (p1) {
        close(fd[1]);
        wait(NULL);
        time_t from_pipe;
        read(fd[0], &from_pipe, sizeof(from_pipe));
        struct tm *my_tm = localtime(&from_pipe);
        int year = 1900 + my_tm->tm_year;
        printf("Y:%d\n", year);
        close(fd[0]);

    } else {
        pid_t p2 = fork();
        if (p2) {
            close(fd[1]);
            wait(NULL);
            time_t from_pipe;
            read(fd[0], &from_pipe, sizeof(from_pipe));
            struct tm *my_tm = localtime(&from_pipe);
            int mon = 1 + my_tm->tm_mon;
            printf("M:");
            if (mon < 10) {
                printf("0");
            }
            printf("%d\n", mon);
            close(fd[0]);

        } else {
            pid_t p3 = fork();
            if (p3) {
                close(fd[1]);
                wait(NULL);
                time_t from_pipe;
                read(fd[0], &from_pipe, sizeof(from_pipe));
                struct tm *my_tm = localtime(&from_pipe);
                int day = my_tm->tm_mday;
                printf("D:");
                if (day < 10) {
                    printf("0");
                }
                printf("%d\n", day);
                close(fd[0]);

            } else {
                close(fd[0]);
                time_t cur = time(NULL);
                write(fd[1], &cur, sizeof(cur));
                write(fd[1], &cur, sizeof(cur));
                write(fd[1], &cur, sizeof(cur));
                close(fd[1]);
            }
        }
    }
    return 0;
}
