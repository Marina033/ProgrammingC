#include <stdio.h>
#include <stdlib.h>

enum { MAX_FRAC_LENGTH = 24 };

int
is_uint_fit(unsigned int x)
{
    unsigned int biased = x >> MAX_FRAC_LENGTH;
    if (!biased) {
        return 1;
    }
    int num_of_bits = 0;
    while (biased) {
        biased >>= 1;
        num_of_bits++;
    }
    int mask = 1 << num_of_bits;
    mask--;
    return !(x & mask);
}

int
main(void)
{
    unsigned int x;
    while (scanf("%u", &x) == 1) {
        printf("%d\n", is_uint_fit(x));
    }
    return 0;
}
