#include <stdio.h>

int	main(void)
{
	int a[10][10];
	int *aap[10];
	int **ap = (int **)a;
	int i, j;

	/* Initialise the original array */
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10 ; j++ ) {
			a[i][j] = j + (i * 10);
		}
	}	

	/* Initialise the pointer array */
	for (i = 0; i < 10; i++) {
		aap[i] = (int *)&a[i];
	}
	
	/* print the original array */
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10 ; j++ ) {
			printf("%d ", ++aap[i][j]);
		}
		printf("\n");
	}	

	return 0;
}
