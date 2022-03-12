#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int n;
    scanf("%d", &n);
    int values[100], probs[100];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &values[i], &probs[i]);
    }

    int m, seed;
    scanf("%d", &m);
    scanf("%d", &seed);
    srand(seed);

    for (int i = 0; i < m; i++) {
        double rand01 = (double) (rand() / (RAND_MAX + 1.0));
        int x = (int) (rand01 * 100);
        int j = 0;
        while (x > 0) {
            x -= probs[j];
            j++;
        }
        if (x == 0) {
            j++;
        }
        printf("%d\n", values[j - 1]);
    }
    return 0;
}
