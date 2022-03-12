#include <stdio.h>
int main(void)
{
long long x;
scanf("%lld", &x);
printf("%lld\n", x * (x + 1) / 2 % 10);
return 0;
}