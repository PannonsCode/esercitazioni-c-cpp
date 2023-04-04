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

int main()
{
	int offerta;
	
	int sd;
	
	struct sockaddr_in server_endpoint;
	char buffer_server[MAX], hostname[MAX];
	
	server_endpoint.sin_family=AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=inet_addr("127.0.0.1");
	sd=socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	connect(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	printf("Aperto canale - server  endpoint %s:%d\n\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	
   bzero(buffer_server, MAX);
   recv(sd,  buffer_server, MAX, 0);
   printf("%s\n", buffer_server);
	
/*do	
//{
    printf("Scegli cosa fare: \n 1 -> Fai un`offerta \n 2 -> Esci \n Inserisci:");
    scanf("%d",&opzione);
    
   switch(opzione){
    case 1:*/
       printf("Inserisci l`offerta: ");
       scanf("%d",&offerta);
       send(sd, &offerta, sizeof(offerta), 0);
   /*    break;
    case 2:
       close(sd);
       return 0;
   } */
   bzero(buffer_server, MAX);
   recv(sd,  buffer_server, MAX, 0);
   printf("%s\n", buffer_server);
   gethostname(hostname, MAX);
   send(sd, &hostname, sizeof(hostname), 0);

 //}while(send(sd, &N, sizeof(N), 0)!=-1);
	
    close(sd);
    printf("CANALE CHIUSO \n");

	return 0;
}

