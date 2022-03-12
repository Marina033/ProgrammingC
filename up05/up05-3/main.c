#include <stdio.h>
#include <time.h>
#include <stdlib.h>

FILE *f;

enum
{
    START_YEAR = 1900,
    MAX_SIZE = 1001
};

int
scan (time_t *time)
{
    char *date = malloc(MAX_SIZE * sizeof(*date));
    if (!fgets(date, MAX_SIZE, f)) {
        return 0;
    }
    struct tm my_struct;
    int year, mon, mday, hour, min, sec;
    sscanf(date, "%d/%d/%d %d:%d:%d", &year, &mon, &mday, &hour, &min, &sec);
    my_struct.tm_year = year - START_YEAR;
    my_struct.tm_mon = mon - 1;
    my_struct.tm_mday = mday;
    my_struct.tm_hour = hour;
    my_struct.tm_min = min;
    my_struct.tm_sec = sec;
    my_struct.tm_isdst = -1;
    *time = mktime(&my_struct);
    free(date);
    return 1;
}

int
main(int argc, char **argv)
{
    f = fopen(argv[1], "r");
    time_t time, time_prev;
    int flag = 0;
    while (scan(&time)) {
        if (!flag) {
            time_prev = time;
            flag = 1;
            continue;
        }
        printf("%ld\n", time - time_prev);
        time_prev = time;
    }
    fclose(f);
    return 0;
}
