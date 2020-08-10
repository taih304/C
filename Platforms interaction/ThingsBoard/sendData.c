#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

char HTTP_REQUEST[200] = "POST /api/v1/gG5svlcW9VB5fVQBpCNC/telemetry HTTP/1.1\r\nHost: ";
char sendValue[100] = "{\"string-value\": \"Hello, World!\"}";
char stringLength[10];

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock == -1){
		perror("setsockopt");
		exit(1);
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);

	}
	return sock;
}

int main(int argc, char *argv[]){
	int fd;
	char buffer[BUFFER_SIZE];

	if(argc < 3){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(1); 
	}

	sprintf(stringLength, "%ld", strlen(sendValue));
	
	//Form a HTTP request like: "GET / HTTP/1.1\r\n Host: 192.168.0.103\r\n\r\n";
	strcat(HTTP_REQUEST, argv[1]);
	strcat(HTTP_REQUEST, "\r\nContent-Type: application/json");
	strcat(HTTP_REQUEST, "\r\nContent-Length: ");
	strcat(HTTP_REQUEST, stringLength);
	strcat(HTTP_REQUEST, "\r\n\r\n");
	strcat(HTTP_REQUEST, sendValue);
	strcat(HTTP_REQUEST, "\r\n");
	
	puts(HTTP_REQUEST);

	fd = socket_connect(argv[1], atoi(argv[2])); 
	write(fd, HTTP_REQUEST, strlen(HTTP_REQUEST)); // write(fd, char[]*, len);  
	bzero(buffer, BUFFER_SIZE);
	
	// while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
	// 	fprintf(stderr, "%s", buffer);
	// 	bzero(buffer, BUFFER_SIZE);
	// }

	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return 0;
}