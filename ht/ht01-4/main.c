#include <stdio.h>
#include <stdlib.h>

enum { MULT = 2 };

char
*getline2(FILE *f)
{
    char *s = malloc(sizeof(*s)), *rsrv;
    int c;
    if (!s) {
        return NULL;
    }
    int capacity = 1, len = 0;
    c = fgetc(f);
    while (c != EOF) {
        if (len + 1 == capacity) {
            capacity *= MULT;
            rsrv = realloc(s, capacity * sizeof(*s));
            if (!rsrv) {
                free(s);
                return NULL;
            }
            s = rsrv;
        }
        s[len++] = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(f);
    }
    if (!len) {
        free(s);
        return NULL;
    }
    s[len++] = '\0';
    s = realloc(s, len * sizeof(c));
    if (!s) {
        free(s);
        return NULL;
    }
    return s;
}
