#include <stdio.h>

int main(void)
{
	const int *ptr;
	int b;
	int *const ptr1 = &b;
	const int a;

	ptr = &a;
	//*ptr = 10;
	//ptr1 = b;
	*ptr1 = 20;

	printf("%d %d \n", a, b);
}
