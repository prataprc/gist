#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int compareint( int *a, int *b )
{
    return *a - *b;
}

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
      return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
                     ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

int main( void ) 
{
    int i,j;
    long a[1000000];
    uint64_t timeElapsed;
    struct timespec start, end;


    for(i=0,j=999999; i < 1000000 ; i++,j--) a[i] = j;

    clock_gettime(CLOCK_MONOTONIC, &start);
    qsort(a, 1000000, sizeof(int), compareint);
    clock_gettime(CLOCK_MONOTONIC, &end);
    timeElapsed = timespecDiff(&end, &start);

    printf("%d %d \n", a[0], a[9999]);
    printf("%ld \n", timeElapsed);
}

