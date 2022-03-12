#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void
print_keys(int fd, int index) 
{
    struct Node cur;
    if (lseek(fd, sizeof(cur) * index, SEEK_SET) == -1) {
        exit(1);
    }
    if (read(fd, &cur, sizeof(cur)) != sizeof(cur)) {
        exit(1);
    }
    
    if (cur.right_idx) {
        print_keys(fd, cur.right_idx);
    }
    printf("%"PRId32"\n", cur.key);
    if (cur.left_idx) {
        print_keys(fd, cur.left_idx);
    }
}

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    print_keys(fd, 0);
    return 0;
}