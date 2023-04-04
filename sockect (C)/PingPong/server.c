#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/times.h>
#define MAX_MESSAGE_LENGHT 16
#define MAXBUF 16


int main()
{
    int sd, nsd, clientlenght;
	struct sockaddr_in server_endpoint, client_endpoint;
	char buffer[MAX_MESSAGE_LENGHT], line[MAX_MESSAGE_LENGHT];
	
	bzero((char *) &server_endpoint, sizeof(server_endpoint));
	server_endpoint.sin_family = AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr= htonl(INADDR_ANY);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	listen(sd, 1);
	printf("Configurato canale - server endpoint %s:%d\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	clientlenght=sizeof(client_endpoint);
	
	while((nsd = accept(sd, (struct sockaddr*)&client_endpoint, &clientlenght))!=-1)
	{
		printf("Serevr: accettata nuova connessione \n\n");
		recv(nsd, line, MAXBUF, 0);
		send(nsd, line, MAXBUF, 0);
		close(nsd);
		printf("Server: fine connessione\n\n");
	}
	printf("Chiusura dei lavori...\n");
	
	close(nsd);
	close(sd);
	return 0;
}


