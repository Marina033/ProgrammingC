#include <stdio.h>
#include <string.h>

const char pattern[] = "rwxrwxrwx";

int
main(int argc, char **argv)
{
    unsigned oct;
    const unsigned char LEN = sizeof(pattern) - 1;
    char str[LEN + 1];
    for (int i = 1; i < argc; i++) {
        strcpy(str, pattern);
        sscanf(argv[i], "%o", &oct);
        for (int j = LEN - 1; j >= 0; j--) {
            if (!(oct & 1)) {
                str[j] = '-';
            }
            oct >>= 1;
        }
        printf("%s\n", str);
    }
    return 0;
}
