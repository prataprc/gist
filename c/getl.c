#include <stdio.h>

void main(int argc, char *argv[])
{
    FILE *fptr;
    char dest[1000];

    if (argv[1] == NULL) {
        printf("No input file ... \n");
        exit(1);
    }

    fptr = fopen(argv[1], "r");
    if (!fptr) {
        printf("unable to open %s ... \n");
        exit(1);
    }

    while(!getline(dest, fptr)) {
        printf("%s\n", dest);
    }
}

int getline(char *dest, FILE *fptr)
{
    int count = 0;
    unsigned char temp;

    fread(&temp, 1, 1, fptr);
    printf(".%c", temp);
    if ((temp == '\n') || (temp == '\r')) {
        return count;
    } else {
        dest[count++] = temp;
    }
    return count;
}
