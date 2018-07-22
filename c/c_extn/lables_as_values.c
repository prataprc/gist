/* The labels inside the functions can be used as _constant_values_. The
 * address of the labels can be obtained using the operator "&&".
 * The obtained address is of the type (void *) ....
 */

int main(void)
{
    void *label_array[] = {&&label1, &&label2, &&label3};
    int ip;

    printf("Enter 1 or 2 or 3 :");
    scanf("%d", &ip);
    goto *label_array[ip-1];

label1:
    printf("Hoo Hoo Number 1 is selected \n");
    goto ret;
label2:
    printf("Uhmm the First Prime Number \n");
    goto ret;
label3:
    printf("The first prime number which is odd \n");

ret:
    return;
}
