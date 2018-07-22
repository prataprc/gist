#define reg(base, a) ({unsigned int *ptr; ptr = base + a; *ptr;})

int main(void)
{
	unsigned int b[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	int i;
	
	for (i = 0; i < 10; i++) {
		printf("%d \n", reg(b, i));
		
	}

	for (i = 0; i < 10; i++) {
		{unsigned int *ptr = b + i; *ptr} = i;
	}

	for (i = 0; i < 10; i++) {
		printf("%d \n", reg(b, i));
	}
}

