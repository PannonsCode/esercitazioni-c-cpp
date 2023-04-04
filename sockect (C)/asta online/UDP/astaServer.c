#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXOFFERTE  10               // numero massimo di offerte per sessione
#define MAXLUNGO    40               // lunghezza nominativo offerente
#define IPADDRESS "127.0.0.1"        // indirizzo del server 
#define PORTA 1313                   // numero di porta del server    


struct sockaddr_in offerente;
int socketlen; 
 
// creazione della socket sul server 
int creaServer (char *ip_address, int porta)
{
  int socketfd;
  struct sockaddr_in server;

  /* crea il descrittore della socket */
  if ((socketfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
  {
     printf ("errore nella creazione della socket");
     return 0;
  }

  /* configurazione parametri porta locale */
  bzero ((char *) &server, sizeof (server));         /* azzera il record */ 
  server.sin_family = AF_INET;                       /* internet         */       
  server.sin_addr.s_addr = inet_addr (ip_address);   /* indirizzo server */   
  server.sin_port = htons (porta);                   /* porta  server    */

  /* collegamento dela socket sul server   */
  if (bind (socketfd, (struct sockaddr *) &server, sizeof(server)) < 0)
  {
     printf ("errore nella operazione di bind");
     return 0;
  }
  return socketfd;
}

// funzione che trasmette un messaggio al client
int inviaMsg (int socketfd, char *buffer)
{
   int msg_len = strlen(buffer);
   if (sendto (socketfd, buffer, msg_len, 0,
              (struct sockaddr *) &offerente, socketlen) < 0)
   {
     printf ("errore nella trasmissione del messaggio di risposta");
     return 0;
   }
   return 1;
}

// funzione che riceve un messaggio dal client
int riceviMsg (int socketfd, char *buffer)
{
  int numCaratteri;
  socketlen = sizeof (offerente);
  if ((numCaratteri = recvfrom (socketfd, buffer, BUFSIZ, 0,
                      (struct sockaddr *) &offerente,(int *) &socketlen)) < 0)
  {
    printf ("errore nella ricezione del messaggio con l'offerta");
    return -1;
  }
  buffer [numCaratteri] = '\0';
  return numCaratteri;
}

// programma principale -------------------------------------------------------------------------
int main (int argc, char *argv[])
{
  int  socketfd, numOfferte;              // definizione delle variabili locali 
  char buffer [BUFSIZ + 1];
  char nomeOfferente [MAXLUNGO], nomeVince [MAXLUNGO];
  int  nuovaOfferta, offertaVince;

  numOfferte = 0;
  nomeVince [0] = '\0';
  // creazione della socket sul server 
  if ((socketfd = creaServer (IPADDRESS, PORTA)) == 0)
  {
    fprintf (stderr, "impossibile creare la socket sul server\n");
    exit (EXIT_FAILURE);
  }
  
 
    printf ("L'asta e' aperta: fate le vostre offerte\n");
  offertaVince=0;
  // ricezione di una offerta  
  while (riceviMsg (socketfd, buffer) > 0)
  {
    nuovaOfferta = 0;
    sscanf (buffer, "%s %d", nomeOfferente, &nuovaOfferta);
    if (nuovaOfferta <= 0)
      inviaMsg (socketfd, "Offerta non valida\n");
    else 
    {
      numOfferte++;
      printf ("Nuova offerta # %d di Euro  %d\n", numOfferte, nuovaOfferta);
      if (nuovaOfferta > offertaVince)            // la nuova offerta diviene
      {                                           // l'offerta vincente 
        offertaVince = nuovaOfferta;
        strcpy (nomeVince, nomeOfferente);
        inviaMsg (socketfd, "Offerta accettata\n");
        printf ("Nuova offerta da superare: %s %d\n", nomeVince, offertaVince);
      }
      else                                        // l'offerta è inferiore 
      {
        inviaMsg (socketfd, "Spiacente, e` stata fatta un'offerta superiore\n");
      }
    }
    
    if (numOfferte>MAXOFFERTE)                    // l'aste e' terminata 
    {
     printf ("Termine asta : si aggiudica il sig. %s con l'offerta di Euro %d \n",
                                                       nomeVince, offertaVince);
     exit (0);
    }
  }

  // chiusura della socket
  if (close (socketfd) != 0)
  {
    printf ("errore nella chiusura della socket");
    return 0;
  }
  return EXIT_SUCCESS;
}





