#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

enum
{
	A = 1103515245,
	C = 12345,
	M = 1 << 31,
	DIGITS = 10,
	LETTERS = 26,
	ALL_SYMBOLS = 62,
	MAX_LEN = 32
};

char
transform(int index)
{
	int new_index = (int) ((double) index / M * ALL_SYMBOLS);
	char new_char;
	if (new_index >= 0 && new_index < DIGITS) {
		new_char = '0' + new_index;
	} else if (new_index < DIGITS + LETTERS) {
		new_char = 'A' + new_index - DIGITS;
	} else {
		new_char = 'a' + new_index - DIGITS - LETTERS;
	}
	return new_char;
}

long long
next_val(long long val)
{
	return (val * (long long) A + C) & ((long long) M - 1);
}

int
main(void)
{
    char s[MAX_LEN + 1];
	scanf("%s", s);
	
	int index;
	if (s[0] >= '0' && s[0] <= '9') {
		index = s[0] - '0';
	} else if (s[0] >= 'A' && s[0] <= 'Z') {
		index = DIGITS + s[0] - 'A';
	} else {
		index = DIGITS + LETTERS + s[0] - 'a';
	}
	
	long long low = (long long) ceil((double) index / ALL_SYMBOLS * M);
	long long high;
	if (index + 1 != ALL_SYMBOLS) {
		high = (int) ceil((double) (index + 1) / ALL_SYMBOLS * M);
	} else {
		high = (long long) M - 1;
	}
	
	int count = 0, hacked = 0;
	for (int i = low; i < high; i++) {
		low = next_val(i);
		int j = 1;
		while (s[j]) {
			if (s[j] != '.' && s[j] != transform(low)) break;
			low = next_val(i);
			j++;
		}
		if (!s[j]) {
			if (++count > 1) break;
			hacked = i;
		}
	}	
	
	if (count != 1) {
		printf("#\n");
	} else {
		int j = 0;
		while (s[j]) {
			char new_char = transform(hacked);
			hacked = low = next_val(hacked);
			putchar(new_char);
			j++;
		}
	}	
			
    return 0;
}
