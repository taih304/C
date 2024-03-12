#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <errno.h>

#define BUFFSIZE 	256
#define PORT 		8000

int udp_socket_param_init(){
    struct sockaddr_in receiver_addr;
    socklen_t len; 

    //Create UDP socket receiver
    int receiver_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create UDP receiver socket successfully\n");
 
    receiver_addr.sin_family = PF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(receiver_fd, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start UDP socket receiver successfully through binding\n");

    return receiver_fd;
}
int main(int argc, char *argv[]){
    int receiver_fd = udp_socket_param_init();
    struct sockaddr_in src_addr;// Dummy src_addr;
    socklen_t src_addr_len = sizeof(src_addr);  //len is value/result

    while(1){
        char buffer[BUFFSIZE];
        bzero(buffer, BUFFSIZE);//Delete buffer
        int bytes_received = recvfrom(receiver_fd, (char *)buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *) &src_addr, &src_addr_len);
        if (bytes_received > 0) {
            printf("Message from UDP sender: %s", buffer);
            bzero(buffer, BUFFSIZE);         //Delete buffer
        } 
    }
}
