/* The purpose of the program is to convert the input file, which is in the
 * HEX format to binary format.
 *
 */

#include <stdio.h>

struct statistics {
  	int		total_lines;
	int		inv_lines;
	int		inv_chars;
	int		dest_size;
} stat;

int				get_line(FILE *, char *);
unsigned char   convert_hex_to_bin(unsigned char *);

int	main(int argc, char **argv)
{
  	FILE	*hex_fptr;
	FILE	*bin_fptr;
	int		line_len;
	unsigned char	line[20];
	unsigned char 	temp;

	int		bytes_written = 0;

	if (argc < 3) {
   		printf("Usage : h2b source destindation \n");
		exit(1);
	}

	/* Open the Source file (HEX) argv[1] */
	hex_fptr = fopen(argv[1], "rb");
	if (hex_fptr == NULL) {
   		printf("Unable to open the SOURCE file \n");
		exit(1);
	}

	/* Open the Destination file (BIN) argv[1] */
	bin_fptr = fopen(argv[2], "wb");
	if (bin_fptr == NULL) {
   		printf("Unable to open the destination file \n");
		exit(1);
	}

	while(1) {	/* The End of file will be detected in "get_line" function */
		int	i;

		line_len = get_line(hex_fptr, line);
		line[line_len] = 0;
		if (line_len == 0) {	/* End of file detected but no new line */
            break;
		}
		stat.total_lines++;
		if (line_len > 8) {
			printf("Invalid line length at %d \n", stat.total_lines);
			stat.inv_lines++;
    		continue;
        }
        if (line[0] != 0x27 ) {
			printf("Invalid line at %d \n", stat.total_lines);
			stat.inv_lines++;
          	continue;
		}
        if (line[1] != 'h' && line[1] != 'H') {
			printf("Invalid line (Not a Hexa) %d \n", stat.total_lines);
			stat.inv_lines++;
          	continue;
        }

		for (i = 6; i >= 2; i-=2) {
   			stat.dest_size++;
    		temp = convert_hex_to_bin(&line[i]);
			fwrite(&temp, 1, 1, bin_fptr);
		}
	}
	/* Print the statistics
	printf("The Total number of lines encountered 	: %d \n", stat.total_lines);
	printf("Number of invalid lines encountered     : %d \n", stat.inv_lines);
	printf("Number of invalid chars encountered     : %d \n", stat.inv_chars);
	printf("Bytes written into %s is                : %d \n", argv[2],
													stat.dest_size);
*/
}

/* This function excrats a VALID line from the file and returns them.
 * 	The return value is "length of the line"
 */
int	get_line(FILE *hex_fptr, char *line)
{
	int		count = 0;
	int		detected_nline = 0;

	while(!(feof(hex_fptr))) {
   		fread(&line[count], 1, 1, hex_fptr);
		if (line[count] == 0xa || line[count] == 0xd) {
   			line[count] = 0;
			if (detected_nline == 0) {
     			continue;
			}
			return count;
		}
		if (line[count] == 0 || line[count] == ' ' || line[count] == '\t') {
    		line[count] = ' ';
    		if (detected_nline == 0 ) {
	    		continue;
			}
		}
		detected_nline = 1;
		count++;
	}
	if (detected_nline == 0) {
   		return 0;
	} else {
		return count;
	}
}

unsigned char convert_hex_to_bin(unsigned char *line)
{
  	unsigned char	val = 0;

	if (line[0] >= '0' && line[0] <= '9') {
   		val += line[0] - 48;
		val *= 16;
	} else if (line[0] >= 'A' && line[0] <= 'F') {
		val	+= line[0] - 65 + 10;
		val *= 16;
	} else if (line[0] >= 'a' && line[0] <= 'f') {
        val += line[0] - 97 + 10;
		val	*= 16;
    } else {
      	stat.inv_chars++;
	}
	if (line[1] >= '0' && line[1] <= '9') {
   		val += line[1] - 48;
	} else if (line[1] >= 'A' && line[1] <= 'F') {
		val	+= line[1] - 65 + 10;
	} else if (line[1] >= 'a' && line[1] <= 'f') {
        val += line[1] - 97 + 10;
    } else {
      	stat.inv_chars++;
	}

	return val;
}
