int
bitcount(STYPE value)
{
    int count = 0;
    UTYPE uvalue = (UTYPE) value;
    while (uvalue) {
        count += uvalue & 1;
        uvalue >>= 1;
    }
    return count;
}
