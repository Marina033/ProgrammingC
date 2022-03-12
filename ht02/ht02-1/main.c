#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    long long pos = 0, neg = 0;
    for (int i = 1; i < argc; i++) {
        long long x = atoll(argv[i]);
        if (x > 0) {
            pos += x;
        } else {
            neg += x;
        }
    }
    printf("%lld\n%lld\n", pos, neg);
    return 0;
}
