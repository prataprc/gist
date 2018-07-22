#include <stdio.h>
#include <string.h>

/* It is assumed that the .dvh files and the tcl files are in the
 * "current directory"
 *
 * Only "tabs/space" are interpreted between words.
 * Only "new_line/carriage_return" are interpreted between lines
 *
 * The path seperator for the path/file name is '/'
 */

/* USAGE:
 *		convert tcl_file
 */

/* Structures */
struct	tab_files {
  	char	fname[50];
	int		st_add;
	int		size;
};

/* Global variables used */
struct tab_files	dev_files[200];
int		dev_files_count= 0 ;
unsigned char		tcl_buff[65535];

/* Sub function used */
int	parse_tcl_file(FILE *tcl_fptr);
int	format_hex_file(int	dev_id);

int	main(int argc, char ** argv)
{
  	char	*tcl_file;
	FILE	*tcl_fptr;
	FILE	*op_fptr;
	int 	rc;
	int		i;


	if (argc < 2) {
   		printf("Insufficient arguments \n");
		printf("\t convert tcl_file \n");
		exit(1);
	}

	if (argv[1] == 0) {
   		printf("Invalid Argument 1 \n");
		exit(1);
	}
	tcl_file = argv[1];
    tcl_fptr = fopen(tcl_file, "rb");
	if (tcl_fptr == NULL) {
   		printf("Unable to open the file %s \n", tcl_file);
		exit(1);
	}

	rc = parse_tcl_file(tcl_fptr);
	if (rc == -1) {
   		printf("FAILED .... \n");
   		exit(1);
	}

	/* Now from the "dev_files" read each entry and create a corresponding
	 * hex file
	 */
    for (i = 0; i < dev_files_count; i++) {
		format_hex_file(i);
	}
}

/* subfunctions called */
int	get_line(FILE *ip_fptr, char *line);

int	format_hex_file(int	dev_id)
{
  	FILE	*ip_fptr;
	FILE	*op_fptr;
	char 	op_fname[50];
	char 	len;
	char 	line[20];
	char	address_str[20];
	int		address_count;
	char 	*temp;
	int		rc;

	ip_fptr = fopen(dev_files[dev_id].fname, "rb");
	if (op_fptr == NULL) {
   		printf("Failed to open file : %s ...\n", dev_files[dev_id].fname);
		return 0;
	}

	/* Format the o/p file name */
	temp = strchr(dev_files[dev_id].fname, '.');
	len = temp - dev_files[dev_id].fname;
	strncpy(op_fname, dev_files[dev_id].fname, len);
	op_fname[len++] = '.';
	op_fname[len++] = 'x';
	op_fname[len] = 0;

	op_fptr  = fopen(op_fname, "wb");
	if (op_fptr == NULL) {
   		printf("Failed to open the file : %s .... \n", op_fname);
		return 0;
	}

	address_count = dev_files[dev_id].st_add;
	while (!(feof(ip_fptr))) {
   		rc = get_line(ip_fptr, line);
        if (rc == 0) {
        	continue;
        }
		line[8] = 0xa;
		sprintf(address_str,"'H%06x ", address_count);
		fwrite(address_str, 1, 9, op_fptr);
		fwrite(line, 1, 9, op_fptr);
		address_count++;
		if (address_count == (dev_files[dev_id].st_add+dev_files[dev_id].size)){
    		break;
		}
	}

	/* Match for no of memory locations that has to be updated */
	if ((address_count - dev_files[dev_id].st_add) != dev_files[dev_id].size) {
   		printf("Mismatch in size for file %s %s %x %x \n",
				dev_files[dev_id].fname, op_fname, dev_files[dev_id].st_add,
																address_count);
		fclose(op_fptr);
		return 0;
	}
	fclose(op_fptr);
}

/* sub functions called */
int	get_line(FILE *tcl_fptr, char *line);
int	get_word(char *line, char *word, int loc);
int	parse_filename(char *word, char *file_name);
int	convert_hex_to_int(char *file_name);

int	parse_tcl_file(FILE *tcl_fptr)
{
	char	line[500];
	char 	word[100];
	int rc;
	int i;

	while(!(feof(tcl_fptr))) {
		/* get_line() function returns the size of the line */
		rc	= get_line(tcl_fptr, line);
		if (rc == 0) {
			continue;
		}

		rc = get_word(line, word, 1);
		if (rc == 0) {
    		printf("Error unable to read line \n");
			return -1;
		}

		rc = strcmp(word, "dread");
		if (rc != 0) {
    		continue;
		}
		/* Execution enters here if the line is "dread" line */
    	/* Read the file name */
		rc = get_word(line, word, 2);
		if (rc == 0) {
    		printf("Error Invalide tcl line .... \n");
			return -1;
		}
		parse_filename(word, dev_files[dev_files_count].fname);

		/* Read the starting address */
		rc	= get_word(line, word, 4);
		if (rc == 0) {
       		printf("Error Invalid 'dread' line...... \n");
			return -1;
		}
		if (word[0] == '0' && word[1] == 'x') {
   			dev_files[dev_files_count].st_add=convert_hex_to_int(&word[2]);
		} else {
    		printf("Error Invalid start address ... \n");
			return -1;
		}

		rc = get_word(line, word, 5);
		if (rc == 0) {
       		printf("Error Invalid 'dread' line...... \n");
			return -1;
		}
		if (word[0] == '0' && word[1] == 'x') {
    			dev_files[dev_files_count].size=convert_hex_to_int(&word[2]);
		} else {
    		printf("Error Invalid size  ... \n");
			return -1;
		}
		dev_files_count++;
		line[0] = 0;
		word[0] = 0;
	}
	for (i =0; i < dev_files_count; i++) {
   		printf("dev id %d \n", i);
		printf("fname %s \n", dev_files[i].fname);
		printf("st_add %x \n", dev_files[i].st_add);
		printf("size %x \n", dev_files[i].size);
	}
	return 0;
}

/* This function excrats a VALID line from the file and returns them.
 * 	The return value is "length of the line"
 */
int	get_line(FILE *tcl_fptr, char *line)
{
	int		count = 0;
	int		detected_nline = 0;

	while(!(feof(tcl_fptr))) {
   		fread(&line[count], 1, 1, tcl_fptr);
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


int	get_word(char *line, char *word, int loc)
{
	int	count = 0;
	int	word_count = 0;
	int	word_len = 0;
	int	line_len = strlen(line);
	int detected_nword = 0;

	while (line_len--) {
   		word[word_len] = line[count++];
		if (word[word_len] == 0 || word[word_len] == ' ' ||
											word[word_len] == '\t' ) {
			word[word_len] = 0;
			if (detected_nword == 0) {
     			continue;
			}
			word_count++;
			if (word_count == loc) {
				return word_len;
			}
            word_len = 0;
			continue;
		}
		detected_nword = 1;
		word_len++;
	}
	return 0;
}


int	parse_filename(char *word, char *fname)
{
	int	name_count = 0;
	int	word_count;

	printf("word %s \n", word);
	while (fname[name_count] = word[word_count++]) {
   		if (fname[name_count] == '/') {
       		name_count = 0;
			continue;
		}
		name_count++;
	}
	return 0;
}

/* sub function */
void 	strrev(char *source, char *dest);

int	convert_hex_to_int(char *hex_str)
{
	int val = 0;
	int	count = 0;
	char dest[10];
	int	digit = 0;
	int	factor = 0;

	strrev(hex_str, dest);

	while (dest[count]) {
   		if( dest[count] >= '0' && dest[count] <= '9') {
       		digit = dest[count] - '0';
        } else if ( (dest[count] >= 'a' || (dest[count] += 32) >= 'a') &&
						(dest[count] <= 'f' || (dest[count] += 32) >= 'f')) {
        	digit = dest[count] - 'a' + 10;
		} else {
			printf("Invalid Hex String ... \n");
			exit(1);
		}
		val	+= digit << factor;
		factor += 4;
		count++;
	}
	return val;
}

void	strrev(char *source, char *dest)
{
    int	len = strlen(source);
	int count = 0;

	while(len--) {
   		dest[count++] = source[len];
	}
	dest[count] = 0;
}
