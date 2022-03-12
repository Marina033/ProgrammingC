void
normalize_path(char *buf)
{
    char *runner = buf;
    char *norm = buf;
    while (*runner) {
        if (*runner == '/') {
            *norm = '/';
            norm++;
            while (*runner == '/') {
                runner++;
            }
        } else {
            *norm = *runner;
            norm++;
            runner++;
        }
    }
    *norm = '\0';
}