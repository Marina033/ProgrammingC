#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int
main(int argc, char** argv)
{
    int fd = open(argv[1], O_RDWR);
    long long x;
    if (read(fd, &x, sizeof(x)) == 0) {
        return 0;
    }
    long long count = 1, min = x, index_min = 0;
    while (read(fd, &x, sizeof(x)) > 0) {
        if (x < min) {
            min = x;
            index_min = count;
        }
        count++;
    }

    lseek(fd, sizeof(x) * index_min, SEEK_SET);
    if (min != LLONG_MIN) {
        min = -min;
    }
    write(fd, &min, sizeof(min));
    close(fd);
}
