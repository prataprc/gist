#include <stdio.h>
#include <signal.h>

void sig_int(void);

int main(void)
{
    void (*prev_int)(void);

    prev_int = signal(SIGINT, sig_int);
    while(1);
}

void sig_int(void)
{
    printf("signal int \n");
}
