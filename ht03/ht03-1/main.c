#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    if (argc < 5) {
        return -1;
    }
    int count, low, high;
    unsigned seed;
    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &low);
    sscanf(argv[3], "%d", &high);
    sscanf(argv[4], "%u", &seed);

    srand(seed);
    for (int i = 0; i < count; i++) {
        double rand01 = (double) (rand() / (RAND_MAX + 1.0));
        int res = low + (int) ((high - low) * rand01);
        printf("%d\n", res);
    }
    return 0;
}
