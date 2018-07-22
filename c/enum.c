#include <stdio.h>

enum week { A = 10, B = 20, C = 30 } ;

int main(void)
{
    enum week b = A;

	printf(" %d %d %d \n", A, B, C);
	printf("%d \n", b);
}
