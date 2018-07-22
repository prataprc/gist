#include "sudoku.h"

/* Portability :
 *	- The maximum allowed size of primary block is 16  by 16
 *
 */

static int  no_of_inst = 0;

static int  get_free_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac, int iter,
			unsigned int *r, unsigned int *c);
static int  clear_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac, unsigned int r, 
			unsigned int c);
static int  update_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac, unsigned int r, 
			unsigned int c);
static void zeroise_arr(unsigned int *arr, unsigned int r, unsigned int c);
static void fprint_arr(FILE *fptr, unsigned int *arr, unsigned int x);
static int verify(unsigned int *arr, unsigned int x);
static int validate(unsigned int *arr, unsigned int x);

/* Creat an instance of the sudoku engine
 * Usage:
 *	prows and pcols indicate the number of rows and columns of the primary
 *	block. Optionally an array 'iarr' of size (prows*pcols) by 
 *	(prows*pcols) can be supplied to initialise the master array. This 
 *	option can be used to solve an already created sudoku puzzle. On 
 *	leaving the iarr NULL the sudoku engine will run, throwing out all 
 *	possible sudoku combinations.
 */
struct sudoku *init_arrays(unsigned int *iarr, unsigned int prows, 
			unsigned int pcols)
{
	unsigned int i, j, x;
	struct sudoku *sdk = NULL;
	char fname[32];
	unsigned int *marr, **warr;

	/* Note that the final array is always X * X square array */
	x = (prows * pcols);
	if (x > 65535) {
        printf("Exceeded limit \n");
		goto ret_null;
	}

	sdk = (struct sudoku *) malloc(sizeof(struct sudoku));
	sdk->marr = NULL;
	sdk->warr = NULL;
	sdk->fptr = NULL;
	sdk->iarr = NULL;
	sdk->prows = prows; 
	sdk->pcols = pcols;
	sdk->ref_count = 0;

	marr = (unsigned int *) malloc(sizeof(int) * (x * x));
	if (marr == NULL) {
		printf("Error allocating the Master array \n");
		goto ret_null;
	}
	zeroise_arr(marr, x, x);
	sdk->marr = marr;

	warr = (unsigned int **) malloc(sizeof(int**) * x);
	if (warr == NULL) {
		printf("Error allocating the Worker array arrays \n");
		goto ret_null;
	}
	sdk->warr = warr;
	for (i = 0; i < x; i++) {
		*(warr + i) = (unsigned int *) 
					malloc(sizeof(int) * (x * x));
		if (*(warr + i) == NULL) {
			printf("Error allocating the Worker array\n");
			goto ret_null;
		}
		zeroise_arr(*(warr + i), x, x);
	}

	if (iarr != NULL) {	/* copy the iarr */
		for (i = 0; i < x; i++) {
			for (j = 0; j < x; j++) {
				if (*(iarr + (i*x) + j) != 0) {
					unsigned int  ar, ac, r, c, val;
					val = *(iarr + (i*x) + j);
					ar = i / prows;
					ac = j / pcols;
					r = i % prows;
					c = j % pcols;
					update_slot(sdk, val, ar, ac, r, c);
				}
			}
		}
		sdk->iarr = iarr;
	}

	no_of_inst++;
	sdk->ref_count = no_of_inst;
	sprintf(fname,"sudoku_%d", sdk->ref_count);
	sdk->fptr = fopen(fname, "w");
	return sdk;

ret_null:
	free_arrays(sdk);
	return NULL;
}

void free_arrays(struct sudoku *sdk)
{
	if (!sdk) {
		goto ret;
	}
	if (sdk->marr) {	
		free(sdk->marr);
	} 
	if (sdk->warr) {
		int i, x;

		x = sdk->prows * sdk->pcols;
		for(i = 0; i < x; i++) {
			if (*(sdk->warr + i)) {
				free(*(sdk->warr + i));
			}
		}
		free(sdk->warr);
	}	
	if (sdk->fptr) {
		fclose(sdk->fptr);
	}
	free(sdk);
	no_of_inst--;
ret:
	return;
}

/* This function zeroise the x by x  array  */
static void zeroise_arr(unsigned int *arr, unsigned int r, unsigned int c)
{
	int i, s;

	s = r * c;
	for (i = 0; i < s; i++ ) {
		*(arr + i) = 0;
	}
	return;
}

/* This function is called to get a free slot in the desired ar,ac block, for 
 * the desired value.  First the master arrary 'marr' is checked for an
 * available slot. If available, 'warr' of the corresponsing 'value' is checked
 * for availability. 'iter' helps the functions to return the 'iter'th 
 * available free slot.
 */
static int  get_free_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac, 
			int iter, unsigned int *r, unsigned int *c)
{
	unsigned int *varr = *(sdk->warr + value-1);
	unsigned int prows = sdk->prows;
	unsigned int pcols = sdk->pcols;
	int roff = ar * prows;		/* Row offset */
	int coff = ac * pcols;		/* Column offset */
	int x = prows * pcols;
	unsigned int i, j, mval, ival;
	int rc = -1;

	for (i = 0; i < prows; i++) {
		for (j = 0; j < pcols; j++) {
			/* if value is already anchored in the initial array
 			 * achor the value in the same slot for master array
			 */
			if (sdk->iarr) {
				ival = *(sdk->iarr + ((roff + i) * x) + (coff + j));
				//printf("ival %d \n", ival);
				if (ival == value) {
					*r = i;
					*c = j;
					return 0;
				}
			}
			mval = *(sdk->marr + ((roff + i) * x) + (coff + j));
			if (mval != 0) {
				continue;
			}
			if (*(varr + ((roff + i) * x) + (coff + j)) == 0) {
				//printf("warr %d %d \n", i, j);
				if (iter) {
					iter--;
					continue;
				}
				*r = i; *c = j;
				iter--;
				rc = 0;
			}
		}
	}
	return rc;
}

/* first the master 'marr' is marked occupied with 'value', then in the
 * corresponding 'value'th 'warr' the entire row and colum are marked
 * occupied.
 */
static int update_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac, unsigned int r, 
			unsigned int c)
{
	unsigned int *varr = *(sdk->warr + (value-1));
	unsigned int *iarr = sdk->iarr;
	int roff = ar  * sdk->prows + r;	/* Row offset */
	int coff = ac * sdk->pcols + c;		/* Column offset */
	int x = sdk->prows * sdk->pcols;
	int i;
		
	if (iarr && (*(iarr + (roff * x) + coff) == value)) {
		*(sdk->marr + (roff * x) + coff) = value;
		goto anchor_slot;
	}
	*(sdk->marr + (roff * x) + coff) = value;
	for (i = 0; i < x; i++) {
		*(varr + (roff * x) + i) += value;
		*(varr + (i * x) + coff) += value;
	}
	return 0;
anchor_slot:
	return 1;
}

/* This is the inverse of update_slot */
static int clear_slot(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac,
			unsigned int r, unsigned int c)
{
	unsigned int *varr = *(sdk->warr + (value-1));
	unsigned int *iarr = sdk->iarr;
	int roff = ar * sdk->prows + r;	/* Row offset */
	int coff = ac * sdk->pcols + c;	/* Column offset */
	int x = sdk->prows * sdk->pcols;
	int i;
		
	if (iarr && (*(iarr + (roff * x) + coff ) == value)) {
		goto anchor_slot;
	}
	*(sdk->marr + (roff * x) + coff ) = 0;
	for (i = 0; i < x; i++) {
		*(varr + (roff * x) + i) -= value;
		*(varr + (i * x) + coff) -= value;
	}
	return 0;
anchor_slot:
	return 1;
}

void sudoku_engine(struct sudoku *sdk, unsigned int value, 
			unsigned int ar, unsigned int ac)
{
	unsigned int r = 0, c = 0;
	int rc;
	int x = sdk->prows * sdk->pcols;
	int iter = 0;
	unsigned int cur_ar, cur_ac, cur_val;
	static int count = 0;
	static int iter_count = 0;

	count++;
#ifdef _DEBUG_
	fprint_arr(sdk->fptr, sdk->marr, x);
	printf("count %d \n", count);
#endif /* _DEBUG_ */
	//printf("iter_count %d \n", iter_count);
	while (1) {
		rc = get_free_slot(sdk, value, ar, ac, iter, &r, &c);	
#ifdef _DEBUG_
		printf("rc %d %d %d %d %d %d \n", rc, value, ar, ac, r, c);
#endif /* _DEBUG_ */
		if (rc != 0) {
			break;
		}
		update_slot(sdk, value, ar, ac, r, c);
		iter++;
        iter_count++;
		cur_ar = ar; cur_ac = ac; cur_val=value;

		ac++;
		if (ac >= sdk->prows) {
			ac = 0;
			ar++;
		}
		if (ar >= sdk->pcols) {
			ar = 0;
			value++;
		}
		if (value <= x) {
			sudoku_engine(sdk, value, ar, ac);
		} else {
			/* Su-doku success  */
            if (!validate(sdk->marr, x)) {
			    fprint_arr(sdk->fptr, sdk->marr, x);
                getchar();
            }
		}
		ar = cur_ar; ac = cur_ac ; value = cur_val;
		if (clear_slot(sdk, value, ar, ac, r, c)) {
			/* It is an anchor slot */
			break;
		}
	}
	count--;
	return;
}
/* Function to print the x by x master array, which is actively populated
 * by the sudoku engine
 */
static void fprint_arr(FILE *fptr, unsigned int *arr, unsigned int x)
{
	int i, j;

        printf("fprintf \n");
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++) {
                        fprintf(fptr, "%c ", *(arr + (i * x) + j));
                        printf("%3d ", *(arr + (i * x) + j));
                }
                fprintf(fptr, "\n");
                printf("\n");
        }
	fprintf(fptr, ";");
    printf("verifying ... \n");
    verify(arr, x);
    return;
}

static int verify(unsigned int *arr, unsigned int x)
{
	int i, j, k;
    unsigned int ch;
    unsigned int *ch_count;
    int rc = -1;

    ch_count = (unsigned int *)malloc(sizeof(int) * x);
    for (i = 0; i < x; i++) {
        ch_count[i] = 0;
    }
    for (i = 0; i < x; i++) {
        for (j = 0; j < x; j++) {
            unsigned int count;

            ch = *(arr + (i * x) + j); 
            count = 0;
            for (k = 0; k < x; k++) {
                if (*(arr + (i * x) + k) == ch) {
                    count++;
                    ch_count[ch-1]++;
                }
            }
            if (count != 1) {
                printf("Error ... \n");
                goto ret;
            }
            count = 0;
            for (k = 0; k < x; k++) {
                if (*(arr + (k * x) + j) == ch) {
                    count++;
                    ch_count[ch-1]++;
                }
            }
            if (count != 1) {
                printf("Error1 ... %d \n", count);
                goto ret;
            }
        }
    }
    for (i = 0; i < x; i++) {
        if (ch_count[i] != x*2) {
                printf("Error2 ... %d %d \n", i, ch_count[i] );
                goto ret;
        } 
    }
    rc = 0;
ret:
    free(ch_count);
    return rc;
}

static int validate(unsigned int *arr, unsigned int x)
{
    unsigned int diag_sum = 0;
    unsigned int i, j;
    
    i = j =0;

    if (x != 9) {
        return 0;
    }

    j = 0;
    for (i = 0; i < x; i++) { 
        diag_sum += *(arr + (i * x) + j++);
    }
    if (diag_sum!= 45) {
        return 1;
    }
    j = 8;
    for (i = 0; i < x; i++) { 
        diag_sum += *(arr + (i * x) + j--);
    }
    if (diag_sum != 45) {
        return 1;
    }
    return 0;
}
