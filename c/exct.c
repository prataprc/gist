/* Exract a given data from the Binary from a START offset to END offset
 *	USAGE :	exct src_fname dest_fname st_offset end_offset
 */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
  	FILE *src_fptr;
	FILE *dest_fptr;
	int	 start;
	char *buffer;
	int	 size;
	int	 read;

	if (argc < 5) {
   		fprintf(stderr, "USAGE : exct src_fname dest_fname st_offset size \n");
		exit(1);
	}

	src_fptr = fopen(argv[1], "rb");
	if (src_fptr == NULL) {
   		fprintf(stderr, "Failed to open file %s \n", argv[1]);
		exit(1);
	}


	dest_fptr = fopen(argv[2], "ab");
	if (dest_fptr == NULL) {
   		fprintf(stderr, "Failed to open file %s \n", argv[2]);
		exit(1);
	}

/*	dest_fptr = stdout; */

	start = atoi(argv[3]);
	size	= atoi(argv[4]);
	if (size <= 0) {
   		fprintf(stderr, "Enter a valid START and END offset \n");
		exit(1);
	}
	fprintf(stderr, "Extracting data from offset %d to offset %d .... \n", start, start + size);
	if (fseek(src_fptr, start, SEEK_SET) != 0) {
		fprintf(stderr, "Unable to seek in the file %s to %d \n", argv[1], start);
		exit(1);
	}

	/* Allocate buffer for data */
	buffer = (char *)malloc(size);
	read = fread(buffer, 1, size, src_fptr);
	if (read != size) {
   		fprintf(stderr, "Only %d bytes where read, instead of %d \n", read, size);
		exit(1);
	}

    fwrite(buffer, 1, read, dest_fptr);

}
