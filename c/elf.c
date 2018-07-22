#include <bfd.h>
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <libiberty.h>

#define true    1
#define false   0

typedef unsigned int bool;

static asymbol **isympp = NULL;	/* Input symbols.  */
static asymbol **osympp = NULL;	/* Output symbols that survive stripping.  */

/* Create a section in OBFD with the same
   name and attributes as ISECTION in IBFD.  */

static void
setup_section( bfd *ibfd, sec_ptr isection, void *obfdarg )
{
    bfd                 *obfd = obfdarg;
    struct section_list *p;
    sec_ptr             osection;
    bfd_size_type       size;
    bfd_vma             vma;
    bfd_vma             lma;
    flagword            flags;
    const char          *err;
    const char          *name;
    char                *prefix = NULL;

    printf("section name %s \n", isection->name);
    osection = bfd_make_section_anyway( obfd, isection->name);
    if ( osection == NULL ) {
        bfd_perror( "while making section with flags" );
        goto loser;
    }
    if ( !bfd_set_section_flags( obfd, osection, isection->flags )) {
        bfd_perror( "while setting section flag" );
    }
    //elf_section_type( osection ) = elf_section_type( isection );

    size    = bfd_section_size( ibfd, isection );
    if ( !bfd_set_section_size( obfd, osection, size )) {
        bfd_perror( "while setting section size" );
        goto loser;
    }

    vma     = bfd_section_vma( ibfd, isection );
    if ( !bfd_set_section_vma( obfd, osection, vma )) {
        bfd_perror( "while settting section vma" );
        goto loser;
    }
    lma     = isection->lma;
    osection->lma   = lma;
    printf("address vma %x lma %x \n", vma, lma);

    /* Copy merge entity size.  */
    osection->entsize = isection->entsize;

    /* This used to be mangle_section; we do here to avoid using
       bfd_get_section_by_name since some formats allow multiple
       sections with the same name.  */
    isection->output_section    = osection;
    isection->output_offset     = 0;
    bfd_set_section_alignment( obfd, osection, bfd_get_section_alignment( ibfd, isection ));
    /* make a program header for the corresponding section */
    //bfd_record_phdr( obfd, PT_LOAD, 1, PF_R | PF_W | PF_X, 1, osection->vma, 0, 0, 1, &osection );
    /* Allow the BFD backend to copy any private data it understands
       from the input section to the output section.  */
    if ( !bfd_copy_private_section_data( ibfd, isection, obfd, osection )) {
        bfd_perror( "while copying private section data" );
        goto loser;
    }
    /* All went well.  */
    return;
loser:
    return;
}

/* Once each of the sections is copied, we may still need to do some
   finalization work for private section headers.  Do that here.  */

static void
setup_bfd_headers( bfd *ibfd, bfd *obfd )
{
    const char *err;

    /* Allow the BFD backend to copy any private data it understands
       from the input section to the output section.  */
    //if ( !bfd_copy_private_header_data( ibfd, obfd )) {
    //    bfd_perror("While copying private header data");
    //}
    /* All went well.  */
    return;
}

/* Copy the data of input section ISECTION of IBFD
   to an output section with the same name in OBFD.
   If stripping then don't copy any relocation info.  */

static void
copy_section( bfd *ibfd, sec_ptr isection, void *obfdarg )
{
    bfd                 *obfd = obfdarg;
    struct section_list *p;
    arelent             **relpp;
    long                relcount;
    sec_ptr             osection;
    bfd_size_type       size;
    long                relsize;
    flagword            flags;

    flags       = bfd_get_section_flags( ibfd, isection );
    osection    = isection->output_section;
    size        = bfd_get_section_size_before_reloc(isection);

    if ( size == 0 || osection == 0 ) {
        return;
    }

    if ( bfd_get_section_flags( ibfd, isection ) & SEC_HAS_CONTENTS && 
         bfd_get_section_flags( obfd, osection ) & SEC_HAS_CONTENTS) {

        void *memhunk = (void *) malloc (size);

        if ( !bfd_get_section_contents( ibfd, isection, memhunk, 0, size )) {
            bfd_perror("While get section contents");
        }
        if ( !bfd_set_section_contents( obfd, osection, memhunk, 0, size )) {
            bfd_perror("While set section contents");
        }

        free (memhunk);
    }
}

static bool copy_object( bfd *ibfd, bfd *obfd )
{
    bool                    rc  = true;
    asection                *asec;
    asection                **osections = NULL;
    asection                *gnu_debuglink_section = NULL;
    asection                 *p;
    bfd_size_type           *gaps = NULL;
    bfd_size_type           max_gap = 0;
    long                    symsize;
    long                    symcount;
    const char              **targets;
    char                    data[1024] = "Hello world";
    enum bfd_architecture   iarch;
    unsigned int            imach;
    char                    *output_target;

    /* BFD mandates that all output sections be created and sizes set before
     * any output is done.  Thus, we traverse all sections multiple times.  
     */
    bfd_map_over_sections( ibfd, setup_section, obfd );
    setup_bfd_headers( ibfd, obfd );
    if ( bfd_count_sections( obfd ) == 0 ) {
        bfd_perror( "there are no sections to be copied!" );
        rc  = false;
    }

    symsize = bfd_get_symtab_upper_bound( ibfd );
    if ( symsize < 0 ) {
        bfd_perror( "While get_symtab_upper_bound" );
        rc  = false;
    }
    osympp  = isympp = malloc( symsize );
    symcount= bfd_canonicalize_symtab( ibfd, isympp );
    if ( symcount < 0 ) {
        bfd_perror( "symcount less than 0" );
        rc  = false;
    }
    bfd_set_symtab( obfd, isympp, symcount );

    return rc;
}

int main (void)
{
    bfd                     *ibfd, *obfd;
    asection                *asec;
    asection                *asec_arr[100000];
    bfd_vma                 start;
    flagword                flags;
    bfd_format              format;
    char                    *secname;
    const char              **targets;
    char                    data[1024] = "Hello world";
    enum bfd_architecture   iarch;
    unsigned int            imach;
    char                    *input_target;
    char                    *output_target;
    int                     i = 100000;

    bfd_init();

    ibfd    = bfd_openr( "./a.out", NULL ); //"elf64-x86-64" );
    if ( ibfd == NULL ) {
        bfd_perror( "while opening a.out" );
        goto loser;
    }
    if (!bfd_check_format( ibfd, bfd_object )) {
        bfd_perror ( "while opening a.out" );
        goto loser;
    }
    else {
	    input_target = bfd_get_target (ibfd);
        obfd    = bfd_openw("./test","elf64-x86-64" );
        if ( obfd == NULL ) {
            bfd_perror ( "while opening test" );
            goto loser;
        }

        format  =  bfd_get_format( ibfd );
        printf( "%d \n", format );
        if ( !bfd_set_format( obfd, format)) {
            bfd_perror( "While setting format" );
            goto loser;
        }
        start = bfd_get_start_address( ibfd );
        if ( !bfd_set_start_address( obfd, start )) {
            bfd_perror( "While setting start address" );
            goto loser;
        }
        flags = bfd_get_file_flags( ibfd );
        if ( !bfd_set_file_flags( obfd, flags )) {
            bfd_perror( "While setting flags" );
            goto loser;
        }
        iarch = bfd_get_arch( ibfd );
        imach = bfd_get_mach( ibfd );
        bfd_set_arch_mach( obfd, iarch, imach);

    }

    if (! copy_object (ibfd, obfd)) {
        printf("Failed Copy_object \n");
    }

    for ( i = 0; i < 7; i++ ) {
        secname = (char *) malloc( sizeof(char) * 256 );
        sprintf( secname, ".dummysec%d", i );
        //printf( "%s \n", secname);
        asec_arr[i]    = bfd_make_section( obfd, secname);
        if ( asec_arr[i] == NULL ) {
            bfd_perror( "while creating section" );
            goto loser;
        }
        if ( bfd_set_section_size( obfd, asec_arr[i], i + 64 ) == FALSE ) {
            bfd_perror( "while setting section size" );
            goto loser;
        }
        asec_arr[i]->output_section    = asec_arr[i];
        asec_arr[i]->output_offset     = 0;
        if ( bfd_set_section_flags( obfd, asec_arr[i], SEC_LOAD | SEC_HAS_CONTENTS | SEC_ALLOC | SEC_DATA ) == FALSE ) {
            bfd_perror( "while setting section flags\n" );
            goto loser;
        }
        if ( !bfd_set_section_vma( obfd, asec_arr[i], 0x600000+(i*100) )) {
            bfd_perror( "set_section_vma" );
            goto loser;
        }
        asec_arr[i]->lma   = 0x600000 + (i*100);
        /* make a program header for the corresponding section */
    }

    if ( !bfd_record_phdr( obfd, PT_LOAD, 1, PF_R | PF_W | PF_X, 1, (bfd_vma) NULL, 0, 0, 7, asec_arr )) {
        bfd_perror( "bfd_record_phdr" );
    }

    for ( i = 0; i < 7; i++ ) {
        if ( !bfd_set_section_contents( obfd, asec_arr[i], data, 0, 32)) {
           bfd_perror( "set_section_contents" );
           goto loser;
        }
    }

    /* This has to happen after the symbol table has been set.  */
    bfd_map_over_sections( ibfd, copy_section, obfd );


    if ( !bfd_copy_private_bfd_data( ibfd, obfd ))  {
        bfd_perror("While copying private bfd data");
    }


    if ( obfd ) {
        if ( !bfd_close( obfd )) {
            bfd_perror ( "while closing obfd" );
            goto loser;
        }
    }
    if ( ibfd ) {
        if (!bfd_close (ibfd)) {
            bfd_perror ( "while closing obfd" );
            goto loser;
        }
    }
loser:
    return 0;
}
