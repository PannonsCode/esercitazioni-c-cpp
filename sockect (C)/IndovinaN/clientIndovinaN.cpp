//Gioco sette e mezzo
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
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
#define MAX 1024
using namespace std;

void introduzione(void);

int main()
{
	introduzione();
	
	struct sockaddr_in server_endpoint;
	int sd, tentativi, N, flag1=0;
	char  hostname[MAX], indizio[MAX];


	//addr_init(&server_endpoint, htons(1025), INADDR_ANY);
	//memset((char *) &server_endpoint, '-', sizeof(server_endpoint));
	server_endpoint.sin_family = AF_INET;
	server_endpoint.sin_port=htons(1025);
	server_endpoint.sin_addr.s_addr=inet_addr("127.0.0.1");
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(sd, (struct sockaddr*)&server_endpoint, sizeof(server_endpoint))>0)
	   cout<<"Connessione stabilita con il server"<<endl;
	else
	   cout<<"Connessione non riuscita"<<endl;
	gethostname((char*)hostname, MAX);
	send(sd, &hostname, sizeof(hostname), 0);
	cout<<"Inserisci il numero da indovinare: ";
	cin>>N;
	send(sd, &N, sizeof(N), 0);
	
	while(flag1==0)
	{
        cout<<"Non indovinato, riprova"<<endl;
        cout<<"Inserisci "; 
        cin>>N;    
        send(sd, &N, sizeof(N), 0);
        
        recv(sd, &indizio, sizeof(indizio), 0);
        cout<<"Il numero da indovinare e' "<<indizio<<endl;

        recv(sd, &flag1, sizeof(flag1), 0);
	}
	
	cout<<"Giusto, hai indovinato"<<endl;
	recv(sd, &tentativi, sizeof(tentativi), 0);
	cout<<endl<<"Hai indovinato con "<<tentativi<<" tentativi"<<endl;
	cout<<endl<<"***FINE PARTITA***"<<endl<<endl;
	cout<<endl<<"Grazie per aver giocato, alla prossima!!!!"<<endl<<endl;
	
	close(sd);
	
	return 0;
}

void introduzione(void)
{
	cout<<"Benvenuti in questa nuova partita di --What is the number?-- "<<endl<<endl;
	cout<<"Indovina il numero generato dal server nel minor numero di tentativi!!!"<<endl;
	cout<<"Il numero generato dal server e' compreso tra 1 e 1000"<<endl;
}
