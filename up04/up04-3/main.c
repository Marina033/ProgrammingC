#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

unsigned long long
hash_function(unsigned long long);

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    off_t start_len = lseek(fd, 0, SEEK_END);
    if (start_len == -1) {
        return -1;
    }
    unsigned long long x;
    int count;
    sscanf(argv[3], "%d", &count);
    sscanf(argv[2], "%llx", &x);
    for (int i = 0; i < count; i++) {
        if (lseek(fd, start_len + (count - i - 1) * sizeof(x), 0) == -1) {
            return -1;
        }
        if (write(fd, &x, sizeof(x)) != sizeof(x)) {
            return -1;
        }
        x = hash_function(x);
    }
    return 0;
}
