#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <omp.h>
#include <unistd.h>

#define MAXOFFERTE   10              // numero massimo di offerte per sessione  
#define MAX 255                       //buffer

int main (int argc, char *argv[])
{ 
   printf("Asta online aperta: sono accettate massimo %d offerte, fate le vostre offerte\n\n",MAXOFFERTE);	
	
   //variabili
   int ContatoreOfferte=0, ricevuta=0, daBattere=0, N, lenght;	

  // creazione della socket sul server 
    int sd, nsd,clientlenght;
	struct sockaddr_in server_endpoint, client_endpoint;
	char buffer_server[MAX], buffer[MAX], hostname[MAX];
	
	//addr_init(&server_endpoint, htons(1025), INADDR_ANY);
	bzero((char *) &server_endpoint, sizeof(server_endpoint));
	server_endpoint.sin_family=AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=INADDR_ANY;
		
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	fork();
	listen(sd,6);
	
	strcpy(buffer, "Benvenuti nell`asta online, fai le tue offerte");
	clientlenght=sizeof(client_endpoint);
	lenght=sizeof(ricevuta);
while(ContatoreOfferte<MAXOFFERTE){
	
	
	listen(sd,6);
	nsd=accept(sd, &client_endpoint, &clientlenght);
    printf("Connessione instaurata sulla porta: %d, con il client %d\n", ntohs(client_endpoint.sin_port));//omp_get_thread_num()
    send(nsd, buffer, strlen(buffer), 0);
    recv(nsd, &ricevuta, lenght, 0);
    if(ricevuta>daBattere)
    {
		daBattere=ricevuta;
		bzero(buffer_server, MAX);
		strcpy(buffer_server,"Offerta accettata, sei il nuovo campione in carica");
		send(nsd, &buffer_server, strlen(buffer_server), 0);
		printf("Nuova offerta da battere: %d\n", daBattere);
		recv(nsd, &hostname, sizeof(hostname), 0);
    }
    else
    {
		bzero(buffer_server, MAX);
		strcpy(buffer_server, "Offerta rifiutata");
		send(nsd, &buffer_server, strlen(buffer_server), 0);
		printf("Offerta da battere: %d\n", daBattere);
    }
	ContatoreOfferte++; 
	recv(nsd, &N, sizeof(N), 0);

}
     
    printf("Asta terminata, si aggiudica l`asta il client: %s\n", hostname);
    //send(nsd, buffer_server, strlen(buffer_server), 0);

    close(nsd);
	close(sd);
	printf("CANALE CHIUSO \n");
  
}

