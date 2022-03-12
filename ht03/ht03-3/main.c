#include <stdio.h>
#include <stdlib.h>

enum { A = 1103515245, C = 12345 };

typedef struct RandomGenerator RandomGenerator;
typedef struct RandomOperations
{
    int (*next)(RandomGenerator *);
    void (*destroy)(RandomGenerator *);
} RandomOperations;

typedef struct RandomGenerator
{
    RandomOperations *ops;
    int cur_value;
} RandomGenerator;

void
destroy (RandomGenerator *r)
{
    free(r);
}

int
next(RandomGenerator *r)
{
    long long mod = 1;
    mod <<= 31;
    long long x = ((long long) A * r->cur_value + C) % mod;
    r->cur_value = x;
    return x;
}

RandomOperations ops_c = {next, destroy};

RandomGenerator *
random_create(int seed)
{
    RandomGenerator *r = calloc(1, sizeof(*r));
    if (r == NULL) {
        return NULL;
    }
    r->cur_value = seed;
    r->ops = &ops_c;
    return r;
}
