#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int
main(void)
{
    int n, w;
    scanf("%o%o", &n, &w);
    int32_t num_lines = 1 << n;
    int32_t mask = ~(1 << (n - 1));
    for (int32_t i = 0; i < ~mask; i++) {
        printf("|%*"PRIo32, w, i);
        printf("|%*"PRId32, w, i);
        printf("|%*"PRId32, w, i & mask);
        printf("|\n");
    }
    for (int32_t i = ~mask; i < num_lines; i++) {
        printf("|%*"PRIo32, w, i);
        printf("|%*"PRId32, w, i);
        printf("|%*"PRId32, w, -(i & mask));
        printf("|\n");
    }
    return 0;
}
