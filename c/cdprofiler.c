/* This code profiles the CD data. */

#include <stdio.h>

struct sector {
	char sync_rcv;
	int  total_bytes;
	int  start_off;
};

int	 skipped_bytes;
struct sector sec[10000];

int	sec_count;

int	main(int argc, char **argv)
{
  	FILE *cd_fptr;
	int	 curr_off = 0;
	int	 sync_count = 0;
	unsigned char next_sync = 0xFF;
	unsigned char byte;
	int i;


	if (argc < 2) {
   		printf("USAGE : cdpr datafile \n");
		exit(1);
	}

	cd_fptr = fopen(argv[1], "rb");
	if (cd_fptr == NULL) {
   		printf("Failed to open %s \n", argv[1]);
		exit(1);
	}

	sec_count = 0;
	curr_off = 0;
	skipped_bytes = 0;
	/* Move till the first SYNC */
	while (!feof(cd_fptr)) {
		curr_off++;
		skipped_bytes++;
                fread(&byte, 1, 1, cd_fptr);
		if (byte == next_sync) {
			sync_count++;
			if (sync_count == 1 || sync_count == 10) {
				next_sync = 0x00;
			} else if (next_sync == 00) {
				next_sync = 0xFF;
			}
 		} else if (sync_count > 0) {
     		       sync_count = 0;
		       next_sync = 0xff;
		}
		if (sync_count == 9) { /* SYNC FINDER */
                	skipped_bytes -= 9; /* SYNC FINDER */
			sec[sec_count].total_bytes = sync_count;
			break;
		}
	}
	while (!feof(cd_fptr)) {
		fread(&byte ,1, 1, cd_fptr);
                curr_off++;
		if (byte == next_sync) {
   			sync_count++;
    		        if (sync_count == 9) { /* SYNC FINDER */
				sec[sec_count].total_bytes -= 8; /* SYNC FINDER */
                        	sec_count++;
			}
			if (sync_count == 1) {
     				next_sync = 0x00;
			} else if (sync_count == 10) {
     				next_sync = 0;
			} else if (sync_count == 12) {
                                sec[sec_count].start_off = curr_off - sync_count;
				sec[sec_count].total_bytes = sync_count;
				sec[sec_count].sync_rcv = sync_count;
				sync_count = 0;
				next_sync = 0xFF;
			} else if (next_sync == 0x00) {
					next_sync = 0xFF;
			}
		} else if (sync_count > 0) {
			if (sync_count >= 9) { /* SYNC FINDER */
     				sec[sec_count].start_off = curr_off - sync_count;
				sec[sec_count].total_bytes = sync_count;
				sec[sec_count].sync_rcv = sync_count;
				sync_count = 0;
				next_sync = 0xFF;
			} else {
     				sync_count = 0;
				next_sync = 0xFF;
			}

		}
	    	if (sync_count < 9) {
       			sec[sec_count].total_bytes++;
		}
	}

	printf("%d bytes skipped \n", skipped_bytes);
	printf("%d sectors received \n \n", sec_count);
	for (i = 0; i < sec_count; i++) {
   		printf("SECTOR %d : \n", i);
		printf("	sync received	: %d \n", sec[i].sync_rcv);
		printf("	total_bytes	: %d \n", sec[i].total_bytes);
		printf("	starting_offset	: %d \n", sec[i].start_off);
	}
}
