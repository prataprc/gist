#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_RECORD_SIZE     (500)

#define MAX(X,Y)    (((X) > (Y)) ? X : Y)
#define MIN(X,Y)    (((X) > (Y)) ? Y : X)

typedef unsigned long long  ullong;

typedef struct region_struct {
    ullong start;
    ullong end;
    unsigned char   *buffer;
    struct region_struct *next;
} region_t;

/* Global switches */
#define     DUMP_REGIONS    (0)
#define     DEMARCATE_REGIONS    (1)

void dump_regions (region_t *r_base)
{
    region_t *r = r_base;
    int count = 0;
    while (r->next) {
        r = r->next;
        printf ("Region %d: [%x] : [%x]\n", count++, (int) r->start, (int) r->end);
    }
}

region_t * new_region(void)
{
    region_t *r;
    r = malloc (sizeof(region_t));
    if (r != NULL) {
        bzero (r, sizeof (region_t));
    }
    return r;
}

void add_new_region (region_t *r_base, ullong start, ullong end)
{
    region_t *curr= r_base;

    // printf ("Adding new region : %x : %x\n", start, end);
    // dump_regions (r_base);

    while(curr->next) {
        if (curr->next->start > start) {
            break;
        }
        curr = curr->next;
    }
    region_t *r;
    r = new_region();
    r->next = curr->next;
    r->start = start;
    r->end = end;
    curr->next = r;
}

void coalesce_regions (region_t *r_base)
{
    region_t *r = r_base;

    while (r->next) {
        r = r->next;
        if (r->next) {
            if (r->end > r->next->start) {
                printf ("Warning : regions [%lx - %lx] and [%lx - %lx] are clashing!\n",
                        r->start, r->end, r->next->start, r->next->end);
            } else if (r->end == r->next->start) {
                // lets gobble the next region
                printf ("Region [%lx - %lx] gobbling [%x - %lx]\n",
                        r->start, r->end, r->next->start, r->next->end);
                r->end = r->next->end;
                r->next = r->next->next;
                free(r->next);
            }
        }
    }
}

void add_region (region_t *r_base, ullong start, ullong end)
{
    region_t *curr= r_base;
    int overlap = 0, error = 0;

    while(curr->next) {
        curr = curr->next;
        if ((curr->start < start) && (curr->end > start)) {
            overlap = 1;
            error = 1;
            // curr->end = MAX (curr->end, end);
        } else if ((curr->start < end) && (curr->end > end)) {
            overlap = 1;
            error = 1;
            // curr->start = MIN (curr->start, start);
        } else if ((start < curr->start) && (end > curr->end)) {
            overlap = 1;
            error = 1;
            // curr->start = start;
            // curr->end = end;
        } else if ((curr->end == (start - 1)) || (curr->start == (end + 1))) {
            overlap = 1;
            curr->end = MAX (curr->end, end);
            curr->start = MIN (curr->start, start);
        } else if (curr->start > end) {
            break;
        }
    }
    if (overlap) {
        if (error) {
            printf ("Overlap detected while adding region [%lx - %lx]\n", start, end);
            if (DUMP_REGIONS) {
                dump_regions (r_base);
            }
        }
    } else {
        add_new_region (r_base, start, end);
    }
    coalesce_regions(r_base);
}

region_t *find_region(region_t *r_base, ullong address)
{
    region_t *r;
    r = r_base;

    while (r->next) {
        r = r->next;
        if ((r->start <= address) && (r->end >= address)) {
            return r;
        }
    }
    //printf ("Couldn't find address:%lx\n", address);
    return NULL;
}

void parse_and_gen (FILE *fp_in, FILE *fp_out, int gen_p, region_t *r_base)
{
    char in_buffer[MAX_RECORD_SIZE];
    int line_count = 0, num_bytes;
    ullong address, rel_address, min_address = -1, max_address = 0;
    unsigned char *out_buffer = NULL;

    rewind (fp_in);

    while (!feof(fp_in)) {
        if (fgets (in_buffer, MAX_RECORD_SIZE, fp_in) != NULL) {

            // printf ("Recvd line : \'%s\'\n", in_buffer);

            if (toupper(in_buffer[0]) != 'S') {
                if (!gen_p) printf ("[%d] : Line can't be decoded\n", line_count);
            } else {
                switch (in_buffer[1]) {
                case '3':
                    sscanf(&in_buffer[2], "%2x", &num_bytes);
                    num_bytes-=5;

                    // get address
                    sscanf (&in_buffer[4], "%8llx", &address);
                    // printf ("%d : %08llx : %d\n", line_count, address, num_bytes);

                    if (gen_p) {
                        int i;
                        int temp;
                        region_t *r;
                        ullong offset;

                        r = find_region(r_base, address);
                        if (r == NULL) {
                            /* Ok to get NULL region, if number of bytes is zero */
                            assert(num_bytes == 0);
                        } else {
                            offset = address - r->start;

                            for (i = 0; i < num_bytes; i++) {
                                sscanf (&in_buffer[12 + i*2], "%2x", &temp);
                                r->buffer[offset + i] = temp;
                            }
                        }
                    } else {
                        add_region(r_base, address, address + num_bytes - 1);
                    }
                    break;
                case '0':
                case '1':
                case '2':
                case '4':
                case '5':
                case '6':
                case '7':
                    printf ("[%d] : S%d record encountered. Ignoring...\n", line_count, (in_buffer[1] - '0'));
                    break;
                default:
                    printf ("[%d] : Unknown record type\n", line_count);
                    break;
                }
            }
            line_count++;
        }
    }
    if (gen_p) {
#if 0
        for (address = 0; address < (*a_max_address - *a_min_address); address++) {
            fprintf (fp_out, "%08x : %02x\n", *a_min_address + address, out_buffer[address]);
        }
#endif
    } else {
    }
}

void convert_to_bin (FILE *fp_in, FILE *fp_out)
{
    region_t r_base = {0, 0, NULL, NULL};

    printf ("Pass #1: Gathering regions\n");
    parse_and_gen (fp_in, fp_out, 0, &r_base);

    // Allocate memory
    {
        region_t *r = &r_base;
        while (r->next) {
            r = r->next;
            r->buffer = malloc (r->end - r->start);
        }
    }

    printf ("Pass #2: Populating memory and generating output\n");
    parse_and_gen (fp_in, fp_out, 1, &r_base);

    // dump_regions (&r_base);

    // Write the output
    {
        region_t *r = &r_base;
        ullong i;

        while (r->next) {
            r = r->next;
            if (DEMARCATE_REGIONS) {
                fprintf(fp_out, "Region [%lx : %lx]\n", r->start, r->end);
            }
            for (i = r->start; i <= r->end; i++) {
                fprintf (fp_out, "%08x : %02x\n", i, (int) r->buffer[i - r->start]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp_in, *fp_out;

    if (argc < 2) {
        printf ("Usage : srec_to_bin in_filename [out_filename] [--dump-regions]\n");
        return 1;
    }

    fp_in = fopen (argv[1], "r");
    if (fp_in == NULL) {
        printf ("Couldn't open input file : %s\n", argv[1]);
        return 2;
    }

    if (argc > 2) {
        fp_out = fopen (argv[2], "w");
    } else {
        fp_out = fopen ("output.bin", "w");
    }
    if (fp_out == NULL) {
        printf ("Couldn't open output file : %s\n", (argc > 2) ? argv[2] : "output.bin");
        return 2;
    }

    convert_to_bin (fp_in, fp_out);

    return 0;
}
