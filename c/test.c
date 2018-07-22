#include <stdio.h>

int main(void)
{
    FILE * fp;
    char str[100];
    char a = 10.2;

    fp = fopen("a", "w");
    if (fp == NULL) {
        printf("fp NULL \n");
    }
    scanf("%s", str);
    write(str, 1, strlen(str), fp);
    printf("Echo %s \n", str); 
}

