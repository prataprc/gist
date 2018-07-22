#include <stdio.h>

int insertion_sort(unsigned short *, int);

int main(char argc, char *argv[])
{
    FILE *fptr;
    FILE *fptr1;
    unsigned short buffer[1000000];
    int length = 0;
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
    n = insertion_sort(buffer, length);
    printf("Clock End %d \n", clock());
    fwrite(buffer, 2, length, fptr1);
    printf("\n count : %d \n", n);
}

int insertion_sort(unsigned short *buffer, int length)
{
    int i, j, k, temp, n = 0;
    for (i=1; i < length; i++)
    {
        temp = buffer[i];
        j = i;
        while ((j > 0) && (buffer[j-1] > temp))
        {
            buffer[j] = buffer[j-1];
            j = j - 1;
#ifdef DEBUG
            for(k = 0; k < length; k++) 
               printf("%d ", buffer[k]);
            printf("\n", buffer[k]);
#endif /* DEBUG */
        }
        buffer[j] = temp;
    }

}



