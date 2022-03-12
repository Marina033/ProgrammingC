#include <limits.h>

STYPE
bit_reverse(STYPE value)
{
    UTYPE uvalue = (UTYPE) value;
    UTYPE mask = 1;
    UTYPE ures = 0;
    for (int i = 1; i < sizeof(UTYPE) * CHAR_BIT; i++) {
        if (mask & uvalue) {
            ures++;
        }
        ures <<= 1;
        mask <<= 1;
    }
    if (mask & uvalue) {
        ures++;
    }
    STYPE res = (STYPE) ures;
    return res;
}