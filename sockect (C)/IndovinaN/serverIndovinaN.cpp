//Gioco sette e mezzo
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/times.h>
#define MAX 1024
using namespace std;

void introduzione(void);

int Assegna_numero()
{
	srand(time(NULL));
    int c=0;
	c=rand() % 1000 + 1;
	return c;
}


int main()
{
	introduzione();
    
	int sd, nsd, clientlenght;
	struct sockaddr_in server_endpoint, client_endpoint;

	int N, NdaIndovinare, cont=1, flag1=0;
	char  utente[MAX], indizio[MAX];
	
	//addr_init(&server_endpoint, htons(1025), INADDR_ANY);
	//memset((char *) &server_endpoint, '-', sizeof(server_endpoint));
	server_endpoint.sin_family = AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr= htonl(INADDR_ANY);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint));
	listen(sd, 1);
//	printf("Configurato canale - server endpoint %s:%d\n", inet_ntoa(server_endpoint.sin_addr), ntohs(server_endpoint.sin_port));
	clientlenght=sizeof(client_endpoint);
	cout<<endl<<"Gioco avviato sul server, in attesa di un avversario..."<<endl;
	
	nsd = accept(sd,(struct sockaddr*)&client_endpoint, (socklen_t*)&clientlenght);
	if(nsd<0)
	 cout<<"Errore1";
	else
	  cout<<"Connessione..."<<endl;
	if(recv(nsd, &utente, sizeof(utente), 0)>0)
	  cout<<"Nuovo giocatore: "<<utente<<endl;
	else
	  cout<<"Errore"<<endl;
    
    NdaIndovinare=Assegna_numero();
    //cout<<NdaIndovinare<<endl;
    recv(nsd, &N, sizeof(N), 0);
    cout<<"Ricevuto numero: "<<N<<endl;
    
	while(NdaIndovinare!=N)
	{
		N=0;
		cout<<"Sbagliato "<<endl;
		cout<<"Non indovinato"<<endl;
		cont++;
		recv(nsd, &N, sizeof(N), 0);
		cout<<"Ricevuto numero: "<<N<<endl;
		
		if(N<NdaIndovinare)
		{
			strcpy(indizio, "maggiore");
			send(nsd, &indizio, sizeof(indizio), 0);
		}
		else
		{
			strcpy(indizio, "minore");
			send(nsd, &indizio, sizeof(indizio), 0);
		}
		cout<<indizio<<endl;
		
		if(N!=NdaIndovinare)
		{
		   flag1=0;
		   send(nsd, &flag1, sizeof(flag1), 0);
		}
		else
		{
		   flag1=1;
		   send(nsd, &flag1, sizeof(flag1), 0);
		}
	}
	
	send(nsd, &cont, sizeof(cont), 0);

	cout<<"GIUSTO "<<endl;
    cout<<"Il giocatore ha indovinato"<<endl;
	
	cout<<endl<<utente<<" ha indovinato con "<<cont<<" tentativi"<<endl;
	
	
	
	cout<<endl<<"FINE PARTITA, chiusura in corso..."<<endl;
	
	return 0;
}

void introduzione(void)
{
	cout<<"Benvenuti in questa nuova partita di --What is the number?-- "<<endl<<endl;
	cout<<"Il server genera un numero e l'utente che si connette deve indovinarlo"<<endl;
}








