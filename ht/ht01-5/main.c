#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

char
*getline2(FILE *f);

enum
{
    SPACES_ONLY = 0x0bad1dea,
    OTHER_SYMBOLS = 0xbedabeda,
    RADIX = 10
};

int
main(void)
{
    int sum, flag, str_num = 1, order_num;
    char *s = getline2(stdin);
    while (s) {
        sum = 0;
        flag = 0;
        order_num = 1;
        char *pos = s;
        while (*pos) {
            if (isdigit(*pos) || ((*pos == '-' || *pos == '+') && isdigit(pos[1]))) {
                char *num_end;
                errno = 0;
                long x = strtol(pos, &num_end, RADIX);
                pos = num_end;
                if (errno == ERANGE || x > INT_MAX || x < INT_MIN) {
                    if (x > 0) {
                        x = order_num;
                    } else {
                        x = -order_num;
                    }
                }
                sum += (unsigned) x;
                order_num++;
            } else if (!isspace(*pos)) {
                flag = 1;
                break;
            }
            while (isspace(*pos)) {
                pos++;
            }
        }
  
        if (flag) {
            printf("%d\n", OTHER_SYMBOLS + str_num);
        } else if (order_num == 1) {
            printf("%d\n", SPACES_ONLY + str_num);
        } else {
                printf("%d\n", sum);
        }
        str_num++;
        free(s);
        s = getline2(stdin);
    }
    return 0;
}
