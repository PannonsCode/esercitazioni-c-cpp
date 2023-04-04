#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 255

void server1();

int main(int argc, char **argv)
{
	server1();
	
	return 0;
}

void server1()
{
	int sd, nsd,clientlenght;
	struct sockaddr_in server_endpoint, client_endpoint;
	char buffer_client[MAX], buffer_server[MAX];
	pid_t pid;
	
	//addr_init(&server_endpoint, htons(1025), INADDR_ANY);
	bzero((char *) &server_endpoint, sizeof(server_endpoint));
	server_endpoint.sin_family=AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=INADDR_ANY;
    sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	listen(sd, 5);
	printf("Configurato canale - server endpoint %s:%d\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	clientlenght=sizeof(client_endpoint);
	nsd = accept(sd, &client_endpoint, &clientlenght);
	fcntl(nsd,F_SETFL,0,O_NONBLOCK);
	printf("Contatto - client endpoint %s:%d\n", inet_ntoa(client_endpoint.sin_addr), ntohs(client_endpoint.sin_port));

	bzero(buffer_client, MAX);
	pid=fork();
	do
	{
	 bzero(buffer_client, MAX);	 
	 
	 fork();
	   recv(nsd, buffer_client, MAX, 0);
	 

       if(buffer_client[0]=='x')
	   {
		   buffer_server[0]='x';
	       send(nsd, buffer_server, strlen(buffer_server), 0);
	       exit(0);
	   }

           printf("Ricevuto messaggio: %s\n", buffer_client);
           fork();
	       printf("Server--> Inserisci un messaggio: \n");
	       fgets(buffer_server,MAX,stdin);
	       send(nsd, buffer_server, strlen(buffer_server), 0);
	       //printf("Inviato\n");

	   bzero(buffer_server,MAX);
      
	}while(1);
	
	   	
	close(nsd);
	close(sd);
	printf("CANALE CHIUSO \n");
}
