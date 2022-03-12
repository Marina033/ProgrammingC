#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    const char pattern[] = {'r', 'w', 'x', 'r', 'w', 'x', 'r', 'w', 'x'};
    const int pattern_len = sizeof(pattern) / sizeof(pattern[0]);
    int len = strlen(str);
    if (len != pattern_len) {
        return -1;
    }
    int res = 0;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c != '-' && c != 'r' && c != 'w' && c != 'x') {
            return -1;
        }
        if (c != '-' && c != pattern[i]) {
            return -1;
        }
        if (c != '-') {
            res |= 1 << (pattern_len - i - 1);
        }
    }
    return res;
}
