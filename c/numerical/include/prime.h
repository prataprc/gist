#ifndef _PRIME_H_

#define MAXFACTORS 32   /* Maximum factors a 32bit number can have */

extern u32 loadprimes( u32 limit );
extern void factors( u32 num, u32 *fact, u32 *count );
extern u32 genprime( u32 limit );
extern u32 getprimes( u32 *primes, u32 upto );

#endif /* _PRIME_H_ */
