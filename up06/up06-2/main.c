#include <stdio.h>
#include <time.h>

enum 
{
    START_YEAR = 1925,
    START_MON = 10,
    START_DAY = 7,
    BASE_YEAR = 1900,
    SEC_DAY = 60 * 60 * 24,
    DAY_MON = 30,
    DAY_YEAR = 360
};

int
main(void)
{
    struct tm tm_begin = {};
    tm_begin.tm_mday = START_DAY;
    tm_begin.tm_mon = START_MON - 1;
    tm_begin.tm_year = START_YEAR - BASE_YEAR;
    long long begin = (long long) mktime(&tm_begin);
    
    int year, mon, day;
    while (scanf("%d%d%d", &year, &mon, &day) == 3) {
        struct tm tm_curr = {};
        tm_curr.tm_mday = day;
        tm_curr.tm_mon = mon - 1;
        tm_curr.tm_year = year - BASE_YEAR;
        long long curr = (long long) mktime(&tm_curr);
        long long diff = curr - begin + (SEC_DAY >> 1);

        diff /= SEC_DAY;
        int year1, mon1, day1;
        year1 = 1 + diff / DAY_YEAR;
        diff %= DAY_YEAR;
        mon1 = 1 + diff / DAY_MON;
        diff %= DAY_MON;
        day1 = 1 + diff;

        printf("%d %d %d\n", year1, mon1, day1);
    }
    return 0;
}