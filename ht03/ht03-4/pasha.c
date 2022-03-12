#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

enum
{
	MULT = 1103515245,
	INC = 12345,
	MOD = 0x80000000,
	MODD = 0x7fffffff,
	NUMBER_OF_LETTERS = 62,
	NUMBERS = 10,
	BIG_LETTERS = 26,
	MAX_LEN = 32
};

int
main(void)
{
    char letters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char template[MAX_LEN + 1] = {};
    int broken = 0;
    scanf("%32s", template);
    if (template[0] == '.') {
        printf("#\n");
        return 0;
    }


    return 0;
}
