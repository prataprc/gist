#include <stdio.h>

int main(void)
{
	int a, b = 10, c = 20, d = 30;
	
	a = b, c, d;
	printf("%d \n", a);
	c = (d = c, d);
	printf("%d %d \n", c, d);
}
