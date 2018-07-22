#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 20;
	int c;

	c = (b++) + a;
	printf("%d %d %d \n", a, b, c);
}
