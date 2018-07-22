/* Local Labels are defined within the scope of the block and can only be
 * referenced within the block.
 *
 * The declaration of the local label looks like,
 *      __label__ label1, label2, label3, label4;
 *
 * The declaration of the local labels should be at the begining of the block.
 *
 * The local label declaration also make the labels they declare visible to
 * nested functions, if there are any.
 */

/* The are occasions where a macro might need labels for goto statements. On
 * these occasions a multiple usage of the MACRO within the same function
 * leads to problems. _local_labels_ can be used to avoid this problems
 */

#define SEARCH(value, array, arr_len, target)               \
    ({  __label__ found;                                    \
        typeof(target) _SEARCH_target = target;             \
        typeof(*(array)) *_SEARCH_array = (array);          \
        int i ;                                             \
        for (i =0; i < arr_len; i++) {                      \
            if (_SEARCH_array[i] == _SEARCH_target) {       \
                (value) = i; goto found;                    \
            }                                               \
        }                                                   \
        found :                                             \
        (value);                                            \
    })                                                      \


int main(void)
{
    int a[10];
    int i;
    int found = 0;

    for(i = 0; i < 10; i++) {
        a[i] = i * 10;
    }
    printf("Enter a value : ");
    scanf("%d", &i);

    printf("%d \n", SEARCH(found, a, 10, i));
}
