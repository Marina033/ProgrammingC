#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv) 
{   
    char *out = argv[1];
    int mod;
    sscanf(argv[2], "%d", &mod);
    FILE *f = fopen("tmp.c", "w");
    fprintf(f, "#include <stdio.h>\n");
    fprintf(f, "int main(void)\n");
    fprintf(f, "{\nlong long x;\n");
    fprintf(f, "scanf(\"%%lld\", &x);\n");
    fprintf(f, "printf(\"%%lld\\n\", x * (x + 1) / 2 %% %d);\n", mod);
    fprintf(f, "return 0;\n}");
    fclose(f);
    
    f = fopen(out, "w");
    fprintf(f, "prog.exe");
    fclose(f);
    
    if (!fork()) {
        execlp("gcc", "gcc", "-o", "prog", "tmp.c", NULL);
        _exit(1);
    }
    
    return 0;
}