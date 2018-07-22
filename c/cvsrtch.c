/* This program list the directories which contain the file "Root" and
 * changes the root name from "whatever" to /home/pratap/repository
 */

#include <stdio.h>

int	main(int argc, char **argv)
{
	int 	i;
	FILE	*fptr;
	char	fname[500];
	
	if (argc < 2) {
		printf("USAGE : Crc base_path_name \n");
		exit(1);
	}

	for (i = 1 ; i < argc ; i++) {
		strcpy(fname, argv[i]);
		strcat(fname, "/Root");
		printf("%d %s \n", i, fname);
		fptr = fopen(fname, "w");
		strcpy(fname, "/home/pratap/repository");
		fwrite(fname, 1, strlen(fname), fptr);
	}
}

		
			
	
