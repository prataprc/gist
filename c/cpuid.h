#ifndef _CPUID_H_
#define _CPUID_H_

#define MAX_CONFIGS     512
#define MAX_CACHES      16
#define OP_BUFF_SIZE    2048

/* This program only uses 8 bit, 16 bit and 32 bit number, and so the
 * following typedefs
 */
typedef char            int8_t;
typedef unsigned char   uint8_t;
typedef short           int16_t;
typedef unsigned short  uint16_t;
typedef int             int32_t;
typedef unsigned int    uint32_t;

typedef struct _cpuid_t {               /* Result of CPUID instruction */
    uint32_t    eax;
    uint32_t    ebx;
    uint32_t    ecx;
    uint32_t    edx;
} cpuid_t;

typedef struct _cpuinfo_t {
    cpuid_t     func0;                  /* EAX = 0 */
    uint8_t     vendorstr[16];
    cpuid_t     func1;                  /* EAX = 1 */
    uint8_t     configs[ MAX_CONFIGS ]; /* EAX = 2 */
    uint32_t    psn[2];                 /* EAX = 3, FIXME : not yet implemented */
    cpuid_t     func4[ MAX_CACHES ];    /* EAX = 4 */
    cpuid_t     func5;                  /* EAX = 5 */
    cpuid_t     func6;                  /* EAX = 6 */
    cpuid_t     funcA;                  /* EAX = A */
    cpuid_t     extfunc0;               /* EAX = 0x80000000 */
    cpuid_t     extfunc1;               /* EAX = 0x80000001 */
    cpuid_t     extfunc2;               /* EAX = 0x80000002 */
    cpuid_t     extfunc3;               /* EAX = 0x80000003 */
    cpuid_t     extfunc4;               /* EAX = 0x80000004 */
    cpuid_t     extfunc5;               /* EAX = 0x80000005 */
    cpuid_t     extfunc6;               /* EAX = 0x80000006 */
    cpuid_t     extfunc7;               /* EAX = 0x80000007 */
    cpuid_t     extfunc8;               /* EAX = 0x80000008 */
    cpuid_t     extfuncA;               /* EAX = 0x8000000A */
    cpuid_t     extfunc19;              /* EAX = 0x80000019 */
    cpuid_t     extfunc1A;              /* EAX = 0x8000001A */
} cpuinfo_t;

/****************************************************************************
 *                              AMD specific definitions
 ***************************************************************************/

/* cpu details */
#define AMD_STEPPING(val)       (( val ) & 0x0000000F)
#define AMD_MODEL(val)          ( ((( val ) & 0x000000F0) >> 4 ) |          \
                                  ((( val ) & 0x000F0000) >> 12 ) )
#define AMD_FAMILY(val)         ( (( val ) & 0x00000F00 ) == 0x00000F00 ?   \
                                  0xF + ((( val ) & 0x0FF00000) >> 20)  :   \
                                  (( val ) & 0x00000F00 ) >> 8 )

#define AMD_BRANDID(val)        (( val ) & 0x000000FF )
#define AMD_CLFLUSH(val)        ( (( val ) & 0x0000FF00 ) >> 8 )
#define AMD_CPUCOUNT(val)       ( (( val ) & 0x00FF0000 ) >> 16 )
#define AMD_APICID(val)         ( (( val ) & 0xFF000000 ) >> 24 )

#define AMD_MLINEMIN(val)       (( val ) & 0xFFFF )
#define AMD_MLINEMAX(val)       (( val ) & 0xFFFF )
#define AMD_EMX(val)            (( val ) & 0x1 )
#define AMD_IBE(val)            (( val ) & 0x2 )

#define AMD_MOVU(val)           (( val ) & 2 )
#define AMD_FP128(val)          (( val ) & 1 )

#define AMD_PAS(val)            (( val ) & 0xFF )
#define AMD_LAS(val)            ( (( val ) & 0xFF00 ) >> 8 )
#define AMD_NCORES(val)         (( val ) & 0xFF )
#define AMD_APIC_CID_SIZE(val)  ( (( val ) & 0xF000 ) >> 12 )

/* svm details */
#define AMD_SVMREV(val)         (( val ) & 0xFF )

/* memory details */
#define AMD_L1_CACHE_LS(val)    (( val ) & 0xFF )
#define AMD_L1_CACHE_LPT(val)   ((( val ) & 0x0000FF00 ) >> 8 )
#define AMD_L1_CACHE_ASSC(val)  ((( val ) & 0x00FF0000 ) >> 16 )
#define AMD_L1_CACHE_SIZE(val)  ((( val ) & 0xFF000000 ) >> 24 )

#define AMD_L1_ITLB_SIZE(val)   (( val ) & 0xFF ) 
#define AMD_L1_ITLB_ASSC(val)   ((( val ) & 0x0000FF00 ) >> 8 )
#define AMD_L1_DTLB_SIZE(val)   ((( val ) & 0x00FF0000 ) >> 16 )
#define AMD_L1_DTLB_ASSC(val)   ((( val ) & 0xFF000000 ) >> 24 )

#define AMD_L2_CACHE_LS(val)    (( val ) & 0xFF )
#define AMD_L2_CACHE_LPT(val)   ((( val ) & 0x00000F00 ) >> 8 )
#define AMD_L2_CACHE_ASSC(val)  ((( val ) & 0x0000F000 ) >> 12 )
#define AMD_L2_CACHE_SIZE(val)  ((( val ) & 0xFFFF0000 ) >> 16 )

#define AMD_L2_ITLB_SIZE(val)   (( val ) & 0xFFF ) 
#define AMD_L2_ITLB_ASSC(val)   ((( val ) & 0x0000F000 ) >> 12 )
#define AMD_L2_DTLB_SIZE(val)   ((( val ) & 0x0FFF0000 ) >> 16 )
#define AMD_L2_DTLB_ASSC(val)   ((( val ) & 0xF0000000 ) >> 28 )

#define AMD_L3_CACHE_LS(val)    (( val ) & 0xFF )
#define AMD_L3_CACHE_LPT(val)   ((( val ) & 0x00000F00 ) >> 8 )
#define AMD_L3_CACHE_ASSC(val)  ((( val ) & 0x0000F000 ) >> 12 )
#define AMD_L3_CACHE_SIZE(val)  ((( val ) & 0xFFFC0000 ) >> 18 )

/****************************************************************************
 *                              Intel specific definitions
 ***************************************************************************/

/* cpu details */
#define INTEL_STEPPING(val)     (( val ) & 0xF )
#define INTEL_MODEL(val)        ( ((( val ) & 0xF00 ) == 0x600 ) ||           \
                                  ((( val ) & 0xF00 ) == 0xF00 ) ?            \
                                  ((( val ) & 0xF0 ) >> 4 ) + ((( val ) & 0xF0000 ) >> 12 ) : \
                                  (( val ) & 0xF0 ) >> 4 )
#define INTEL_FAMILY(val)       ( (( val ) & 0xF00 ) == 0xF00  ?              \
                                  ((( val ) & 0xF00 ) >> 8 ) + ((( val ) & 0xFF00000 ) >> 20 ) : \
                                  (( val ) & 0xF00 ) >> 8 )
#define INTEL_CPUID(val)        ( (( val ) & 0x3000 ) >> 12 )

#define INTEL_BRANDID(val)      (( val ) & 0xFF )
#define INTEL_CLFLUSH(val)      ( (( val ) & 0xFF00 ) >> 8 )
#define INTEL_CPUCOUNT(val)     ( (( val ) & 0xFF0000 ) >> 16 )
#define INTEL_APICID(val)       ( (( val ) & 0xFF000000 ) >> 24 )

/* memory details */

#define INTEL_CACHETYPE(val)    (( val ) & 0x1F )
#define INTEL_CACHELEVEL(val)   ( (( val ) & 0xE0 ) >> 5 )
#define INTEL_SELFINIT(val)     ( (( val ) & 0x100 ) >> 8 )
#define INTEL_FULLASSC(val)     ( (( val ) & 0x200 ) >> 9 )
#define INTEL_WBINVALIDATE(val) ( (( val ) & 0x400 ) >> 10 )
#define INTEL_INCLUSIVE(val)    ( (( val ) & 0x800 ) >> 11 )
#define INTEL_MAXTHREADS(val)   ( (( val ) & 0x3FFC000 ) >> 14 )
#define INTEL_MAXCORES(val)     ( (( val ) & 0xFC000000 ) >> 26 )
#define INTEL_L(val)            (( val ) & 0xFFF )
#define INTEL_P(val)            ( (( val ) & 0x3FF000 ) >> 12 )
#define INTEL_W(val)            ( (( val ) & 0xFFC00000 ) >> 22 )

#define INTEL_C0(val)           (( val ) & 0xF )
#define INTEL_C1(val)           ( (( val ) & 0xF0 ) >> 4 )
#define INTEL_C2(val)           ( (( val ) & 0xF00 ) >> 8 )
#define INTEL_C3(val)           ( (( val ) & 0xF000 ) >> 12 )
#define INTEL_C4(val)           ( (( val ) & 0xF0000 ) >> 16 )

#define INTEL_PERF_VER(val)     (( val ) & 0xFF )
#define INTEL_PERF_COUNT(val)   ( (( val ) & 0xFF00 ) >> 8 )
#define INTEL_PERF_BW(val)      ( (( val ) & 0xFF0000 ) >> 16 )
#define INTEL_PERF_LENEBX(val)  ( (( val ) & 0xFF000000 ) >> 24)
#define INTEL_PERF_FFCNT(val)   (( val ) & 0x1F )
#define INTEL_PERF_FFBW(val)    ( (( val ) & 0x1FE0 ) >> 5 )



#endif  /* _CPUID_H_ */
