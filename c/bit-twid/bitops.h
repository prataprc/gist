#ifdef __BITOPS_H__

#include <stdio.h>

#define BITS_PER_BYTE 8

/* Returns -1 if negative, ZERO otherwise */
#define IS_NEGATIVE(a, type) ((a) >> ((sizeof(type) * BITS_PER_BYTE) - 1))
#define IS_POWER2(a) (!((a) & ((a) -1)))

#ifdef EXPENSIVE_BRANCH

/* (1's complement - 1) is the logic. The side effect is that, if 'a' is 
 * MAX_NEG the result is also MAX_NEG
 */
#define ABS(a,type) (((a) ^ ((a) >> (sizeof(type) * BITS_PER_BYTE) - 1)) - \
			    ((a) >> (sizeof(type) * BITS_PER_BYTE) - 1))
/* r = b + (a-b) & IS_NEGATIVE(a-b),
 *	if b > a,  r = b + (a-b) & -1 => r = b + a -b => r = a
 * 	if a >= b, r = b + (a-b) & 0 => r = b
 */
#define MIN(a, b, type) ((b) + (((a) - (b)) & \
			(((a) - (b)) >> (sizeof(type) * BITS_PER_BYTE) - 1)))

#define MAX(a, b, type) ((a) - (((a) - (b)) & \
			(((a) - (b)) >> (sizeof(type) * BITS_PER_BYTE) - 1)))
#else 

#define ABS(a,type) ((a) < 0 ? (-a) : (a))
#define MIN(a, b, type) ((a) < (b) ? (a) : (b))
#define MAX(a, b, type) ((a) > (b) ? (a) : (b))

#endif /* EXPENSIVE_BRANCH */

#endif /* __BITOPS_H__ */
