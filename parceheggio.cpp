#include<iostream>
#include<time.h>
#define N_posti 3
#define Prezzo 1.20
using namespace std;

void stampa_Menu(void);
bool Controllo_targa(string targ);
double Calcola_prezzo(time_t g_in, time_t g_out, time_t m_in, time_t m_out, time_t a_in, time_t a_out, time_t o_in, time_t o_out, time_t min_in, time_t min_out);

class Automobile
{
   string targa;
   string categoria;
   time_t mese_in;
   time_t mese_out;
   time_t giorno_in;
   time_t giorno_out;
   time_t anno_in;
   time_t anno_out;
   time_t ora_in;
   time_t ora_out;
   time_t minuti_in;
   time_t minuti_out;
   int numero_post;
   public:
      void Ingresso(Automobile* macchina[]);
      void Uscita(Automobile* macchina[]);
      void MostraInf(Automobile* macchina[]);
      void Modifica(Automobile* macchina[]);
      void Stampa(Automobile* macchina[]);      
      Automobile()
      {
         targa="";
         categoria="";
         numero_post=0;
      }
};
int cont=0; //contatore per i posti auto
void Inizializza(Automobile* macchina[]);//inizializza il vettore NULL in ogni posizione

time_t tempo; //varaibile per data e ora attuali
struct tm*data; //struct per data e ora attuali

//ingresso di un`automobile
void Automobile::Ingresso(Automobile* macchina[])
{
   int i=0;
   while(macchina[i]!=NULL && i<N_posti)
   {
      i++;
   }
   if(i>=N_posti)
      cout<<endl<<"Parchrggio pieno! \n\n";
   else
    {
       cout<<"Benvenuto al parcheggio, inserici i dati dell`automobile: \n";
       macchina[i] = new Automobile;
       macchina[i]->numero_post = i+1;
       cout<<"Inserisci la targa (nel formato XX123YY): ";
       cin>>macchina[i]->targa;
       bool targa_giusta=true;
       targa_giusta=Controllo_targa(macchina[i]->targa);
       while(!targa_giusta)
       {
       	    cout<<"Il formato della targa risulta errato, inserisci di nuovo: ";
        	cin>>macchina[i]->targa;
        	targa_giusta=Controllo_targa(macchina[i]->targa);
	   }
       cout<<endl<<"Inserisci la categoria (utilitaria, berlina, station wagon, monovolume, fuoristrada): ";
       cin>>macchina[i]->categoria;
       time(&tempo);
       data=localtime(&tempo);
       macchina[i]->giorno_in=data->tm_mday;
       macchina[i]->mese_in=data->tm_mon+1;
       macchina[i]->anno_in=data->tm_year+1900;
       macchina[i]->ora_in=data->tm_hour;
       macchina[i]->minuti_in=data->tm_min;
       cout<<endl<<"Il numero di posto assegnato e`: "<<macchina[i]->numero_post;
       cout<<endl<<endl;
       cont++;
   }
}

//uscita di un`automobile
void Automobile::Uscita(Automobile* macchina[])
{
   string t="";
   cout<<endl<<"Inserisci la targa dell`automobile in uscita: (nel formato XX123YY) ";
   cin>>t;
   bool targa_giusta;
   targa_giusta=Controllo_targa(t);
    while(!targa_giusta)
    {
    	    cout<<"Il formato della targa risulta errato, inserisci di nuovo: ";
        	cin>>t;
        	targa_giusta=Controllo_targa(t);
    }
   int i=0;
   int j=0;
   for(int j=0; j<N_posti; j++)
   {
      if(macchina[j]==NULL || macchina[j]->targa!=t)
       {
          i++;
       }
   }
   
   if(i>=N_posti)
   {
      cout<<endl<<"Automobile non trovata. \n\n ";
   }    
   else
   {
      i=0;
      while( macchina[i]==NULL || macchina[i]->targa!=t)
       {
          i++;
       }
       time(&tempo);
       data=localtime(&tempo);
       macchina[i]->giorno_out=data->tm_mday;
       macchina[i]->mese_out=data->tm_mon+1;
       macchina[i]->anno_out=data->tm_year+1900;
       macchina[i]->ora_out=data->tm_hour;
       macchina[i]->minuti_out=data->tm_min;
       double prezzo;
       prezzo=Calcola_prezzo(macchina[i]->giorno_in, macchina[i]->giorno_out, macchina[i]->mese_in, macchina[i]->mese_out, macchina[i]->anno_in, macchina[i]->anno_out, macchina[i]->ora_in, macchina[i]->ora_out, macchina[i]->minuti_in, macchina[i]->minuti_out);
       cout<<"Data e ora di uscita: "<<macchina[i]->giorno_out<<"/"<<macchina[i]->mese_out<<"/"<<macchina[i]->anno_out<<" "<<macchina[i]->ora_out<<":"<<macchina[i]->minuti_out<<endl;
       cout<<endl<<"Il prezzo totale da pagare per il posteggio e` di: "<<prezzo<<" Euro. /n /n";
       delete macchina[i];
       macchina[i]=NULL;
       cout<<endl<<"Automobile uscita. \n";
       cout<<endl<<endl;
       cont--;
   }
}

//informazioni di un`automobile
void Automobile::MostraInf(Automobile* macchina[])
{
   string t="";
   int i=0;
   cout<<endl<<"Inserisci la targa dell`automobile che vuoi visualizzare (nel formato XX123YY): ";
   cin>>t;
   bool targa_giusta;
   targa_giusta=Controllo_targa(t);
    while(!targa_giusta)
    {
    	    cout<<"Il formato della targa risulta errato, inserisci di nuovo: ";
        	cin>>t;
        	targa_giusta=Controllo_targa(t);
    }
   cout<<endl;
   for(int j=0; j<N_posti; j++)
   {
      if(macchina[j]==NULL || macchina[j]->targa!=t)
      {
          i++;
      }
   }
   if(i>=N_posti)
       cout<<"\nAutomobile non trovata. \n";
    else
   {
      i=0;
      while(macchina[i]==NULL || macchina[i]->targa!=t)
      {
         i++;
      }
      cout<<"N posto     Targa        Categoria       Data e ora arrivo \n";
      cout<<"-----------------------------------------------------------\n";
      cout<<"   "<<macchina[i]->numero_post<<"       ";
      cout<<macchina[i]->targa<<"       ";
      cout<<macchina[i]->categoria<<"       ";
      cout<<macchina[i]->giorno_in<<"/"<<macchina[i]->mese_in<<"/"<<macchina[i]->anno_in<<" "<<macchina[i]->ora_in<<":"<<macchina[i]->minuti_in<<endl;
   }
   cout<<endl<<endl;
}

//stampa le automobili presenti
void Automobile::Stampa(Automobile* macchina[])
{
    cout<<endl<<"N posto     Targa        Categoria       Data e ora arrivo \n";
   cout<<"-----------------------------------------------------------\n";
   int i=0;
   for(int j=0; j<N_posti; j++)
   {
      if(macchina[i]!=NULL)
       {
             cout<<"   "<<macchina[i]->numero_post<<"       ";
             cout<<macchina[i]->targa<<"       ";
             cout<<macchina[i]->categoria<<"       ";
             cout<<macchina[i]->giorno_in<<"/"<<macchina[i]->mese_in<<"/"<<macchina[i]->anno_in<<" "<<macchina[i]->ora_in<<":"<<macchina[i]->minuti_in<<endl;  
           
       }
      i++;
   }
   cout<<endl<<endl;
}

//modifica informazioni di un`automobile
void Automobile::Modifica(Automobile* macchina[])
{
   int n;
   string c="";
   string t="";
   int i=0;
   cout<<"Inserisci la targa dell`automobile che vuoi modificare (nel formato XX123YY): ";
   cin>>t;
   bool targa_giusta;
   targa_giusta=Controllo_targa(t);
    while(!targa_giusta)
    {
    	    cout<<"Il formato della targa risulta errato, inserisci di nuovo: ";
        	cin>>t;
        	targa_giusta=Controllo_targa(t);
    }
   for(int j=0; j<N_posti; j++)
   {
      if(macchina[j]==NULL || macchina[j]->targa!=t)
        {
               i++;               
       }
   }
   
   if(i>=N_posti)
       cout<<endl<<"Automobile non trovata. \n\n";
   else
   {
      i=0;
      while(macchina[i]==NULL || macchina[i]->targa!=t)
      {
         i++;
      }
      cout<<endl<<endl;
      cout<<"Cosa vuoi modificare? \n";
      cout<<"1) Targa \n";
      cout<<"2) Categoria \n";
      cout<<"3) Numero posto \n";
      int s;
      cout<<endl<<"Opzione: ";
      cin>>s;
      while(s<1 || s>3)
      {
      	cout<<"Opzioni non corretta, inserisci di nuovo: ";
      	cin>>s;
	  }
      switch(s)
      {
         case 1:
            t="";
            cout<<endl<<"Inserisci la nuova targa: (nel formato XX123YY) ";
            cin>>t;
            bool targa_giusta;
            targa_giusta=Controllo_targa(t);
            while(!targa_giusta)
            {
              	    cout<<"Il formato della targa risulta errato, inserisci di nuovo: ";
                 	cin>>t;
                	targa_giusta=Controllo_targa(t);
            }
            macchina[i]->targa=t;
            cout<<endl<<"Targa modificata correttamente. \n \n";
         break;
         case 2:
            c="";
            cout<<endl<<"Inserisci la nuova categoria: ";
            cin>>c;
            macchina[i]->categoria="";
            macchina[i]->categoria=c;
            cout<<endl<<"Categoria modificata correttamente. \n \n";
         break;
         case 3:
            int j=0;
            for(int y=0; y<N_posti; y++)
            {
               while(macchina[j]!=NULL)
                {
                   j++;
                }
            }
            
            if(j>=N_posti)
            {
               cout<<endl<<"Il posto che ti e` ststo assegnato e` l`unico disponibile. \n \n";
            }
            else
            {
               cout<<endl<<"Inserisci il numero di posto che desideri: ";
                cin>>n;
               while(macchina[n-1]!=NULL)
                {
                       cout<<endl<<"Posizione occupata, scegline un`altra: ";
                       cin>>n;
                }
                macchina[n-1]= new Automobile;
                macchina[n-1]->targa=macchina[i]->targa;
                macchina[n-1]->categoria=macchina[i]->categoria;
                macchina[n-1]->giorno_in=macchina[i]->giorno_in;
                macchina[n-1]->mese_in=macchina[i]->mese_in;
                macchina[n-1]->anno_in=macchina[i]->anno_in;
                macchina[n-1]->ora_in=macchina[i]->ora_in;
                macchina[n-1]->minuti_in=macchina[i]->minuti_in;
                macchina[i]->targa="";
                macchina[i]->categoria="";
                macchina[i]=NULL;
                 delete macchina[i];
                 macchina[n-1]->numero_post = n;
                cout<<endl<<"Ok, posizione assegnata: "<<macchina[n-1]->numero_post;
                 cout<<endl<<endl;
            }
            
         break;
      }
   }
}


main()
{
   Automobile* m[N_posti];
   Automobile operazione;
   int scelta;
   cout<<"Benvenuti al PARCHEGGIO \n";
    Inizializza(m);
   do
   {
      stampa_Menu();
        do
       {
           cin>>scelta;
       }while(scelta<1 || scelta>6);
       
      switch(scelta)
      {
      case 1:
         operazione.Ingresso(m);
      break;
      case 2:
         operazione.Uscita(m);
      break;
      case 3:
         operazione.MostraInf(m);
      break;
      case 4:
         operazione.Modifica(m);
      break;
      case 5:
         operazione.Stampa(m);
      break;
      }
   }while(scelta!=6);
   
   cout<<"Grazie, arrivederci! \n";
   
   return 0;
}

void stampa_Menu(void)
{
   cout<<"Posti disponibili: "<<N_posti-cont;
   cout<<"\nTariffa: "<<Prezzo<<" Euro l`ora.";
   cout<<"\nScegli l`operazone da effettuare: \n";
   cout<<"1) Ingresso nuova auto \n";
   cout<<"2) Uscita auto \n";
   cout<<"3) Informazioni di un`automobile \n";
   cout<<"4) Modifica informazioni di un`automobile \n";
   cout<<"5) Stampa Automobili presenti \n";
   cout<<"6) Esci \n";   
   cout<<endl<<"Opzione: ";
}

void Inizializza(Automobile* macchina[])
{
   for(int i=0; i<N_posti; i++)
       macchina[i]=NULL;
}

bool Controllo_targa(string targ)
{
	if((targ[0]>=65 && targ[0]<=90) && (targ[1]>=65 && targ[1]<=90) && (targ[2]>='0' && targ[2]<='9') && (targ[3]>='0' && targ[3]<='9') && (targ[4]>='0' && targ[4]<='9') && (targ[5]>=65 && targ[5]<=90) && (targ[6]>=65 && targ[6]<=90))
	   return true;
	else
	   return false;
}

double Calcola_prezzo(time_t g_in, time_t g_out, time_t m_in, time_t m_out, time_t a_in, time_t a_out, time_t o_in, time_t o_out, time_t min_in, time_t min_out)
{
	time_t anno;
	time_t mese;
	time_t giorno;
	time_t ora;
	time_t minuti;
	
	anno=(a_out-a_in)*365*24;
	mese=(m_out-m_in)*30*24;
	giorno=(g_out-g_in)*24;
	ora=o_out-o_in;
	minuti=(min_out-min_in)/60;
	return (anno+mese+giorno+ora+minuti)*Prezzo;
}

