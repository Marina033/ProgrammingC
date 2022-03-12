#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

int
main(int argc, char **argv)
{
    struct stat my_stat;
    uint64_t sum = 0;
    for (int i = 1; i < argc; i++) {
        if (lstat(argv[i], &my_stat) == 0 && S_ISREG(my_stat.st_mode) && my_stat.st_nlink == 1) {
            sum += my_stat.st_size;
        }
    }
    printf("%"PRId64"\n", sum);
    return 0;
}
