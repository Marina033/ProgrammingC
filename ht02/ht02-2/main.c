#include <stdio.h>
#include <math.h>

#define PERCENT 0.01

enum
{
    DEC = 10, //работаем с десятичными числами
    ACCURACY = 4 //до какого знака после запятой округляем
};

int
main(int argc, char **argv)
{
    double price;
    sscanf(argv[1], "%lf", &price);
    for (int i = 2; i < argc; i++) {
        double num;
        sscanf(argv[i], "%lf", &num);
        price *= 1.0 + num * PERCENT;
        int mult = pow(DEC, ACCURACY);
        price = round(price * mult) / mult;
    }
    printf("%.4lf\n", price);
    return 0;
}
