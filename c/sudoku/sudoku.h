#ifndef __SUDOKU_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define ROWS 	9		/* Default rows of primary block */
#define COLUMNS	9		/* Default columns of primary block */

struct sudoku {
	unsigned int *iarr;	/* Initial array */
	unsigned int *marr; 
			/* (ROWS*COLUMNS) by (ROWS*COLUMNS) master array */
	unsigned int **warr;
			/* (ROWS * COLUMNS) arrays of (ROWS*COLUMNS) by 
			 * (ROWS*COLUMNS) worker array */
	unsigned int  prows;
	unsigned int  pcols;
	int ref_count;
	FILE *fptr;
};

/* The following are the global instances */
extern void sudoku_engine(struct sudoku *sdk, unsigned int value, 
				unsigned int ar, unsigned int ac);
extern struct sudoku * init_arrays(unsigned int *iarr, unsigned int prows, 
				unsigned int pcols);
extern void free_arrays(struct sudoku *sdk);
#endif /*__SUDOKU_H__*/ 
