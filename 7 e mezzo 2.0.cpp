//Gioco sette e mezzo
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<windows.h>
#include<dos.h>
using namespace std;

void introduzione(void);
void controllo_carte(int &C, int cart[]);

class Carte
{
	public:
		int carta;
		int carta1;
		int puntata;
		int gettoni;
		int totp;
		double punti;
		int Assegna_carta();
		void Stampa_carta(int carta);
		Carte()
		{
			carta=0;
	        carta1=0;
    	    puntata=0;
	    	gettoni=0;
	        totp=0;
	        punti=0;
		}
};



int Carte::Assegna_carta()
{
	srand(time(NULL));
    int c=0;
	c=rand() % 10 + 1;
	return c;
}

void Carte::Stampa_carta(int carta)
{
	if(carta!=10)
	{
       Sleep(700);
			      cout<<"         ---"<<endl;
		          cout<<"        |"<<"   |"<<endl;
			      cout<<"Carta:  | "<<carta<<" |"<<endl;
			      cout<<"        | "<<"  |"<<endl;
		          cout<<"         ---"<<endl;
	}
	else
	{
	  Sleep(700);
			      cout<<"         ---"<<endl;
		          cout<<"        |"<<"   |"<<endl;
			      cout<<"Carta:  | "<<carta<<"|"<<endl;
			      cout<<"        | "<<"  |"<<endl;
		          cout<<"         ---"<<endl;
	}
}

main()
{
	system("COLOR 2F");
	introduzione();
	Carte giocatore, banco;
	int risposta, N;
	int carta[10]={0,0,0,0,0,0,0,0,0,0};
    double punticarta1;

	cout<<"Inserisci il numero di round che vuoi giocare: ";
	cin>>N;
		cout<<"Decidi con quanti gettoni giocare: "<<endl;
	cout<<"(N.B.: il numero che deciderai per te saranno gli stessi per il banco)"<<endl;
	cin>>giocatore.gettoni;
	banco.gettoni=giocatore.gettoni;
    banco.puntata=10;
	cout<<endl;
	for(int i=0; i<N; i++)
	{
		Sleep(500);
	    cout<<"***NUOVO ROUND***"<<endl<<endl;
	    cout<<"Puntata: ";
	    cin>>giocatore.puntata;
	    cout<<endl<<endl;
	    cout<<"Banco: "<<banco.gettoni<<endl;
	    cout<<"Tu: "<<giocatore.gettoni<<endl<<endl;
	    Sleep(500);
	//assegno la carta al giocatore
	giocatore.carta1 = giocatore.Assegna_carta();
	cout<<"Questa e' la tua prima carta:"<<endl;
    giocatore.Stampa_carta(giocatore.carta1);
    
	//controllo carte
	controllo_carte(giocatore.carta1, carta);
	//fine controllo
	
	if(giocatore.carta1<=7)
	    giocatore.punti=giocatore.carta1;
	else
		giocatore.punti=0.5;

	punticarta1=giocatore.punti;
	//assegno la carta al banco
	banco.carta1=banco.Assegna_carta();
	
		//controllo carte
	controllo_carte(banco.carta1, carta);
		//fine cotrollo
	
	if(banco.carta1<=7)
	    banco.punti=banco.carta1;
	else
		banco.punti=0.5;
	
	//gioca l'utente
	Sleep(500);
	cout<<"Hai "<<giocatore.punti<<" punti, voui un' altra carta? (Rispondi 1 per si o 2 per no)"<<endl;
	cin>>risposta;
	while(risposta==1)
	{
		giocatore.carta=giocatore.Assegna_carta();
		controllo_carte(giocatore.carta, carta);
	    giocatore.Stampa_carta(giocatore.carta);
	    
		if(giocatore.carta<=7)
	        giocatore.punti+=giocatore.carta;
	    else
			giocatore.punti+=0.5;
			
		if(giocatore.punti>7.5)
	    {
	    	Sleep(500);
	    	cout<<"Con "<<giocatore.punti<<" punti, HAI SBALLATO! Hai perso questo round"<<endl<<endl;
	    	banco.gettoni+=giocatore.puntata;
	    	giocatore.gettoni-=giocatore.puntata;
	    	banco.totp++;
	    	break;
	    }
	    else
	    {
	    	if(giocatore.punti<7.5)
	    	{
	    		Sleep(500);
	    		cout<<"Hai "<<giocatore.punti<<" punti, voui un' altra carta? (Rispondi 1 per si o 2 per no)"<<endl<<endl;
	            cin>>risposta;
	    	}
	    	else
	    	{
	    		Sleep(500);
	    		cout<<"Hai fatto 7 e mezzo!!! Complimenti hai vinto questo round!!!"<<endl<<endl;
	    		banco.gettoni-=banco.puntata;
	    	    giocatore.gettoni+=giocatore.puntata;
	    		giocatore.totp++;
	    		break;
	    	}
	    }
	}
	if(giocatore.punti>=7.5)
	{
		Sleep(500);
		cout<<"Il banco possedeva "<<banco.carta1<<" con "<<banco.punti<<" punti."<<endl<<endl;
	}
	else
	{
		Sleep(500);
		cout<<"Il banco ha:"<<endl;
		banco.Stampa_carta(banco.carta1);
		if(giocatore.punti-punticarta1==0)
		{
			while((banco.punti!=6 || banco.punti!=6.5 || banco.punti!=7) && banco.punti<7.5)
			{
				  banco.carta=banco.Assegna_carta();
				  controllo_carte(banco.carta, carta);
			      banco.Stampa_carta(banco.carta);
			      
			        if(banco.carta<=7)
			            banco.punti+=banco.carta;
			        else
					    banco.punti+=0.5;
				
				  Sleep(500);
			}
		}
		else
		{
		 while(banco.punti<=giocatore.punti-punticarta1)
		 {
			banco.carta=banco.Assegna_carta();
			controllo_carte(banco.carta, carta);
			banco.Stampa_carta(banco.carta);
			
			if(banco.carta<=7)
			  banco.punti+=banco.carta;
			else
			  banco.punti+=0.5;
			
			Sleep(500);
		 }
	    }
	    Sleep(500);
		cout<<endl<<"Il banco ha realizzato: "<<banco.punti<<" punti."<<endl;
		if(banco.punti>=giocatore.punti && banco.punti<=7.5)
		{
			Sleep(500);
		  cout<<"Peccato, hai perso questo round!!!"<<endl<<endl;
		  banco.gettoni+=giocatore.puntata;
	      giocatore.gettoni-=giocatore.puntata;
		  banco.totp++;
	    }
		else
		{
			if(banco.punti<giocatore.punti)
			{
			Sleep(500);
		       cout<<"Complimenti, hai vinto questo round!!!"<<endl<<endl;
		       banco.gettoni-=banco.puntata;
	    	   giocatore.gettoni+=banco.puntata;
		    }
		    else
		    {
		    Sleep(500);
		       cout<<"Il banco ha SBALLATO!!! Hai vinto questo round!!!"<<endl<<endl;
		       banco.gettoni-=banco.puntata;
	    	   giocatore.gettoni+=banco.puntata;
		    }
		       giocatore.totp++;
	    }
	}
    }
      cout<<endl;
       Sleep(500);
       cout<<"***FINE PARTITA***"<<endl<<endl;
    if(giocatore.totp>banco.totp)
       cout<<"Punteggio(banco-giocatore)"<<banco.totp<<" a "<<giocatore.totp<<endl<<"Comlimenti!!! HAI VINTO!!!"<<endl;
    else
    {
    	if(giocatore.totp<banco.totp)
    	 cout<<"Punteggio(banco-giocatore)"<<banco.totp<<" a "<<giocatore.totp<<endl<<"PECCATO!!! HAI PERSO!!!"<<endl;
    	else
    	 cout<<"Punteggio(banco-giocatore)"<<banco.totp<<" a "<<giocatore.totp<<endl<<"HAI PAREGGIATO!!!"<<endl;
    }
    cout<<"La situazione del conto e' la seguente:"<<endl;
    cout<<"Banco: "<<banco.gettoni<<endl;
    cout<<"Tu : "<<giocatore.gettoni<<endl;
    Sleep(500);
    cout<<"Grazie per aver giocato, alla prossima!!!"<<endl<<" THE END "<<endl;
	system("PAUSE");
	return 0;
}



void introduzione(void)
{
	cout<<"Benvenuti in questa nuova partita a 7 e mezzo!!!"<<endl<<endl;
	Sleep(500);
	cout<<"Questo e' un gioco che simula il tradizionale gioco di carte 7 e mezzo,"<<endl;
	cout<<"ma in questa partita si giochera' solo con numeri,"<<endl; 
	cout<<"che rappresentano le carte secondo la seguente legenda:"<<endl;
	cout<<"1 (ASSO) = 1 punto"<<endl<<"2 = 2 punti"<<endl<<"3 = 3 punti"<<endl<<"4 = 4 punti"<<endl<<"5 = 5 punti"<<endl<<"6 = 6 punti"<<endl; 
	cout<<"7 = 7 punti"<<endl;
	cout<<"8, 9 e 10 equivalgono alle figure e quindi = 0.5 punti"<<endl;
	cout<<"Come detto, questa e' una simulazione, quindi in questo gioco non sono"<<endl;
	cout<<"presenti i semi delle carte (denara, bastoni, spade e coppe) e non e'"<<endl;
	cout<<"possibile fare sette e mezzo con il 10 a denara."<<endl;
	cout<<"L'obiettivo e' cercare di fare piu' punti del banco,"<<endl;
	cout<<"non superando pero' il limite del 7 e mezzo, o magari fare proprio 7 e mezzo."<<endl;
	cout<<"All' inizio del gioco deciderai con quanti gettoni giocare, alla fine della"<<endl;
	cout<<"partita vedrai la situazione del conto; se finisci i gettoni prima della fine"<<endl;
	cout<<"della partita, essa non finira', ma alla fine, nella situazione del conto,"<<endl;
	cout<<"i numeri negativi indicheranno di quanto sei sotto."<<endl;
	cout<<"ATTENZIONE: non c'e' trucco e non c'e' inganno,"<<endl; 
	cout<<"i numeri sono generati casualmente."<<endl;
	cout<<"Buona partita!!!"<<endl<<endl;
	Sleep(500);
}

void controllo_carte(int &C, int cart[])
{
		if(cart[0]==4 && cart[1]==4 && cart[2]==4 && cart[3]==4 && cart[4]==4 && cart[5]==4 && cart[6]==4 && cart[7]==4 && cart[8]==4 && cart[9]==4)
	{
        cout<<"Rimescolamento carte...\n";
        Sleep(1000);
		cart[0]=0;
		cart[1]=0;
		cart[2]=0;
		cart[3]=0;
		cart[4]=0;
		cart[5]=0;
		cart[6]=0;
		cart[7]=0;
		cart[8]=0;
		cart[9]=0;
	}

	switch(C)
	{
		case 1:
			cart[0]++;
			if(cart[0]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
		     break;
		case 2:
			cart[1]++;
			if(cart[1]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
		     break;
		case 3:
			cart[2]++;
			if(cart[2]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
		      break;
		case 4:
			cart[3]++;
			if(cart[3]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
			   break;
		case 5:
			cart[4]++;
			if(cart[4]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
			  break;
		case 6:
			cart[5]++;
				if(cart[5]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
			   break;
		case 7:
			cart[6]++;
			if(cart[6]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
				break;
		case 8:
			cart[7]++;
			if(cart[7]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
				break;
		case 9:
			cart[8]++;
			if(cart[8]>=4)
			{
			    C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
				break;
		case 10:
			cart[9]++;
			if(cart[9]>=4)
			{
				C= rand() % 10 + 1;
				controllo_carte(C, cart);
			}
			else
				break;
	}
}









