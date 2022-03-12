#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum
{
    DIGITS = 10
};

int
main(void)
{
    char s[PATH_MAX];
    fgets(s, PATH_MAX, stdin);
    int i = strlen(s) - 1;
    while (s[i] == '\n' || s[i] == '\r') {
        s[i--] = '\0';
    }

    long long arr[DIGITS], x;
    for (int i = 0; i < DIGITS; i++) {
        arr[i] = 0;
    }

    FILE *f = fopen(s, "r");
    if (f) {
        int c = getc_unlocked(f);
        while (c != EOF) {
            if (c >= '0' && c <= '9') {
                x = c - '0';
                arr[x] += 1;
            }
            c = getc_unlocked(f);
        }
        fclose(f);
    }

    for (int i = 0; i < DIGITS; i++) {
        printf("%d %lld\n", i, arr[i]);
    }
    return 0;
}
