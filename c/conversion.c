#include <stdio.h>

int main(void)
{
	int a;
	float b = 10.2;
	char ch = 'A';

	a =  b;
	printf("%d \n", a);
	printf("%c %d \n", ch, ch);
	
	printf("%d \n", a < 0 ? b++ : a);
	printf("%f %d \n", b, a);
}
