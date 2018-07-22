#include <stdio.h>

int buffer_sort(unsigned short *, int);
int n = 0;
int calls = 0;
int depth = 1;
int main(char argc, char *argv[])
{
    FILE *fptr;
    FILE *fptr1;
    unsigned short buffer[1000000];
    int length;

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
    quick_sort(buffer,0, length-1);
    printf("Clock End %d \n", clock());
    fwrite(buffer, 2, length, fptr1);
    printf("\n count : %d \n", n);
}

int quick_sort(unsigned short *buffer, int left, int right)
{
    int pivot;
    int stick_left, stick_right;

    //printf("%x %x \n", &left, &right);
    calls++;
    if (depth <= calls) {
        depth = calls;
        printf("depth %d \n", depth);
    }
#if 0
    printf("%d \n", stack_count++);
#endif 
    pivot = buffer[left];
    stick_left = left;
    stick_right = right;

    while (left < right) {
        while((pivot < buffer[right]) && (left < right))
            right--;
        if (left != right) {
            n++;
            buffer[left] = buffer[right];
            left++;
        }
        while((pivot > buffer[left]) && (left < right))
            left++;
        if (left != right) {
            n++;
            buffer[right] = buffer[left];
            right--;
        }
    }
    buffer[left] = pivot;
    if (stick_left < left) {
        // printf("left = %d stick_left = %d \n", 
        //            left, stick_left);
        quick_sort(buffer, stick_left, left -1); 
    }
    if (stick_right > left) {
        //printf("left = %d stick_right = %d \n", 
        //            left, stick_right);
        quick_sort(buffer, left+1, stick_right); 
    } 
    calls--;
}

