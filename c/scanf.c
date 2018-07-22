#include <stdio.h>

int main(void)
{
    char    name[10];

    scanf( "%s", name); /* catalog\0 */
    scanf( "%s", &name[3]); /* catdog\0ue\0 */
    printf( "%s", name);
}
