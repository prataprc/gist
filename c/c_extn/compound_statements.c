/* A compound statement enclosed in paranthesis may appear as an _expression_ 
 * in GNU C. This helps us to implement local variables, loops, switches
 * within the expression.
 *
 * The compound statement generates an _rvaue_. It cannot be used for _lvalue_
 */

/* The compund statements can be used to implement MACROS reducing the side
 * effects
 */

#define max(a,b) ({int _a = a; int _b= b; int _c ; _c = _a > _b ? _a : _b; _c;})
int main(void)
{
    int a, b,  c;
    printf("Enter two numbers : ");
    scanf("%d %d", &a, &b);
    printf("MAX : %d ", max(a,b--)); 
}
