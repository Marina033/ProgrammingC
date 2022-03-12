#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

enum
{
    HOURS_DAY = 24,
    MINS_HOUR = 60,
    SECS_MIN = 60,
    FIRST_YEAR = 1900,
    SUNDAY = 7
};

int
main(int argc, char **argv)
{
    int year, yday;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &yday);
    time_t ysec = yday * HOURS_DAY * MINS_HOUR * SECS_MIN;
    struct tm start = {};
    start.tm_year = year - FIRST_YEAR;

    ysec += mktime(&start);
    struct tm *ptrtime = localtime(&ysec);
    printf("%lu ", (unsigned long) ptrtime->tm_year + FIRST_YEAR);
    printf("%lu ", (unsigned long) ptrtime->tm_mon + 1);
    printf("%lu ", (unsigned long) ptrtime->tm_mday);
    int wday = ptrtime->tm_wday;
    if (wday == 0) {
        wday = SUNDAY;
    }
    printf("%d\n", wday);
    return 0;
}
