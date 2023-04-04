#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORTA 1313
#define IPSERVER "127.0.0.1"

struct sockaddr_in client;
int socketlen; 

// funzione che riceve un messaggio al server 
int riceviMsg (int socketfd, char *buffer)
{
  int numCaratteri;
  socketlen = sizeof (client);
  if ((numCaratteri = recvfrom (socketfd, buffer, BUFSIZ, 0,
                       (struct sockaddr *) &client,(int *) &socketlen)) < 0)
  {
    printf ("errore nella ricezione del messaggio");
    return -1;
  }
  buffer [numCaratteri] = '\0';
  return numCaratteri;
}

// funzione che trasmette un messaggio al server 
int inviaMsg (int socketfd, char *buffer, char *ip_address, int porta)
{
  int numCaratteri = strlen(buffer);
  /* configurazione parametri porta locale */
  bzero ((char *) &client, sizeof (client));
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr (ip_address);
  client.sin_port = htons ((unsigned short) porta);

  if (sendto (socketfd, buffer, numCaratteri, 0,(struct sockaddr *) &client, 
                                                sizeof(client)) != numCaratteri)
  {
    printf ("errore  nella trasmissione del messaggio");
    return 0;
  }
  return 1;
}
//------------------------------------------------------------------------------------------------
int main (int argc, char *argv[]){
   // variabili locali  
   char buffer[BUFSIZ + 1];
   int socketfd;

   //  creazione della socket del client
   if ((socketfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
      printf ("errore fatale nella creazione della socket()");
      return 0;
   } 
   
   // creazione della offerta 
   printf ("Inserire nome e offerta: "); 
   if (fgets (buffer, BUFSIZ, stdin) != NULL)
   {
     inviaMsg (socketfd, buffer, IPSERVER, PORTA);     // inoltro messaggio 
     if (riceviMsg (socketfd, buffer) > 0)            // attesa risposta 
       fputs (buffer, stdout);
   }

   // chiusura socket del client 
   if (close (socketfd) != 0)
   {
     printf ("errore fatale nella chiusura della socket()");
     return 0;
   }

   return EXIT_SUCCESS;
}

 
