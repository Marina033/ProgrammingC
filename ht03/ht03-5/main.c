#include <stdio.h>

enum
{
    MOST_BIT = 128
};

int
main(void)
{
    int count = 0, max = 0;
    char buf[1000000];
    int k = 0;
    char c = getchar();
    while (c != EOF) {
        if ((c & MOST_BIT) == 0) {
            if (c > 32) {
                count++;
                buf[k++] = c;
            } else {
                if (count > max) {
                    max = count;
                }
                count = 0;
                k = 0;
            }
        } else {
            int i = 1;
            while (c & (1 << (7 - i))) {
                i++;
            }
            buf[k++] = c;
            for (int j = 1; j <= i - 1; j++) {
                buf[k++] = getchar();
            }
            count++;
        }
        c = getchar();
    }

    printf("%d\n", max);
    for (int i = 0; i < k; i++) {
        putchar(buf[i]);
    }
    printf("\n");
    return 0;
}
