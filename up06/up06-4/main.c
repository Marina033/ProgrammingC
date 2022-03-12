#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv)
{
    long long sum = 0;
    DIR *my_dir = opendir(argv[1]);
    if (!my_dir) {
        return 1;
    }
    struct dirent *elem;
    struct stat buf;
    
    while ((elem = readdir(my_dir))) {
        char c = elem->d_name[0];
        if (!(c >= 'A' && c <= 'Z')) {
            continue;
        }
        char new_path[PATH_MAX + 1];
        snprintf(new_path, PATH_MAX, "%s/%s", argv[1], elem->d_name);
        if (stat(new_path, &buf) != 0) {
            continue;
        }
        if (S_ISREG(buf.st_mode) && buf.st_uid == getuid()) {
            sum += buf.st_size;
        }
    }
    closedir(my_dir);
    printf("%lld\n", sum);
    return 0;
}
