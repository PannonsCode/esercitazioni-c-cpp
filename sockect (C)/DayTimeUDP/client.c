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

#define SERV_PORT 5193
#define MAXLINE 1024

int main(int argc, char*argv[])
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;
	
	if(argc!=2)
	{
		fprintf(stderr, "utilizzo: daytime_clientUDP <indirizzo IP server>\n");
		exit(1);
    }
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
		perror("errore in socket");
		exit(-1);
    }
    
    memset((void*)&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
	{
		perror("errore in inet_pton");
		exit(-1);
	}		
	if(sendto(sockfd, NULL,0,0, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		perror("errore in sendto");
		exit(-1);
    }
    n=recvfrom(sockfd, recvline, MAXLINE,0,NULL,NULL);
    if(n<0)
    {
		perror("errore in recvfrom");
		exit(-1);
	}
	if(n>0)
	{
		recvline[n]=0;
		if(fputs(recvline, stdout)==EOF)
		{
			perror("errore in fputs");
			exit(-1);
		}
	}
	exit(0);
}

