/* The purpose of the program is to convert the input file, which is in the
 * HEX format to binary format.
 */

#include <stdio.h>

int	main(int argc, char ** argv)
{
  	FILE *hex_fptr;
	FILE *bin_fptr;
	unsigned char line[20];
	unsigned char bin_char[3];
	int	 total_lines = 0;

	if (argc < 3) {
   		printf("USAGE : b2h source destination \n");
		exit(1);
	}
	bin_fptr = fopen(argv[1], "rb");
	if (bin_fptr == NULL) {
   		printf("Unable to open %s \n", argv[1]);
		exit(1);
	}

	hex_fptr = fopen(argv[2], "wb");
	if (hex_fptr == NULL) {
   		printf("Unable to open %s \n", argv[2]);
		exit(1);
	}

	while(!feof(bin_fptr)) {
   		bin_char[0] = bin_char[1] = bin_char[2] = 0;
   		if (!(fread(bin_char, 1, 3, bin_fptr))) {
       		break;
		}
		sprintf(line,"'H%02X%02X%02X\r\n", bin_char[2], bin_char[1], bin_char[0]);
		fwrite(line, 1, strlen(line), hex_fptr);
		total_lines++;
	}
	printf("The total number of lines written in %s is %d \n", argv[2],
															total_lines);
}

