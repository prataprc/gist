#include "sudoku.h"

/* How to use this program ? */
void usage(void)
{
	printf("solve [row] [column] \n");
	printf("\t the rows and columns are optional, ");
	printf("\t the default will be taken as 3 X 3 \n");
	return;
}

int main(int argc, char **argv)
{
	int opt;
	int primary_rows = ROWS;
	int primary_columns = COLUMNS;
	int i, j, x;
	unsigned int *iarr;
	struct sudoku *sdk;

	/* Parse the command line options */
	do { opt = getopt(argc, argv, "h");
		switch (opt) {
			case 'h' :		/* Help ! */
				usage();
				break;
		}
	} while (opt != -1);
	
	if (argc == 3) {
		primary_rows 	= atoi((const char *)argv[1]);
		primary_columns = atoi((const char *)argv[2]);
	} 

	/* FIX ME : Check the values of primary_rows and primary_columns */

	/* Creat the init array */
	x = primary_rows * primary_columns;
	iarr = (unsigned int *) malloc(sizeof(unsigned int ) * x * x);
	for(i = 0; i < x; i++) {
		for(j = 0; j < x; j++) {
			int temp;
			scanf("%d",&temp);
			*(iarr + (i*x) + j) = (unsigned int) temp;
		}
	}
	for(i = 0; i < x; i++) {
		for(j = 0; j < x; j++) {
			printf("%d ", *(iarr + (i*x) + j));
		}
		printf("\n");
	}
	sdk = init_arrays(iarr, primary_rows, primary_columns);

	if (sdk == NULL) {
		printf("init array failed ... \n");
		return 1;
	}
	sudoku_engine(sdk, 1, 0, 0);
	free_arrays(sdk);
	free(iarr);
	return 0;
}
