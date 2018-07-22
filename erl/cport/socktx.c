/* Sniffed out of these places,
 *  http://www.tcpdump.org/pcap.html, Tim Carstens, Guy Harris 
 *  http://aschauf.landshut.org/fh/linux/udp_vs_raw/ch01s03.html
 *
 *  compile with,
 *      gcc -lpcap $0
 */

#include <ei.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pcap/pcap.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#define DEBUG 1

int main( int argc, char *argv[] ) {
    int s;                              // socketdescriptor
    struct sockaddr_ll socket_address;  // target address
    unsigned char buffer[2048];
    unsigned int size;

    int index, version, arity;
    unsigned char frame[ETH_FRAME_LEN];
    unsigned long frame_len;
    unsigned long mac_len;
    ei_x_buff retok;
    ei_x_buff reterr;

    // Open a raw-socket for sending frames
    s = socket( AF_PACKET, SOCK_RAW, htons(ETH_P_ALL) );
    if ( s == -1 ) return 1;

    // Compose ok term
    if( ei_x_new_with_version(&retok) ) return 2;
    if( ei_x_encode_atom(&retok, "ok") ) return 3;

    // Compose err term
    if( ei_x_new_with_version(&reterr) ) return 4;
    if( ei_x_encode_atom(&retok, "error") ) return 5;

    /*RAW communication*/
    socket_address.sll_family   = PF_PACKET;    
    socket_address.sll_protocol = htons(ETH_P_IP);  
    socket_address.sll_ifindex  = 2;
    socket_address.sll_hatype   = ARPHRD_ETHER;
    socket_address.sll_pkttype  = PACKET_OTHERHOST;
    socket_address.sll_halen    = ETH_ALEN;     

    // This while automatically exits on EOF.
    while( read_msg( buffer, &size ) > 0 ) {
        /* Reset the index, so that ei functions can decode terms from the 
         * beginning of the buffer */
        index = 0;
        /* Ensure that we are receiving the binary term by reading and 
         * stripping the version byte */
        if( ei_decode_version(buffer, &index, &version) ) return 6;
        /* Our marshalling spec is that we are expecting a tuple
         * { frame_len, frame, sockaddr_len, sockaddr } */
        if( ei_decode_tuple_header( buffer, &index, &arity ) ) return 7;
        if( arity != 2 ) return 8;
        if( ei_decode_binary(buffer, &index, frame, &frame_len) ) return 9;
        if( ei_decode_binary(buffer, &index, socket_address.sll_addr, &mac_len) ) return 10;
        fprintf( stderr, "%x %x\n", socket_address.sll_addr[0], socket_address.sll_addr[mac_len-1] );
        fprintf( stderr, "%s \n", frame+14 );
        //rc = sendto(
        //        s,
        //        frame,
        //        (size_t)frame_len,
        //        0,
        //        (struct sockaddr*)&socket_address
        //        sizeof( socket_address )
        //     );
        //if( rc < 0 ) return 13;
        write_msg( &retok );
    }
    return 0;
}

int read_msg( unsigned char buf[], int *size ) {
    unsigned int len;

    if( read_exact(buf, 2) != 2 ) return -1;
    len = (buf[0] << 8) | buf[1];
    *size = len;
    return read_exact( buf, len );
}

int read_exact( unsigned char buf[], int len) {
    int i, got=0;
    do {
        if ( (i = read(0, buf+got, len-got)) <= 0 ) {
            return i;
        }
        got += i;
    } while( got<len );
    return len;
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
