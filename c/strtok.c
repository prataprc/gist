#include <string.h>

int     main(void)
{
    char str[] = ";;;;";
    char *s;

    printf("string %s addr %x len %d \n", str, str, strlen(str));
    s = strtok(str, ";");
    printf("; token %x %s \n",s, s);
    s = strtok(NULL, ":");
    printf(": token  %x  %s\n",s, s);
    s = strtok(s, ";");
    printf("; token  %x  %s\n",s, s);
    s = strtok(s, ",");
    printf(", token  %x  %s\n",s, s);
    s = strtok(NULL, ",");
    printf(", token  %x  %s\n",s, s);
}

