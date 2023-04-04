#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#define MAX_MESSAGE_LENGHT 16

int main(int argc, char **argv)
{
	int sd, portno;
	
	struct sockaddr_in server_endpoint;
	char buffer[MAX_MESSAGE_LENGHT];
	
	server_endpoint.sin_family=AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=inet_addr("127.0.0.1");
	sd=socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	connect(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	printf("Aperto canale - server  endpoint %s:%d\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	
	strcpy(buffer, "Ping Pong");
	send(sd, buffer, strlen(buffer), 0);
	printf("Inviato: \"%s\"\n", buffer);
	recv(sd,  buffer, MAX_MESSAGE_LENGHT, 0);
	printf("Ritornato indietro: \%s\"\n", buffer);
	
    close(sd);	
	return 0;
}




