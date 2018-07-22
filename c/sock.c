/* A simple server in the internet domain using TCP
 *    The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int my_socket, length;
    struct sockaddr_in me, dest;
    char buf[ ]="Text we want to send …";

    my_socket = socket( AF_INET, SOCK_DGRAM, 0 );
    me.sin_family = AF_INET;
    me.sin_port = htons(9998);
    me.sin_addr.s_addr = INADDR_ANY;
    memset( &(me.sin_zero), '\0', 8 );
    dest.sin_family = AF_INET;
    dest.sin_port = htons(9999);
    dest.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset( &( dest.sin_zero), '\0', 8 );
    length = sizeof( struct sockaddr_in );
    bind( my_socket, (struct sockaddr *)&me, length );
    sendto( my_socket, buf, strlen(buf), 0, (struct sockaddr *)&dest, length );
    /* we then wait for an answer */
    recvfrom( my_socket, buf, strlen(buf), 0, (struct sockaddr *)&dest, &length );
    printf("%s \n", buf);
    sendto( my_socket, buf, strlen(buf), 0, (struct sockaddr *)&dest, length );
}
