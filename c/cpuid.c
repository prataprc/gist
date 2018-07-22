#include <stdio.h>
#include <string.h>
#include "cpuid.h"

/*
 * Notes :
 * This program probes the processor with CPUID instruction.
 * Consists of 2 parts,
 *
 * Part 1 : Collect the cpu information and populate it in a local table.
 *
 * Part 2 : Format the information for printing, the information is ruffly
 *          classified into, cpu, memory, svm, apm (power) catogaries
 *
 * Optionally a third part may be added, providing library functions to know
 * specific details about the CPU.
 */

/* Exported identifiers */
cpuid_t cpuid( unsigned long number, uint32_t ecx );
void cpuid_details( cpuinfo_t cpu, char * options, char *buffer, unsigned int size );
cpuinfo_t get_cpuid(void);

/* Local identifiers */

static cpuinfo_t cpu;
static char op_buffer[OP_BUFF_SIZE];

static void vendorstring( cpuinfo_t *cpu );

static void intel_identify( void );
static uint8_t * intel_collect_configs( cpuid_t res, uint8_t *config );
static void intel_summary_details( cpuinfo_t cpu, char *buffer );
static void intel_cpu_details( cpuinfo_t cpu, char *buffer );
static void intel_memory_details( cpuinfo_t cpu, char *buffer );
static void intel_svm_details( cpuinfo_t cpu, char *buffer );
static void intel_apm_details( cpuinfo_t cpu, char *buffer );
static void intel_dump_details( cpuinfo_t cpu, char *buffer );

static void amd_identify( void );
static void amd_summary_details( cpuinfo_t cpu, char *buffer );
static void amd_cpu_details( cpuinfo_t cpu, char *buffer );
static void amd_memory_details( cpuinfo_t cpu, char *buffer );
static void amd_svm_details( cpuinfo_t cpu, char *buffer );
static void amd_apm_details( cpuinfo_t cpu, char *buffer );
static void amd_dump_details( cpuinfo_t cpu, char *buffer );

int main( void )
{
    cpuinfo_t   cpuinfo;

    cpuinfo     = get_cpuid();
    cpuid_details(cpuinfo, "a", op_buffer, OP_BUFF_SIZE);
    printf("%s \n", op_buffer);
}

/* 
 * Return EAX, EBX, ECX, EDX contents (through cpuid_t) for the parameter
 * value mentioned in 'number'
 */
cpuid_t cpuid(unsigned long number, uint32_t ecx) 
{
    cpuid_t         result; 
    unsigned long   rcx = ( unsigned long ) ecx;
    
    /* %rax <- number, %rcx <- ecx call CPUID, save %eax, %ebx, %ecx, %edx in 
     * result.  o/p constraint "m=" has been used as this keeps 
     * gcc's optimizer from overwriting %eax, %ebx, %ecx, %edx by accident */
    asm("movq %4, %%rax; movq %5, %%rcx; cpuid; movq %%rax, %0; movq %%rbx, %1;\
         movq %%rcx, %2; movq %%rdx, %3;"
            : "=m" (result.eax),
              "=m" (result.ebx),
              "=m" (result.ecx),
              "=m" (result.edx)               /* output */
            : "r"  (number),                  /* input */
              "r"  (rcx)
            : "rax", "rbx", "rcx", "rdx"    
       );
    return result;
}

/****************************************************************************
 * Part 1:
 * The following functions collect the CPUID functions and details for Intel
 * and AMD and returns the cpuinfo table back to the caller.
 ***************************************************************************/

cpuinfo_t get_cpuid(void)
{
    cpuid_t         res;
    uint32_t        i;
    uint8_t         *config;
    uint8_t         *tmp;

    /* FIXME : The cpuid can be limited to 3 funcs by the bit
     * IA32_MISC_ENABLES.BOOT_NT4[22]. Though the default setting is ZERO,
     * BIOS could alter it later.
     *
     * Also the desired sequence should be,
     *      IS 386
     *      IS 486
     *      IS CPUID present
     *      probe for CPUID
     */

    /* Clear memory */
    tmp         = (uint8_t *) &cpu;
    for ( i = 0 ; i < sizeof(cpuinfo_t) ; i++ ) {
        *tmp++ = 0;
    }

    res         = cpuid( 0, 0 ); 
    cpu.func0  = res;
    vendorstring( &cpu );
    if ( strncmp( cpu.vendorstr, "GenuineIntel", 12 ) == 0 ) {
        intel_identify();
    } else if ( strncmp( cpu.vendorstr, "AuthenticAMD", 12 ) == 0 ) {
        amd_identify();
    } else {
        printf( "Unknown Vendor Idenfication \n" );
    }
    return cpu;
}
    
static void intel_identify( void )
{
    cpuid_t         res;
    uint32_t        i;
    uint8_t         *config;

    if ( cpu.func0.eax >= 1 ) {
        cpu.func1  = cpuid( 1, 0 );
    }

    if ( cpu.func0.eax >= 2 ) {
        /* FIXME : Make sure that func 2 call for CPUID is made from the
         * beginning and the following code is executed on the same CPU
         */
        config  = cpu.configs;
        i       = 0; 
        do {
            res     = cpuid( 2, 0 );
            i++;
            config  = intel_collect_configs( res, config );
            if ( config[0] == 0 ) {
                printf("Config 0 says ZERO configs \n");
            }
        } while ( i < config[0] );
    }

    if ( cpu.func0.eax >= 3 ) {
        /* PSN is not implemented */
    }

    if ( cpu.func0.eax >= 4 ) {
        for ( i = 0 ; i < MAX_CACHES ; i++ ) {
            cpu.func4[i]   = cpuid( 4, i );
            if (( res.eax & 0xF ) == 0 ) {
                break;
            }
        }
    }

    if ( cpu.func0.eax >= 5 ) {
        cpu.func5  = cpuid( 5, 0 );
    }

    if ( cpu.func0.eax >= 6 ) {
        cpu.func6  = cpuid( 6, 0 );
    }

    if ( cpu.func0.eax >= 10 ) {
        cpu.funcA  = cpuid( 10, 0 );
    }

    /* Extended CPUID functions */
    res     = cpuid( 0x80000000, 0 );
    if ( res.eax & 0x80000000 ) {       /* extended functions not supported */
        return;
    }
    cpu.extfunc0   = res;
    
    if ( cpu.extfunc0.eax >= 1 ) {
        cpu.extfunc1   = cpuid( 0x80000001, 0 );
    }

    if ( cpu.extfunc0.eax >= 2 ) {
        cpu.extfunc2   = cpuid( 0x80000002, 0 );
    }

    if ( cpu.extfunc0.eax >= 3 ) {
        cpu.extfunc3   = cpuid( 0x80000003, 0 );
    }

    if ( cpu.extfunc0.eax >= 4 ) {
        cpu.extfunc4   = cpuid( 0x80000004, 0 );
    }

    if ( cpu.extfunc0.eax >= 5 ) {
        cpu.extfunc5   = cpuid( 0x80000005, 0 );
    }

    if ( cpu.extfunc0.eax >= 6 ) {
        cpu.extfunc6   = cpuid( 0x80000006, 0 );
    }

    if ( cpu.extfunc0.eax >= 7 ) {
        cpu.extfunc7   = cpuid( 0x80000007, 0 );
    }

    if ( cpu.extfunc0.eax >= 8 ) {
        cpu.extfunc8   = cpuid( 0x80000008, 0 );
    }
}

static uint8_t * intel_collect_configs( cpuid_t res, uint8_t *config )
{
    if ( (res.eax & 0x80000000) == 0 ) {
        if ( res.eax & 0xFF ) *config++ = res.eax & 0xFF;
        if (( res.eax >> 8  ) & 0xFF ) *config++ = ( res.eax >> 8 ) & 0xFF;
        if (( res.eax >> 16 ) & 0xFF ) *config++ = ( res.eax >> 16 ) & 0xFF;
        if (( res.eax >> 24 ) & 0xFF ) *config++ = ( res.eax >> 24 ) & 0xFF;
    }
    if ( (res.ebx & 0x80000000) == 0 ) {
        if ( res.ebx & 0xFF ) *config++ = res.ebx & 0xFF;
        if (( res.ebx >> 8  ) & 0xFF ) *config++ = ( res.ebx >> 8 ) & 0xFF;
        if (( res.ebx >> 16 ) & 0xFF ) *config++ = ( res.ebx >> 16 ) & 0xFF;
        if (( res.ebx >> 24 ) & 0xFF ) *config++ = ( res.ebx >> 24 ) & 0xFF;
    }
    if ( (res.ecx & 0x80000000) == 0 ) {
        if ( res.ecx & 0xFF ) *config++ = res.ecx & 0xFF;
        if (( res.ecx >> 8  ) & 0xFF ) *config++ = ( res.ecx >> 8 ) & 0xFF;
        if (( res.ecx >> 16 ) & 0xFF ) *config++ = ( res.ecx >> 16 ) & 0xFF;
        if (( res.ecx >> 24 ) & 0xFF ) *config++ = ( res.ecx >> 24 ) & 0xFF;
    }
    if ( (res.edx & 0x80000000) == 0 ) {
        if ( res.edx & 0xFF ) *config++ = res.edx & 0xFF;
        if (( res.edx >> 8  ) & 0xFF ) *config++ = ( res.edx >> 8 ) & 0xFF;
        if (( res.edx >> 16 ) & 0xFF ) *config++ = ( res.edx >> 16 ) & 0xFF;
        if (( res.edx >> 24 ) & 0xFF ) *config++ = ( res.edx >> 24 ) & 0xFF;
    }

    return config;
}

static void amd_identify( void )
{
    cpuid_t         res;

    if ( cpu.func0.eax >= 1 ) {
        cpu.func1  = cpuid( 1, 0 );
    }

    /* For AMD, functions 2,3,4 are reserved */

    if ( cpu.func0.eax >= 5 ) {
        cpu.func5  = cpuid( 5, 0 );
    }

    /* Extended CPUID functions */
    res     = cpuid( 0x80000000, 0 );
    if ( !( res.eax & 0x80000000 )) {       /* extended functions not supported */
        return;
    }
    cpu.extfunc0    = res;
                     
    if ( cpu.extfunc0.eax >= 0x80000001 ) {
        cpu.extfunc1    = cpuid( 0x80000001, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000002 ) {
        cpu.extfunc2    = cpuid( 0x80000002, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000003 ) {
        cpu.extfunc3    = cpuid( 0x80000003, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000004 ) {
        cpu.extfunc4    = cpuid( 0x80000004, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000005 ) {
        cpu.extfunc5    = cpuid( 0x80000005, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000006 ) {
        cpu.extfunc6    = cpuid( 0x80000006, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000007 ) {
        cpu.extfunc7    = cpuid( 0x80000007, 0 );
    }

    if ( cpu.extfunc0.eax >= 0x80000008 ) {
        cpu.extfunc8    = cpuid( 0x80000008, 0 );
    }

    /* Function 9 is reserved */

    if ( cpu.extfunc0.eax >= 0x8000000A ) {
        cpu.extfuncA    = cpuid( 0x8000000A, 0 );
    }

    /* Functions [0xB-0x18] are reserved */

    if ( cpu.extfunc0.eax >= 0x80000019 ) {
        cpu.extfunc19   = cpuid( 0x80000019, 0 );
    }
    if ( cpu.extfunc0.eax >= 0x8000001A ) {
        cpu.extfunc1A   = cpuid( 0x8000001A, 0 );
    }

    return;
}

static void vendorstring( cpuinfo_t *cpu )
{
    cpu->vendorstr[0]   = (uint8_t) ( cpu->func0.ebx & 0xFF );
    cpu->vendorstr[1]   = (uint8_t) (( cpu->func0.ebx >> 8 ) & 0xFF );
    cpu->vendorstr[2]   = (uint8_t) (( cpu->func0.ebx >> 16 ) & 0xFF );
    cpu->vendorstr[3]   = (uint8_t) (( cpu->func0.ebx >> 24 ) & 0xFF );
    cpu->vendorstr[4]   = (uint8_t) ( cpu->func0.edx & 0xFF );
    cpu->vendorstr[5]   = (uint8_t) (( cpu->func0.edx >> 8 ) & 0xFF );
    cpu->vendorstr[6]   = (uint8_t) (( cpu->func0.edx >> 16 ) & 0xFF );
    cpu->vendorstr[7]   = (uint8_t) (( cpu->func0.edx >> 24 ) & 0xFF );
    cpu->vendorstr[8]   = (uint8_t) ( cpu->func0.ecx & 0xFF );
    cpu->vendorstr[9]   = (uint8_t) (( cpu->func0.ecx >> 8 ) & 0xFF );
    cpu->vendorstr[10]  = (uint8_t) (( cpu->func0.ecx >> 16 ) & 0xFF );
    cpu->vendorstr[11]  = (uint8_t) (( cpu->func0.ecx >> 24 ) & 0xFF );
    cpu->vendorstr[12]  = 0;
}

/***************************************************************************
 * Part 2:
 * The following functions are to format the output
 **************************************************************************/

/* Options are,
 *      c       cpu details
 *      m       memory details
 *      s       svm details
 *      p       power details
 *      d       dump of CPUID values in hex
 *      a       all the details
 */

void cpuid_details(cpuinfo_t cpu, char *options, char *buffer, unsigned int size )
{
    uint32_t    i;

    *buffer     = 0;
    if ( strncmp( cpu.vendorstr, "GenuineIntel", 12 ) == 0 ) {
        intel_summary_details( cpu, buffer );
        buffer  += strlen(buffer);
        while ( *options ) {
            switch ( *options ) {
                case 'c' :
                    intel_cpu_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'm' :
                    intel_memory_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 's' :
                    intel_svm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'p' :
                    intel_apm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'd' :
                    intel_dump_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'a' :
                    intel_cpu_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    intel_memory_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    intel_svm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    intel_apm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    intel_dump_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
            }
            options++;
        }
    } else if ( strncmp( cpu.vendorstr, "AuthenticAMD", 12 ) == 0 ) {
        amd_summary_details( cpu, buffer );
        buffer  += strlen(buffer);
        while ( *options ) {
            switch ( *options ) {
                case 'c' :
                    amd_cpu_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'm' :
                    amd_memory_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 's' :
                    amd_svm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'p' :
                    amd_apm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'd' :
                    amd_dump_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
                case 'a' :
                    amd_cpu_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    amd_memory_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    amd_svm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    amd_apm_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    amd_dump_details( cpu, buffer );
                    buffer  += strlen(buffer);
                    break;
            }
            options++;
        }
    } else {
        printf( "Unknown Vendor Idenfication \n" );
    }
}

static const char *amd_features_ecx[32] = {
    "SSE3",         "RESERVED", "RESERVED", "MONITOR",      
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "CMPXCHG16B", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "POPCNT",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
};

static const char *amd_extfeatures_ecx[32] = {
    "LAHFSAHF", "CMPLEGACY", "SVM", "EXTAPICSPACE",
    "ALTMOVCR8", "ABM", "SSE4A", "MISALIGNSSE",
    "3DNOWPREFETCH", "OSVW", "RESERVED", "RESERVED",
    "SKINIT", "WDT", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
};

static const char *amd_features_edx[32] = {
    "FPU", "VME", "DE", "PSE", "TSC", "MSR", "PAE", "MCE",
    "CMPXCHG8B", "APIC", "RESERVED", "SYSENTEREXIT", "MTRR", "PGE", "MCA", "CMOV",
    "PAT", "PSE36", "RESERVED", "CLFSH", "RESERVED", "RESERVED", "RESERVED", "MMX",
    "FXSR", "SSE", "SSE2", "RESERVED", "HTT", "RESERVED", "RESERVED", "RESERVED"
};

static const char *amd_extfeatures_edx[32] = {
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "SYSCALLRET",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "NX", "RESERVED", "MMXEXT", "RESERVED",
    "RESERVED", "FFXSR", "PAGE1GB", "RDTSCP",
    "RESERVED", "LM", "3DNOWEXT", "3DNOW"
};

static const char *amd_extfunc6_assc[] = {
    "L2/L3 Disabled", "Direct mapped", "2-way associative", "Invalid associativity",
    "4-way associative", "Invalid associativity", "8-way associative",
    "Invalid associativity", "16-way associative", "Invalid associativity",
    "32-way associative", "48-way associative", "64-way associative",
    "96-way associative", "128-way associative", "fully associative"
};

static const char *amd_apm_edx[32] = {
    "TS", "FID", "VID", "TTP", "TM", "STC", "100MSTEPS", "HWPSTATE",
    "TSCINVARIANT", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
};

static const char *amd_svm_edx[32] = {
    "NP", "LBRVIRT", "SVML", "NRIPS",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
};

static void amd_summary_details( cpuinfo_t cpu, char *buffer )
{
    buffer      += sprintf( buffer, "summary: \n\n" );
    buffer      += sprintf( buffer, "%s, 0x%x functions & 0x%x extended functions \n", 
                                    cpu.vendorstr, cpu.func0.eax, 
                                    cpu.extfunc0.eax );
    buffer      += sprintf( buffer, "\n");
    return;
}

static void amd_dump_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    i;

    buffer      += sprintf( buffer, "Basic Functions :\n" );
    {
        buffer      += sprintf( buffer, "0          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func0.eax, cpu.func0.ebx, cpu.func0.ecx, 
                                         cpu.func0.edx);
    }
    if ( cpu.func0.eax >= 1 ) {
        buffer      += sprintf( buffer, "1          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func1.eax, cpu.func1.ebx, cpu.func1.ecx, 
                                         cpu.func1.edx);
    }
    if ( cpu.func0.eax >= 2 ) {
        buffer      += sprintf( buffer, "2          : Reserved\n");
    }
    if ( cpu.func0.eax >= 3 ) {
        buffer      += sprintf( buffer, "3          : Reserved\n"); 
    }
    if ( cpu.func0.eax >= 4 ) {
        buffer      += sprintf( buffer, "4          : Reserved\n");
    }
    if ( cpu.func0.eax >= 5 ) {
        buffer      += sprintf( buffer, "5          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func5.eax, cpu.func5.ebx, cpu.func5.ecx, 
                                         cpu.func5.edx);
    }
    buffer      += sprintf( buffer, "Extended Functions :\n" );
    {
        buffer      += sprintf( buffer, "0          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc0.eax, cpu.extfunc0.ebx, cpu.extfunc0.ecx, 
                                         cpu.extfunc0.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000001 ) {
        buffer      += sprintf( buffer, "1          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc1.eax, cpu.extfunc1.ebx, cpu.extfunc1.ecx, 
                                         cpu.extfunc1.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000002 ) {
        buffer      += sprintf( buffer, "2          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc2.eax, cpu.extfunc2.ebx, cpu.extfunc2.ecx, 
                                         cpu.extfunc2.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000003 ) {
        buffer      += sprintf( buffer, "3          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc3.eax, cpu.extfunc3.ebx, cpu.extfunc3.ecx, 
                                         cpu.extfunc3.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000004 ) {
        buffer      += sprintf( buffer, "4          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc4.eax, cpu.extfunc4.ebx, cpu.extfunc4.ecx, 
                                         cpu.extfunc4.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000005 ) {
        buffer      += sprintf( buffer, "5          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc5.eax, cpu.extfunc5.ebx, cpu.extfunc5.ecx, 
                                         cpu.extfunc5.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000006 ) {
        buffer      += sprintf( buffer, "6          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc6.eax, cpu.extfunc6.ebx, cpu.extfunc6.ecx, 
                                         cpu.extfunc6.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000007 ) {
        buffer      += sprintf( buffer, "7          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc7.eax, cpu.extfunc7.ebx, cpu.extfunc7.ecx, 
                                         cpu.extfunc7.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000008 ) {
        buffer      += sprintf( buffer, "8          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc8.eax, cpu.extfunc8.ebx, cpu.extfunc8.ecx, 
                                         cpu.extfunc8.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000009 ) {
        buffer      += sprintf( buffer, "9          : Reserved\n");
    }
    if ( cpu.extfunc0.eax >= 0x8000000A ) {
        buffer      += sprintf( buffer, "0xA        : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfuncA.eax, cpu.extfuncA.ebx, cpu.extfuncA.ecx, 
                                         cpu.extfuncA.edx);
    }
    if ( cpu.extfunc0.eax >= 0x80000019 ) {
        buffer      += sprintf( buffer, "0xA-0x1B   : Reserved\n");
        buffer      += sprintf( buffer, "0x19       : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc19.eax, cpu.extfunc19.ebx, cpu.extfunc19.ecx, 
                                         cpu.extfunc19.edx);
    }
    if ( cpu.extfunc0.eax >= 0x8000001A ) {
        buffer      += sprintf( buffer, "0x1A       : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc1A.eax, cpu.extfunc1A.ebx, cpu.extfunc1A.ecx, 
                                         cpu.extfunc1A.edx);
    }
    buffer      += sprintf( buffer, "\n");
    return;
}

static void amd_cpu_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t    i;

    buffer      += sprintf(buffer, "cpu details :\n\n");

    /* function 1 */
    if ( cpu.func0.eax >= 1 ) {
        eax         =  cpu.func1.eax;
        buffer      += sprintf( buffer, "family %d  model %d stepping %d ", 
                                         AMD_FAMILY(eax), AMD_MODEL(eax), AMD_STEPPING(eax) );
        ebx         =  cpu.func1.ebx;
        buffer      += sprintf( buffer, "brand-id %d clflush %d cpu-count %d apic-id %d \n",
                                         AMD_BRANDID(ebx), AMD_CLFLUSH(ebx) * 8, AMD_CPUCOUNT(ebx),
                                         AMD_APICID(ebx) );
        ecx         =  cpu.func1.ecx;
        for ( i = 0 ; i < 32 ; i++) {
            if ( strncmp( amd_features_ecx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( ecx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_features_ecx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
        edx         =  cpu.func1.edx;
        for ( i = 0 ; i < 16 ; i++) {
            if ( strncmp( amd_features_edx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_features_edx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
        for ( i = 16 ; i < 32 ; i++) {
            if ( strncmp( amd_features_edx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_features_edx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
    }
    /* function 5 */
    if ( cpu.func0.eax >= 5 ) {
        buffer  += sprintf( buffer, "MonLineSizeMin %d MonLineSizeMax %d ", 
                                     AMD_MLINEMIN(cpu.func5.eax), AMD_MLINEMIN(cpu.func5.ebx) );
        if ( AMD_EMX(cpu.func5.ecx) ) {
            buffer  += sprintf( buffer, "EMX ");
        }
        if ( AMD_IBE(cpu.func5.ecx) ) {
            buffer  += sprintf( buffer, "IBE ");
        }
        buffer  += sprintf( buffer, "\n");
    }
    /* function 0x80000001 */
    if ( cpu.extfunc0.eax >= 0x80000001 ) {
        /* FIXME : Interpretation of PkgID and BrandID */
        ecx         =  cpu.extfunc1.ecx;
        for ( i = 0 ; i < 32 ; i++) {
            if ( strncmp( amd_extfeatures_ecx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( ecx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_extfeatures_ecx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
        edx         =  cpu.extfunc1.edx;
        for ( i = 0 ; i < 32 ; i++) {
            if ( strncmp( amd_extfeatures_edx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_extfeatures_edx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
    }
    /* function 0x80000008 */
    if ( cpu.extfunc0.eax >= 0x80000008 ) {
        uint8_t ncores = 0;

        eax     =  cpu.extfunc8.eax;
        buffer  += sprintf( buffer, "LASize %d PASize %d ", AMD_LAS(eax), AMD_PAS(eax) );
        ecx     =  cpu.extfunc8.ecx;
        /* FIXME : The calculation of number of cores has to be re-looked */
        if ( AMD_APIC_CID_SIZE(ecx) ) {
            ncores  = 1 << AMD_APIC_CID_SIZE(ecx);
        } else {
            ncores  = AMD_NCORES(ecx) + 1;  
        }
        buffer  += sprintf( buffer, "Number of cores %d (func8 vals %d / %d) \n", 
                                     ncores, AMD_NCORES(ecx), AMD_APIC_CID_SIZE(ecx) );
    }
    /* function 0x8000001A */
    if ( cpu.extfunc0.eax >= 0x8000001A ) {
        if ( AMD_FP128( cpu.extfunc1A.eax ) ) {
            buffer  += sprintf( buffer, "FP128 ");
        }
        if ( AMD_MOVU( cpu.extfunc1A.eax ) ) {
            buffer  += sprintf( buffer, "MOVU");
        }
        buffer  += sprintf( buffer, "\n");
    }
    buffer      += sprintf( buffer, "\n");
    return;
}

static void amd_memory_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;

    buffer      += sprintf( buffer, "memory : \n\n");
    /* function 0x80000005 */
    if ( cpu.extfunc0.eax >= 0x80000005 ) {
        eax     =  cpu.extfunc5.eax;
        buffer  += sprintf( buffer, "%d 2M entries in ", AMD_L1_ITLB_SIZE(eax) );
        switch ( AMD_L1_ITLB_ASSC(eax) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_ITLB_ASSC(eax) );
                break;
        }
        buffer  += sprintf( buffer, "L1 Instruction TLB \n" );
        buffer  += sprintf( buffer, "%d 2M entries in ", AMD_L1_DTLB_SIZE(eax) );
        switch ( AMD_L1_DTLB_ASSC(eax) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_DTLB_ASSC(eax) );
                break;
        }
        buffer  += sprintf( buffer, "L1 Data TLB \n" );

        ebx     =  cpu.extfunc5.ebx;
        buffer  += sprintf( buffer, "%d 4K entries in ", AMD_L1_ITLB_SIZE(ebx) );
        switch ( AMD_L1_ITLB_ASSC(ebx) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_ITLB_ASSC(ebx) );
                break;
        }
        buffer  += sprintf( buffer, "L1 Instruction TLB \n" );
        buffer  += sprintf( buffer, "%d 4K entries in ", AMD_L1_DTLB_SIZE(ebx) );
        switch ( AMD_L1_DTLB_ASSC(ebx) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_DTLB_ASSC(ebx) );
                break;
        }
        buffer  += sprintf( buffer, "L1 Data TLB \n" );

        ecx     =  cpu.extfunc5.ecx;
        buffer  += sprintf( buffer, "%d KB in %d byte lines (%d lines per tag) of ",
                                     AMD_L1_CACHE_SIZE(ecx), AMD_L1_CACHE_LS(ecx),
                                     AMD_L1_CACHE_LPT(ecx) );
        switch ( AMD_L1_CACHE_ASSC(ecx) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_CACHE_ASSC(ebx) );
                break;
        }
        buffer  += sprintf( buffer, "L1 DCache \n");

        edx     =  cpu.extfunc5.edx;
        buffer  += sprintf( buffer, "%d KB in %d byte lines (%d lines per tag) of ",
                                     AMD_L1_CACHE_SIZE(edx), AMD_L1_CACHE_LS(edx),
                                     AMD_L1_CACHE_LPT(edx) );
        switch ( AMD_L1_CACHE_ASSC(edx) ) {
            case 0 :
                buffer += sprintf( buffer, "Reserved ");
                break;
            case 1 :
                buffer += sprintf( buffer, "Direct Mapped ");
                break;
            case 0xFF :
                buffer += sprintf( buffer, "Fully associative ");
                break;
            default :
                buffer += sprintf( buffer, "%d way associative ", AMD_L1_CACHE_ASSC(ebx) );
                break;
        }
        buffer  += sprintf( buffer, "L1 ICache \n");
    }

    /* function 6 */
    if ( cpu.extfunc0.eax >= 0x80000006 ) {
        eax     =  cpu.extfunc6.eax;
        buffer  += sprintf( buffer, "%d 2M entries in ", AMD_L2_ITLB_SIZE(eax) );
        buffer  += sprintf( buffer, "%s ", amd_extfunc6_assc[AMD_L2_ITLB_ASSC(eax)] );
        if ( AMD_L2_DTLB_SIZE(eax) || AMD_L2_DTLB_ASSC(eax) ) {
            buffer  += sprintf( buffer, "L2 Instruction TLB \n" );
            ebx     =  cpu.extfunc6.ebx;
            buffer  += sprintf( buffer, "%d 2M entries in ", AMD_L2_DTLB_SIZE(ebx) );
            buffer  += sprintf( buffer, "%s ", amd_extfunc6_assc[AMD_L2_DTLB_ASSC(ebx)] );
            buffer  += sprintf( buffer, "L2 Data TLB \n" );
        } else {
            buffer  += sprintf( buffer, "L2 Unified TLB \n" );
        }
        ebx     =  cpu.extfunc6.ebx;
        buffer  += sprintf( buffer, "%d 4K entries in ", AMD_L2_ITLB_SIZE(ebx) );
        buffer  += sprintf( buffer, "%s ", amd_extfunc6_assc[AMD_L2_ITLB_ASSC(ebx)] );
        if ( AMD_L2_DTLB_SIZE(ebx) || AMD_L2_DTLB_ASSC(ebx) ) {
            buffer  += sprintf( buffer, "L2 Instruction TLB \n" );
            ebx     =  cpu.extfunc6.ebx;
            buffer  += sprintf( buffer, "%d 4K entries in ", AMD_L2_DTLB_SIZE(ebx) );
            buffer  += sprintf( buffer, "%s ", amd_extfunc6_assc[AMD_L2_DTLB_ASSC(ebx)] );
            buffer  += sprintf( buffer, "L2 Data TLB \n" );
        } else {
            buffer  += sprintf( buffer, "L2 Unified TLB \n" );
        }
        ecx     = cpu.extfunc6.ecx;
        buffer  += sprintf( buffer, "%d KB in %d byte lines (%d lines per tag) of ",
                                     AMD_L2_CACHE_SIZE(ecx), AMD_L2_CACHE_LS(ecx),
                                     AMD_L2_CACHE_LPT(ecx) );
        buffer  += sprintf( buffer, "%s L2 Cache \n", amd_extfunc6_assc[AMD_L2_CACHE_ASSC(ecx)] );

        edx     = cpu.extfunc6.edx;
        buffer  += sprintf( buffer, "%d KB in %d byte lines (%d lines per tag) of ",
                                     AMD_L3_CACHE_SIZE(edx), AMD_L3_CACHE_LS(edx),
                                     AMD_L3_CACHE_LPT(edx) );
        buffer  += sprintf( buffer, "%s L3 Cache \n", amd_extfunc6_assc[AMD_L3_CACHE_ASSC(edx)] );
    }

    /* function 0x19 */
    if ( cpu.extfunc0.eax >= 0x80000019 ) {
        eax     =  cpu.extfunc1A.eax;    
        buffer  += sprintf( buffer, "%d 1G entries in ", AMD_L2_ITLB_SIZE(eax) );
        buffer  += sprintf( buffer, "%s L1 Instruction TLB", amd_extfunc6_assc[AMD_L2_ITLB_ASSC(eax)] );
        buffer  += sprintf( buffer, "%d 1G entries in ", AMD_L2_DTLB_SIZE(eax) );
        buffer  += sprintf( buffer, "%s L1 Data TLB", amd_extfunc6_assc[AMD_L2_DTLB_ASSC(eax)] );
        ebx     =  cpu.extfunc1A.ebx;    
        buffer  += sprintf( buffer, "%d 1G entries in ", AMD_L2_ITLB_SIZE(ebx) );
        buffer  += sprintf( buffer, "%s L2 Instruction TLB", amd_extfunc6_assc[AMD_L2_ITLB_ASSC(ebx)] );
        buffer  += sprintf( buffer, "%d 1G entries in ", AMD_L2_DTLB_SIZE(ebx) );
        buffer  += sprintf( buffer, "%s L2 Data TLB", amd_extfunc6_assc[AMD_L2_DTLB_ASSC(ebx)] );
    }
    buffer      += sprintf( buffer, "\n");
    return;
}

static void amd_svm_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t     i;

    buffer      += sprintf( buffer, "svm details: \n\n");
    /* function 0x80000009 */
    if ( cpu.extfunc0.eax >= 0x80000009 ) {
        eax     = cpu.extfuncA.eax;
        buffer  += sprintf( buffer, "Revision %x ", AMD_SVMREV(eax) );
        buffer  += sprintf( buffer, "%d address space identifiers \n", cpu.extfuncA.ebx);
        edx     = cpu.extfuncA.edx;
        for ( i = 0 ; i < 32 ; i++ ) {
            if ( strncmp( amd_svm_edx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_extfeatures_edx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n");
    }
    return;
}

static void amd_apm_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t     i;

    buffer      += sprintf( buffer, "apm details: \n\n");
    /* function 0x80000007 */
    if ( cpu.extfunc0.eax >= 0x80000007 ) {
        edx     = cpu.extfunc7.edx;
        for ( i = 0 ; i < 32 ; i++ ) {
            if ( strncmp( amd_apm_edx[i], "RESERVED", 8 ) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", amd_apm_edx[i] );
            }
        }
        buffer  += sprintf( buffer, "\n\n");
    }
    return;
}

static const char *intel_features_ecx[32] = {
    "SSE3", "RESERVED", "RESERVED", "MONITOR",
    "DS-CPL", "VMX", "SMX", "EST",
    "TM2", "SSSE3", "CNXT-ID", "RESERVED",
    "RESERVED", "CMPXCHG16B", "xTPR", "PDCM",
    "RESERVED", "RESERVED", "RESERVED", "SSE4.1",
    "SSE4.2", "RESERVED", "RESERVED", "POPCNT",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED"
};

static const char *intel_features_edx[32] = {
    "FPU", "VME", "DE", "PSE", "TSC", "MSR", "PAE", "MCE",
    "CX8", "APIC", "RESERVED", "SEP", "MTRR", "PGE", "MCA", "CMOV",
    "PAT", "PSE-36", "PSN", "CLFSH", "RESERVED", "DS", "ACPI", "MMX",
    "FXSR", "SSE", "SSE2", "SS", "HTT", "TM", "RESERVED", "PBE"
};

static const char *intel_cache_type[32] = {
    "null",
    "Data",
    "Instr.",
    "Unified",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED"
};

static const char *intel_config_desc[256] = {
    "Null descriptor",
    "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries",
    "Instruction TLB: 4 MByte pages, 4-way set associative, 2 entries",
    "Data TLB: 4 KByte pages, 4-way set associative, 64 entries",
    "Data TLB: 4 MByte pages, 4-way set associative, 8 entries",
    "Data TLB1: 4 MByte pages, 4-way set associative, 32 entries",
    "L1 instruction cache: 8 KBytes, 4-way set associative, 32 byte line size",
    "Invalid configuration",
    "L1 instruction cache: 16 KBytes, 4-way set associative, 32 byte line size",
    "Invalid configuration",
    "L1 data cache: 8 KBytes, 2-way set associative, 32 byte line size",
    "Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries",
    "L1 data cache: 16 KBytes, 4-way set associative, 32 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "L3 cache: 512 KB, 4-way set assoc., 64 byte line size, 2 lines per sector",
    "L3 cache: 1 MB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "Invalid configuration",
    "L3 cache: 2 MB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "L3 cache: 4 MB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "Invalid configuration", "Invalid configuration",
    "L1 data cache: 32 KBytes, 8-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "L1 instruction cache: 32 KBytes, 8-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "No L2 cache or, if processor contains a valid L2 cache, no L3 cache",
    "L2 cache: 128 KBytes, 4-way set associative, 32 byte line size",
    "L2 cache: 256 KBytes, 4-way set associative, 32 byte line size",
    "L2 cache: 512 KBytes, 4-way set associative, 32 byte line size",
    "L2 cache: 1 MByte, 4-way set associative, 32 byte line size",
    "L2 cache: 2 MByte, 4-way set associative, 32 byte line size",
    "L3 cache: 4 MByte, 4-way set associative, 64 byte line size",
    "L3 cache: 8 MByte, 8-way set associative, 64 byte line size",
    "Invalid configuration",
    "L2 cache: 4 MByte, 16-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries",
    "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries",
    "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Data TLB0: 4 MByte pages, 4-way set associative, 16 entries",
    "Data TLB0: 4 KByte pages, 4-way associative, 16 entries",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Data TLB: 4 KByte and 4 MByte pages, 64 entries",
    "Data TLB: 4 KByte and 4 MByte pages,128 entries",
    "Data TLB: 4 KByte and 4 MByte pages,256 entries",
    "Invalid configuration", "Invalid configuration",
    "L1 data cache: 16 KByte, 8-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration",
    "L1 data cache: 8 KByte, 4-way set associative, 64 byte line size",
    "L1 data cache: 16 KByte, 4-way set associative, 64 byte line size",
    "L1 data cache: 32 KByte, 4-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration",
    "Trace cache: 12 K-μop, 8-way set associative",
    "Trace cache: 16 K-μop, 8-way set associative",
    "Trace cache: 32 K-μop, 8-way set associative",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration",
    "L2 cache: 1 MByte, 4-way set associative, 64byte line size",
    "L2 cache: 128 KB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "L2 cache: 256 KB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "L2 cache: 512 KB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "L2 cache: 1 MB, 8-way set assoc., 64 byte line size, 2 lines per sector",
    "L2 cache: 2 MB, 8-way set assoc., 64byte line size",
    "Invalid configuration",
    "L2 cache: 512 KByte, 2-way set associative, 64-byte line size",
    "Invalid configuration", "Invalid configuration",
    "L2 cache: 256 KByte, 8-way set associative, 32 byte line size",
    "L2 cache: 512 KByte, 8-way set associative, 32 byte line size",
    "L2 cache: 1 MByte, 8-way set associative, 32 byte line size",
    "L2 cache: 2 MByte, 8-way set associative, 32 byte line size",
    "L2 cache: 512 KByte, 4-way set associative, 64 byte line size",
    "L2 cache: 1 MByte, 8-way set associative, 64 byte line size",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration",
    "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries",
    "Invalid configuration", "Invalid configuration",
    "Data TLB: 4 KByte pages, 4-way set associative, 128 entries",
    "Data TLB1: 4 KByte pages, 4-way associative, 256 entries",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration",
    "64-Byte prefetching",
    "128-Byte prefetching",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration", "Invalid configuration",
    "Invalid configuration", "Invalid configuration"
};

static const char * intel_perf_events [] = {
    "CORE-CYCLE",
    "INSTR-RETIRED",
    "REF-CYCLES",
    "LAST-LEVEL-CACHE-REF",
    "LAST-LEVEL-CACHE-MISS",
    "BR-RETIRED",
    "BRMISS-RETIRED"
};

static void intel_summary_details( cpuinfo_t cpu, char *buffer )
{
    buffer      += sprintf( buffer, "summary: \n\n" );
    buffer      += sprintf( buffer, "%s, 0x%x functions & 0x%x extended functions \n", 
                                    cpu.vendorstr, cpu.func0.eax, 
                                    cpu.extfunc0.eax );
    buffer      += sprintf( buffer, "\n");
    return;
}

static void intel_dump_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    i;
    uint8_t     *config;

    if (( cpu.func0.eax & 0xFFFFFF00 ) == 0x00000500 ) {     /* pre-B0 P5 procs */
        buffer  += sprintf( buffer, "Pre-BO step p5 Processor \n" );
        return;
    }

    buffer      += sprintf( buffer, "Basic Functions :\n" );
    buffer      += sprintf( buffer, "0          : ");
    buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                     cpu.func0.eax, cpu.func0.ebx, cpu.func0.ecx, 
                                     cpu.func0.edx);
    if ( cpu.func0.eax >= 1) {
        buffer      += sprintf( buffer, "1          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func1.eax, cpu.func1.ebx, cpu.func1.ecx, 
                                         cpu.func1.edx);
    }
    if ( cpu.func0.eax >= 2) {
        buffer      += sprintf( buffer, "2 (Configs): ");
        for ( i = 0 ; i < config[0] ; i++ ) {
            buffer  += sprintf( buffer, "%x ", cpu.configs[i]);
        }
        buffer      += sprintf( buffer, "\n");
    }
    if ( cpu.func0.eax >= 3) {
        buffer      += sprintf( buffer, "3          : Reserved ");
    }
    if ( cpu.func0.eax >= 4) {
        i           = 0;
        while ( cpu.func4[i].eax & 0xF ) {
            buffer  += sprintf( buffer, "4 cache %2d : ", i );
            buffer  += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                             cpu.func4[i].eax, cpu.func4[i].ebx, cpu.func4[i].ecx, 
                                             cpu.func4[i].edx);
            i++;
        }
    }
    if ( cpu.func0.eax >= 5) {
        buffer      += sprintf( buffer, "5          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func5.eax, cpu.func5.ebx, cpu.func5.ecx, 
                                         cpu.func5.edx);
    }
    if ( cpu.func0.eax >= 6) {
        buffer      += sprintf( buffer, "6          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.func6.eax, cpu.func6.ebx, cpu.func6.ecx, 
                                         cpu.func6.edx);
    }
    if ( cpu.func0.eax >= 0xA) {
        buffer      += sprintf( buffer, "0xA        : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.funcA.eax, cpu.funcA.ebx, cpu.funcA.ecx, 
                                         cpu.funcA.edx);
    }

    buffer      += sprintf( buffer, "0          : ");
    buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                     cpu.extfunc0.eax, cpu.extfunc0.ebx, cpu.extfunc0.ecx, 
                                     cpu.extfunc0.edx);
    if ( cpu.extfunc0.eax >= 1) {
        buffer      += sprintf( buffer, "1          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc1.eax, cpu.extfunc1.ebx, cpu.extfunc1.ecx, 
                                         cpu.extfunc1.edx);
    }
    if ( cpu.extfunc0.eax >= 2) {
        buffer      += sprintf( buffer, "2          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc2.eax, cpu.extfunc2.ebx, cpu.extfunc2.ecx, 
                                         cpu.extfunc2.edx);
    }
    if ( cpu.extfunc0.eax >= 3) {
        buffer      += sprintf( buffer, "3          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc3.eax, cpu.extfunc3.ebx, cpu.extfunc3.ecx, 
                                         cpu.extfunc3.edx);
    }
    if ( cpu.extfunc0.eax >= 4) {
        buffer      += sprintf( buffer, "4          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc4.eax, cpu.extfunc4.ebx, cpu.extfunc4.ecx, 
                                         cpu.extfunc4.edx);
    }
    if ( cpu.extfunc0.eax >= 5) {
        buffer      += sprintf( buffer, "5          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc5.eax, cpu.extfunc5.ebx, cpu.extfunc5.ecx, 
                                         cpu.extfunc5.edx);
    }
    if ( cpu.extfunc0.eax >= 6) {
        buffer      += sprintf( buffer, "6          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc6.eax, cpu.extfunc6.ebx, cpu.extfunc6.ecx, 
                                         cpu.extfunc6.edx);
    }
    if ( cpu.extfunc0.eax >= 7) {
        buffer      += sprintf( buffer, "7          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc7.eax, cpu.extfunc7.ebx, cpu.extfunc7.ecx, 
                                         cpu.extfunc7.edx);
    }
    if ( cpu.extfunc0.eax >= 8) {
        buffer      += sprintf( buffer, "8          : ");
        buffer      += sprintf( buffer, "(eax) %08x (ebx) %08x (ecx) %08x (edx) %08x \n",
                                         cpu.extfunc8.eax, cpu.extfunc8.ebx, cpu.extfunc8.ecx, 
                                         cpu.extfunc8.edx);
    }
    buffer      += sprintf( buffer, "\n");
    return;
}

static void intel_cpu_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t    i;

    buffer      += sprintf( buffer, "cpu details : \n" );

    /* function 1 */
    if ( cpu.func0.eax >= 1 ) {
        eax     =  cpu.func1.eax;
        buffer  += sprintf( buffer, "family %d model %d stepping %d processor ID %d \n",
                                     INTEL_FAMILY(eax), INTEL_MODEL(eax), INTEL_STEPPING(eax),
                                     INTEL_CPUID(eax) );
        ebx     =  cpu.func1.ebx;
        buffer  += sprintf( buffer, "brand-id %d clflush %d cpu-count %d inital apic-id %d \n",
                                     INTEL_BRANDID(ebx), INTEL_CLFLUSH(ebx), INTEL_CPUCOUNT(ebx),
                                     INTEL_APICID(ebx) );
        ecx     =  cpu.func1.ecx;
        for ( i  = 0 ; i < 32 ; i++ ) {
            if ( strncmp( intel_features_ecx[i], "RESERVED", 8) == 0 ) {
                continue;
            }
            if ( ecx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", intel_features_ecx[i] );
            }
        }
        buffer      += sprintf( buffer, "\n" );
        edx         =  cpu.func1.edx;
        for ( i  = 0 ; i < 16 ; i++ ) {
            if ( strncmp( intel_features_edx[i], "RESERVED", 8) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", intel_features_edx[i] );
            }
        }
        buffer      += sprintf( buffer, "\n" );
        for ( i  = 16 ; i < 32 ; i++ ) {
            if ( strncmp( intel_features_edx[i], "RESERVED", 8) == 0 ) {
                continue;
            }
            if ( edx & ( 1 << i ) ) {
                buffer  += sprintf( buffer, "%s ", intel_features_edx[i] );
            }
        }
        buffer      += sprintf( buffer, "\n" );
    }

    /* function 5 */
    if ( cpu.func0.eax >= 5 ) {
        buffer      += sprintf( buffer, "monitor line size %d-%d ", 
                                     cpu.func5.eax & 0xFFFF,
                                     cpu.func5.ebx & 0xFFFF );
        if ( cpu.func5.ecx & 1 ) {
            buffer  += sprintf( buffer, "Enumeration of MMWAIT " );
        }
        if ( cpu.func5.ecx & 2 ) {
            buffer  += sprintf( buffer, "MWAIT break events " );
        }
        edx         =  cpu.func5.edx;
        buffer      += sprintf( buffer, "C0-%d C1-%d C2-%d C3-%d C4-%d\n",
                                         INTEL_C0(edx), INTEL_C1(edx), INTEL_C2(edx),
                                         INTEL_C3(edx), INTEL_C4(edx) );
    }

    buffer      += sprintf( buffer, "\n" );

    buffer      += sprintf( buffer, "Architectural perfomance monitoring : \n" );
    
    /* function 0xA */
    if ( cpu.func0.eax >= 0xA ) {
        eax     =  cpu.funcA.eax;    
        buffer  += sprintf( buffer, "version %d, %d bit wide %d perf-counter per \
                                     logical processor (%d events)\n", 
                                     INTEL_PERF_VER(eax), INTEL_PERF_BW(eax), 
                                     INTEL_PERF_COUNT(eax), INTEL_PERF_LENEBX(eax) );
        for ( i = 0 ; i < 7 ; i++ ) {
            if ( cpu.funcA.ebx & 1 << i ) {
                buffer  += sprintf( buffer, "%s", intel_perf_events[i] );
            }
        }
        edx     =  cpu.funcA.edx;
        buffer  += sprintf( buffer, "%d bit wide %d fixed function performance counters \n",
                                     INTEL_PERF_FFCNT(edx), INTEL_PERF_FFBW(edx) );
    }

    /* function 0x80000001 */
    if ( cpu.extfunc0.eax >= 0x80000001 ) {
        if ( cpu.extfunc1.ecx & 1 ) {
            buffer  += sprintf( buffer, "LAHF/SAHF in 64-bit mode, ");
        }
        if ( cpu.extfunc1.edx & 0x800 ) {
            buffer  += sprintf( buffer, "SYSCALL/SYSRET, ");
        }
        if ( cpu.extfunc1.edx & 0x100000 ) {
            buffer  += sprintf( buffer, "Execute disable bit, ");
        }
        if ( cpu.extfunc1.edx & 0x20000000 ) {
            buffer  += sprintf( buffer, "Intel 64");
        }
        buffer  += sprintf( buffer, "\n");
    }
    buffer      += sprintf( buffer, "\n" );
    return;
}

static void intel_memory_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t    i;

    buffer      += sprintf(buffer, "memory details :\n");
    /* function 2 */
    if ( cpu.func0.eax >= 2 ) {
        for ( i = 1 ; i < MAX_CONFIGS ; i++ ) {
            buffer  += sprintf( buffer, "%s\n", intel_config_desc[cpu.configs[i]] );
            if ( cpu.configs[i] == 0 ) {
                break;
            }
        }
    }
    /* function 4 */
    if ( cpu.func0.eax >= 4 ) {
        for ( i = 0 ; i < MAX_CACHES ; i++ ) {
            eax     =  cpu.func4[i].eax;
            if ( ( eax & 0xF ) == 0 ) {
                break;
            }
            buffer  += sprintf( buffer, "%s cache-level %d max-threads %d max-cores %d ",
                                         intel_cache_type[INTEL_CACHETYPE(eax)], 
                                         INTEL_CACHELEVEL(eax),
                                         INTEL_MAXTHREADS(eax) + 1, INTEL_MAXCORES(eax) + 1 );
            buffer  += sprintf( buffer, "(" );
            if ( INTEL_SELFINIT(eax) ) {
                buffer  += sprintf( buffer, "SI " );
            }
            if ( INTEL_FULLASSC(eax) ) {
                buffer  += sprintf( buffer, "FA " );
            }
            if ( INTEL_WBINVALIDATE(eax) ) {
                buffer  += sprintf( buffer, "WBI " );
            }
            if ( INTEL_INCLUSIVE(eax) ) {
                buffer  += sprintf( buffer, "INC " );
            }
            buffer  += sprintf( buffer, ") " );
            ebx     =  cpu.func4[i].ebx;
            buffer  += sprintf( buffer, "L-%d P-%d W-%d S-%d \n", INTEL_L(ebx) + 1,
                                         INTEL_P(ebx) + 1, INTEL_W(ebx) + 1, 
                                         cpu.func4[i].ecx + 1 );
        }
    }
    /* function 0x80000006 */
    if ( cpu.extfunc0.eax >= 0x80000006 ) {
        buffer  += sprintf( buffer, "%d KB of ", ( cpu.extfunc6.ecx & 0xFFFF0000 ) >> 16 );
        switch (( cpu.extfunc6.ecx & 0xF000 ) >> 8 )  {
            case 0 :
                buffer  += sprintf( buffer, "Disabled " );
                break;
            case 1 :
                buffer  += sprintf( buffer, "Direct mapped " );
                break;
            case 2 :
                buffer  += sprintf( buffer, "2-way assoc. " );
                break;
            case 4 :
                buffer  += sprintf( buffer, "4-way assoc. " );
                break;
            case 6 :
                buffer  += sprintf( buffer, "8-way assoc. " );
                break;
            case 8 :
                buffer  += sprintf( buffer, "16-way assoc. " );
                break;
            default :
                buffer  += sprintf( buffer, "fully assoc. " );
                break;
        } 
        buffer  += sprintf( buffer, "Cache with %d byte line size \n",
                                     cpu.extfunc6.ecx & 0xFF );
    }
    /* function 0x80000008 */
    if ( cpu.extfunc0.eax >= 0x80000008 ) {
        buffer  += sprintf( buffer, "PAS %d LAS %d \n", cpu.extfunc8.eax & 0xFF,
                                     ( cpu.extfunc8.eax & 0xFF00 ) >> 8 );
    }

    buffer      += sprintf( buffer, "\n");
    return;
}

static void intel_svm_details( cpuinfo_t cpu, char *buffer )
{
    buffer      += sprintf( buffer, "\n");
    return;
}

static void intel_apm_details( cpuinfo_t cpu, char *buffer )
{
    uint32_t    eax, ebx, ecx, edx;
    uint32_t    i;

    buffer      += sprintf( buffer, "apm details:\n" );
    /* function 6 */
    if ( cpu.func0.eax >= 6) {
        if ( cpu.func6.eax & 1 ) {
            buffer      += sprintf( buffer, "Digital-temperature with %d interrupt thresholds, ",
                                            cpu.func6.ebx & 0xF );
        }
        if ( cpu.func6.eax & 2 ) {
            buffer      += sprintf( buffer, "Dynamic-acceleration " );
        }
        if ( cpu.func6.ecx & 1 ) {
            buffer      += sprintf( buffer, "MCNT/ACNT MSRs available\n" );
        }
    }

    buffer      += sprintf( buffer, "\n");
    return;
}
