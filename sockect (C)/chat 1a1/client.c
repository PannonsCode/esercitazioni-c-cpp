#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <errno.h>

#define MAX 255
void client();

int main()
{
    printf("Sistema di chat, digitare il carattere \'x\' per uscire \n\n");
	client();
	
	return 0;
}

void client()
{
	int sd;
	
	struct sockaddr_in server_endpoint;
	char buffer_server[MAX], buffer_client[MAX];
	
	server_endpoint.sin_family=AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=inet_addr("127.0.0.1");
	sd=socket(AF_INET, SOCK_STREAM, 0);
	//bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	connect(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	printf("Aperto canale - server  endpoint %s:%d\n\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	
	bzero(buffer_server,MAX);
   while(1)
   {
	  bzero(buffer_client,MAX);
      printf("Client--> Inserisci un messaggio: ");
	  fgets(buffer_client,MAX,stdin);
	  int ris; ris = send(sd, buffer_client, strlen(buffer_client), 0);
	  
	  
	  printf("Inviato\n");
	  recv(sd,  buffer_server, MAX, 0);
	  if(buffer_server[0]=='x')
	  {
		  printf("Connessione in chiusura... \n");
		  break;
	  }
	  printf("Ricevuto messaggio: %s\n", buffer_server);
	  bzero(buffer_server,MAX);
   }
	
    close(sd);
    printf("CANALE CHIUSO \n");
}

