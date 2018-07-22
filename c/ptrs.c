#include <stdio.h>

char (*(*x())[])(void);
char func(void);
char func1(void);
char func2(void);

char str[] = "Hello World";

int main(void)
{
	char a[] = { 10, 20, 30, 40, 50 };
	char *ptr;
	char *ptr1 = a;
	char *str1 = "Good Bye";	
	void (*f)(void);
	char (*ff)(void);
    int  bkp = 0x12345678;
    int sum = 0x1234;

	//(ptr=ptr1)++;
	//printf("%d %d\n", *ptr, *ptr1);

	str[0] = 'A';
	//str1[0] = 'A';
	f = x();
	ff = *f;
	printf("%x %d \n", func, (*ff)());
    printf("%s \n", str);
    printf("%x \n", bkp);
    sum -= ((char*)&bkp)[3];
    ((char*)&bkp)[3] = 0;
    printf("%x sum %x\n", bkp, sum);
	
}
char (*(*x())[])(void)
{
	static char (*fun[3])(void);
	fun[0] = func;
	fun[1] = func1;
	fun[2] = func2;
	
	return func; 
}

char func(void)
{
	return 10;
}

char func1(void)
{
	return 20;
}
char func2(void)
{
	return 30;
}
