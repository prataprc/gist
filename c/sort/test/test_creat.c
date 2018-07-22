#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr;
    unsigned short buffer[32767];
    int  i, j, k;
    int random_count = 450;

    fptr = fopen("asc_rand450.tst", "w");
    if (fptr == NULL) {
        printf("Unable to open the file \n");
        exit(0);
    }

    i = 32767;
    j = 16383;
    k = 0;

    /* Random - predictable
    while(i--) {
        buffer[j] = (short)k++;
        if (k/2 == (float)k/2) {
            j += k;
        } else {
            j -= k;
        }
    } */

    /* Almost random 
    while(i--) {
        buffer[j] = rand() / 65536;
    } */

    /* ascending */
    while (i--)  {
        buffer[k] = k++;
    } 

    /* randomise the ascending */
    while(random_count--) {
        i = rand() / 65535;
        j = rand() / 65535;
        k = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = k;
    }

    /* descending 
    while (i) {
        buffer[k++] = i--;
    } */

    /* randomise the ascending 
    while(random_count--) {
        i = rand() / 65535;
        j = rand() / 65535;
        k = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = k;
    } */

    fwrite(buffer,2,32767, fptr);
    fclose(fptr);
}
