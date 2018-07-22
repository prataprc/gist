// 	This program generates attenuates the input signal 
//
//	Usage :
//		genwave freq_n freq_d [phase] sample_freq filename
// 		
//		freq 		- The frequency of the desired wave, in float.
//		phase		- The phase can range from 0 to 360.
//		sample_freq	- Sample frequency of the output wave.
//
//
//	Output :
//		Generates the file 'filename' which contains the PCM samples 
//		with sampling frequency 'sample_freq' and sample size as 16 
//		bits. The duration of the file will be 5 minutes.
//

#include <stdio.h>
#include <math.h>
#include <string.h>

extern void    gen_sin(float freq, int phase, int sf,  short *buff, 
                                                        char type);

int main(int argc, char *argv[])
{
	int freq_n, freq_d, phase = 0, sf;
	char filename[100];
	int total_samples;
	FILE *fptr;
    float freq;
    short buff[48000];
    int n;

	if (argc < 5) {
		printf("Usage : genwave freq [phase] sample_freq filename\n");
		exit(1);
	}

	strcpy(filename, argv[argc-1]);
	fptr = fopen(filename, "w");
	if (fptr == NULL) {
		printf("Unable to open the file %s for Writing ... \n",
			filename);
		exit(1);
	}
	

	freq_n = atoi(argv[1]);
	freq_d = atoi(argv[2]);
    freq = freq_n/freq_d;
	if (argc == 5) {
		phase = 0;
		sf = atoi(argv[3]);
	} else if (argc == 6) {
		phase = atoi(argv[3]);
		sf = atoi(argv[4]);
	}

	printf("User Inputs : \n");
	printf("\t Analog Frequency \t\t : %f \n", freq);
	printf("\t Phase            \t\t : %d \n", phase);
	printf("\t Sample Frequency \t\t : %d \n", sf);

	// Generate the PCM wave, sin(2*pi*f*n / N)

    gen_sin(freq, phase, sf, buff,1);

    for (n = 0; n < sf; n++) {
        fwrite(&buff[n], 2, 1, fptr);
    }
	return 0;
}
