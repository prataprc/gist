int a ;
int *b = &a;

#define MAX(a,b) a > b ? a : b

int main(void)
{
	int a = 10;
	int b = 20;
	int c;

	c = MAX(a++,b++);	
	printf(" %d %d %d \n", a, b, c);	
}

