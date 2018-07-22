#ifndef _BITS_H_

#include "types.h"

/* The following logic provides bit operation interfaces */

/* Return -1 if negative or ZERO */
#define sign(v)     ((v) >> (sizeof((v))*8-1))

/* ABS without branching */
#define abs(v)      (((v) ^ sign(v)) - sign(v))

/* minimum of two integers without branching */
#define min(m, n)   ((n) + (((m)-(n)) & sign(((m)-(n)))))

/* maximum of two integers without branching */
#define max(m, n)   ((m) - (((m)-(n)) & sign(((m)-(n)))))

/* Check whether 'v' is a power of 2 */
#define ispow2(v)   ((v) & ((v)-1))

/* Is sign-extending implicit in all of the languages ??? */

/* Set bits */
#define set(w, m)   ((w) | (m))

/* Clear bits */
#define clear(w, m) ((w) & (m))

/* Conditional bit setting. If f is TRUE, set bits, else clear bits ??? */
#define setclear(f, w, m)   ((w) ^ ((-(f) ^ (w)) & (m)))

/* Clear LSB */
#define clearlsb(v) ((v) & ((v) - 1))

/* Count the number of bits in a byte, hword, word using lookup */
static u8 _bits = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};
#define bitsinbyte(b)   (bits[b])
#define bitsinhword(hw) (bitsinbyte(( hw&0xFF )) + \
                         bitsinbyte(( (u16)hw>>8 )))
#define bitsinword(hw)  (bitsinword(( w&0xFFFF )) + \
                         bitsinword(( (u32)w>>16 )))

    /* Count the number of bits in the variable using K&R method */
#define countbits(w)    ({ u64 _c=0, _w=(w); for(;_w;_c++) _w=clearlsb(_w); _c})

/* Parity */
#define parity(w)   (countbits((w)) & 1)

/* Swap */
#define swap(a, b)  ((a^=b), (b^=a), (a^=b))

    /* Swapping individual bits with XOR */
#define swapbits(i, j, n, w)  ({ typeof((w)) _x; \
                                _x = (((w) >> i) ^ ((w) >> j)) & ((1<<n) - 1);\
                                (w) ^ ((_x<<i) | (_x<<j)) })

/* Reverse the bits in byte 64 bit version */
#define revbyte( b )    (((b) * 0x0202020202ULL & 0x010884422010ULL) % 1023)
    /* Reverse the bits in byte non-64bit version */
#define revbyte1( b)    ((((b) * 0x0802LU & 0x22110LU) | \
                          (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16)
    /* Reverse bits - generic */
#define reverse( m )    ({ s32  _i=sizeof(m)*8-1, _t=(m), _m=(m); \
                           for( ; _i ; _i-- ) { _t |= v&1; _t<<=1; _v>>=1; } \
                           _v })

/* logbase2 of an integer - generic way */
#define log2(v)     ({ typeof(v) _v=(v), _x=0 ; while( _v>>=1 ) _x++; _x })
