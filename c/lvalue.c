#include <stdio.h>

int main(void)
{
	int *a;
	int b[10] = { 10, 11, 12, 13, 14};

	*(a = (b+2)) = 22;
	printf("%d %d \n", b[2], *a);
}
