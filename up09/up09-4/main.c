#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    int file = creat("abp.py", 0777);
    
    int maxlen = 0;
    for (int i = 1; i < argc; i++) {
        maxlen += 1 + strlen(argv[i]);
    }
    maxlen += argc + 7;
    char *s = malloc(maxlen * sizeof(*s));
    s = strcat(s, "#! /usr/bin/env/python\nimport os\nprint(");
    s = strcat(s, argv[1]);
    for (int i = 2; i < argc; i++) {
        s = strcat(s, "*");
        s = strcat(s, argv[i]);
    }
    s = strcat(s, ")\nos.remove('abp.py')");
    
    write(file, s, strlen(s));
    close(file);
    execlp("python3", "python3", "abp.py", NULL);
    return 1;
}