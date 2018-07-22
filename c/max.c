#include <stdio.h>

int main(void)
{
	int a =10, b = 20;
	int c;
	c = a++ > b++ ? a++ : b++;
	printf("a %d b %d c %d \n", a, b, c);
}
