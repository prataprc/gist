#include <stdio.h>

int buffer_sort(unsigned short *, int);

int main(char argc, char *argv[])
{
    FILE *fptr;
    FILE *fptr1;
    unsigned short buffer[1000000];
    int length;
    int n = 0;

    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Unable to open the file \n");
        exit(0);
    }
    fptr1 = fopen(argv[2], "w");
    if (fptr == NULL) {
        printf("Unable to open the file \n");
        exit(0);
    }

    length = fread(buffer, 2, 1000000, fptr);
    printf("Number of characters : %d \n", length);
    printf("Clock Start %d \n", clock());
    n = bubble_sort(buffer, length);
    printf("Clock End %d \n", clock());
    fwrite(buffer, 2, length, fptr1);
    printf("\n count : %d \n", n);
}

int bubble_sort(unsigned short *buffer, int length)
{
    int i, j, k, temp;
    int n;

    printf("%d \n", length);
    for (i = 0; i < length-1; i++) {
        for (j = i+1; j < length; j++) {
            if (buffer[i] > buffer[j]) {
                n++;
                temp = buffer[i];
                buffer[i] = buffer[j];
                buffer[j] = temp;
#ifdef DEBUG
                for(k = 0; k < length; k++) 
                    printf("%d ", buffer[k]);
                printf("\n", buffer[k]);
#endif /* DEBUG */
            }
        }
    } 
    return n;
}

