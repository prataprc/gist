#include <sys/time.h>

int main(void)
{
    printf("Size of char    : %d \n", sizeof(char));
    printf("Size of int     : %d \n", sizeof(int));
    printf("Size of long    : %d \n", sizeof(long));
    printf("Size of short   : %d \n", sizeof(short));
    printf("Size of float   : %d \n", sizeof(float));
    printf("Size of double  : %d \n", sizeof(double));
    printf("Size of pointer : %d \n", sizeof(void *));
    printf("Size of time_t  : %d \n", sizeof(time_t));
    printf("Size of suseconds_t: %d \n", sizeof(suseconds_t));
}
