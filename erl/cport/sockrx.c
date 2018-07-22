/* Sniffed out of these places,
 *  http://www.tcpdump.org/pcap.html, Tim Carstens, Guy Harris 
 *  http://aschauf.landshut.org/fh/linux/udp_vs_raw/ch01s03.html
 *
 *  compile with,
 *      gcc -lpcap $0
 */

#include <ei.h>

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pcap/pcap.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#define DEBUG 1
#define PROMISC 0
#define BUFSIZE 1024

/* struct pcap_pkthdr {
 *      struct timeval ts;      time stamp
 *      bpf_u_int32 caplen;     length of portion present
 *      bpf_u_int32;            length this packet (off wire)
 * }
 */

int write_msg( ei_x_buff *result );
int write_exact( unsigned char *buf, int len );

extern int ei_x_new_with_version(ei_x_buff* x);

int main( int argc, char *argv[] ) {
    char *dev;                          // Name of the device to use
    char errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 netp;                   // ip
    bpf_u_int32 maskp;                  // subnet mask
    char *net;          // dot notation of the network address
    char *mask;         // dot notation of the network mask
    struct in_addr addr;
    int rc; 

    pcap_t *descr;
    const u_char *packet;
    struct pcap_pkthdr hdr;         // pcap.h
    ei_x_buff result;
    unsigned char pkt[ETH_FRAME_LEN];

    // ask pcap to find a valid device for use to sniff on
    dev = pcap_lookupdev( errbuf );
    if( dev == NULL ) return 1;

    // ask pcap for the network address and mask of the device */
    pcap_lookupnet( dev, &netp, &maskp, errbuf );
    // get the network address and device mask in a human readable form
    addr.s_addr = netp;
    net = inet_ntoa( addr );
    addr.s_addr = maskp;
    mask = inet_ntoa( addr );
    if( (net == NULL) || (mask == NULL) ) return 2;

    /* open the device for sniffing.
     *      pcap_t *pcap_open_live( char *device, int snaplen, int prmisc,
     *                              int to_ms, char *ebuf )
     *     snaplen - maximum size of packets to capture in bytes
     *     promisc - set card in promiscuous mode?
     *     to_ms - time to wait for packets in miliseconds before read
     *     times out
     *     errbuf - if something happens, place error string here
     */
    descr = pcap_open_live( dev, BUFSIZE, PROMISC, 1000000, errbuf );
    if( descr == NULL ) return 3;

    // Re-open standard input in non-blocking mode
    fcntl( 0, F_SETFL, O_NONBLOCK ); 
    while(1) {
        // Fetch the packet
        packet = pcap_next( descr, &hdr );
        if( packet == NULL ) return 4;

        /* Our marshalling spec is that we are expecting a tuple
         * { frame_len, frame, hdr_len, hdr } */
        if( ei_x_new_with_version(&result) ) return 5;
        if( ei_x_encode_tuple_header(&result, 4) ) return 6;
        if( ei_x_encode_long(&result, ETH_FRAME_LEN) ) return 8;
        if( ei_x_encode_binary(&result, packet, ETH_FRAME_LEN) ) return 7;
        if( ei_x_encode_long(&result, sizeof(hdr)) ) return 10;
        if( ei_x_encode_binary(&result, &hdr, sizeof(hdr)) ) return 11;
        printf("Received ...");
        // send them to stdout.
        write_msg( &result );

        // This seems to be the standard way of ending the port-process.
        rc = read( 0, (void*)packet, 1 );
        if( rc == 0 ) return 0; // EOF
    }
    return 0;
}

int write_msg( ei_x_buff *result ) {
    unsigned char li;

    li = (result->index >> 8) & 0xff; 
    write_exact(&li, 1);
    li = result->index & 0xff;
    write_exact(&li, 1);
    return write_exact( result->buff, result->index );
}

int write_exact( unsigned char *buf, int len ) {
    int i, wrote = 0;
    do {
        if( (i = write(1, buf+wrote, len-wrote)) <= 0 ) return i;
        wrote += i;
    } while( wrote<len );
    return len;
}
