#include <stdio.h>

int main (void)
{
    double x, y;
    scanf("%lf%lf", &x, &y);
    int ans = x >= 1 && x <= 7 && y >= 2 && y <= 5 && y + x <= 10;
    printf("%d\n", ans);
}
