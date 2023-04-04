//Gioco sette e mezzo
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<windows.h>
#include<dos.h>
using namespace std;
main()
{
	system("COLOR 2F");
	int carta_giocatore1, carta_giocatore, carta_banco1, carta_banco, cartaG[15], cartaB[15], p=0, q=0, risposta, N, giocatore=0, banco=0, carta[10];
	double puntiG, puntiB, punticarta1;
	srand(time(NULL));
	cout<<"Benvenuti in questa nuova partita a 7 e mezzo NumBer!!!"<<endl<<endl;
	Sleep(500);
	cout<<"Questo e' un gioco che simula il tradizionale gioco di carte 7 e mezzo,"<<endl;
	cout<<"ma in questa partita si giochera' solo con numeri,"<<endl; 
	cout<<"che rappresentano le carte secondo la seguente legenda:"<<endl;
	cout<<"1 (ASSO) = 1 punto"<<endl<<"2 = 2 punti"<<endl<<"3 = 3 punti"<<endl<<"4 = 4 punti"<<endl<<"5 = 5 punti"<<endl<<"6 = 6 punti"<<endl; 
	cout<<"7 = 7 punti"<<endl;
	cout<<"8, 9 e 10 equivalgono alle figure e quindi = 0.5 punti"<<endl;
	cout<<"In questo gioco non e' presente la matta (10 a denara)"<<endl;
	cout<<"L'obiettivo e' cercare di fare piu' punti del banco,"<<endl;
	cout<<"non superando pero' il limite del 7 e mezzo, o magari fare proprio 7 e mezzo."<<endl;
	cout<<"ATTENZIONE: non c'e' trucco e non c'e' inganno,"<<endl; 
	cout<<"i numeri sono generati casualmente."<<endl;
	cout<<"Buona partita!!!"<<endl<<endl;
	Sleep(500);
	cout<<"Inserisci il numero di round che vuoi giocare:"<<endl;
	cin>>N;
	cout<<endl;
	for(int i=0; i<N; i++)
	{
		Sleep(500);
	    cout<<"***NUOVO ROUND***"<<endl<<endl;
	    Sleep(500);
	//assegno la carta al giocatore
	carta_giocatore1= rand() % 11 + 1;
	cout<<"Questa e' la tua prima carta:"<<endl;
	Sleep(500);
	cout<<carta_giocatore1<<endl;
	
	//controllo carte
    	switch(carta_cartagiocatore1)
	{
		case 1:
			if(carta[0]!=4)
			carta[0]++;
			else
			carta_giocatore1= rand() % 11 + 1;
		break;
		case 2:
			carta[1]++;
		break;
		case 3:
			carta[2]++;
		break;
		case 4:
			carta[3]++;
		break;
		case 5:
			carta[4]++;
		break;
		case 6:
			carta[5]++;
		break;
		case 7:
			carta[6]++;
		break;
		case 8:
			carta[7]++;
		break;
		case 9:
			carta[8]++;
		break;
		case 10:
			carta[9]++;
		break;
	}
	//fine controllo
	
	if(carta_giocatore1<=7)
	    puntiG=carta_giocatore1;
	else
	{
		switch(carta_giocatore1)
		{
			case 8:
			case 9:
			case 10:
				puntiG=0.5;
		}
	}
	

	punticarta1=puntiG;
	//assegno la carta al banco
	carta_banco1= rand() % 10 + 1;
	
	//controllo carte
			switch(carta_cartabanco1)
	{
		case 1:
			carta[0]++;
		break;
		case 2:
			carta[1]++;
		break;
		case 3:
			carta[2]++;
		break;
		case 4:
			carta[3]++;
		break;
		case 5:
			carta[4]++;
		break;
		case 6:
			carta[5]++;
		break;
		case 7:
			carta[6]++;
		break;
		case 8:
			carta[7]++;
		break;
		case 9:
			carta[8]++;
		break;
		case 10:
			carta[9]++;
		break;
	}
	//fine cotrollo
	
	if(carta_banco1<=7)
	    puntiB=carta_banco1;
	else
	{
		switch(carta_banco1)
		{
			case 8:
			case 9:
			case 10:
				puntiB=0.5;
			break;
		}
	}
	

	
	//gioca l'utente
	Sleep(500);
	cout<<"Hai "<<puntiG<<" punti, voui un' altra carta? (Rispondi 1 per si o 2 per no)"<<endl;
	cin>>risposta;
	while(risposta==1)
	{
		carta_giocatore= rand() % 10 + 1;
		cartaG[p] = carta_giocatore;
		Sleep(500);
		cout<<"Carta: "<<cartaG[p]<<endl;
		p++;
		if(carta_giocatore<=7)
	    puntiG+=carta_giocatore;
	    else
	    {
		    switch(carta_giocatore)
		    {
			case 8:
			case 9:
			case 10:
				puntiG+=0.5;
			break;
		    }
	    }
	    if(puntiG>7.5)
	    {
	    	Sleep(500);
	    	cout<<"Con "<<puntiG<<" punti, HAI SBALLATO! Hai perso questo round"<<endl<<endl;
	    	banco++;
	    	break;
	    }
	    else
	    {
	    	if(puntiG<7.5)
	    	{
	    		Sleep(500);
	    		cout<<"Hai "<<puntiG<<" punti, voui un' altra carta? (Rispondi 1 per si o 2 per no)"<<endl<<endl;
	            cin>>risposta;
	    	}
	    	else
	    	{
	    		Sleep(500);
	    		cout<<"Hai fatto 7 e mezzo!!! Complimenti hai vinto questo round!!!"<<endl<<endl;
	    		giocatore++;
	    		break;
	    	}
	    }
	}
	if(puntiG>=7.5)
	{
		Sleep(500);
		cout<<"Il banco possedeva "<<carta_banco1<<" con "<<puntiB<<" punti."<<endl<<endl;
	}
	else
	{
		Sleep(500);
		cout<<"Il banco ha:"<<endl;
		Sleep(500);
		cout<<"Prima carta: "<<carta_banco1<<endl;  //gioca il banco
		if(puntiG-punticarta1==0)
		{
			while((puntiB!=6 || puntiB!=6.5 || puntiB!=7) && puntiB<7.5)
			{
				  carta_banco= rand() % 10 + 1;
			      cartaB[q]=carta_banco;
			      Sleep(700);
			      cout<<"Carta: "<<cartaB[q]<<endl;
			      q++;
			        if(carta_banco<=7)
			            puntiB+=carta_banco;
			        else
			        {
				        switch(carta_banco)
				       {
				          case 8:
				          case 9:
				          case 10:
					      puntiB+=0.5;
				          break;
			           }
			        }
			        Sleep(500);
			}
		}
		else
		{
		 while(puntiB<=puntiG-punticarta1)
		 {
			carta_banco= rand() % 10 + 1;
			cartaB[q]=carta_banco;
			Sleep(700);
			cout<<"Carta: "<<cartaB[q]<<endl;
			q++;
			if(carta_banco<=7)
			  puntiB+=carta_banco;
			else
			{
				switch(carta_banco)
				{
				case 8:
				case 9:
				case 10:
					puntiB+=0.5;
				break;
			    }
			}	
			Sleep(500);
		 }
	    }
	    Sleep(500);
		cout<<endl<<"Il banco ha realizzato: "<<puntiB<<" punti."<<endl;
		if(puntiB>=puntiG && puntiB<=7.5)
		{
			Sleep(500);
		  cout<<"Peccato, hai perso questo round!!!"<<endl<<endl;
		  banco++;
	    }
		else
		{
			if(puntiB<puntiG)
			{
			Sleep(500);
		       cout<<"Complimenti, hai vinto questo round!!!"<<endl<<endl;
		    }
		    else
		    {
		    Sleep(500);
		       cout<<"Il banco ha SBALLATO!!! Hai vinto questo round!!!"<<endl<<endl;
		    }
		       giocatore++;
	    }
	}
    }
      cout<<endl;
       Sleep(500);
       cout<<"***FINE PARTITA***"<<endl<<endl;
    if(giocatore>banco)
       cout<<"Punteggio(banco-giocatore)"<<banco<<" a "<<giocatore<<endl<<"Comlimenti!!! HAI VINTO!!!"<<endl;
    else
    {
    	if(giocatore<banco)
    	 cout<<"Punteggio(banco-giocatore)"<<banco<<" a "<<giocatore<<endl<<"PECCATO!!! HAI PERSO!!!"<<endl;
    	else
    	 cout<<"Punteggio(banco-giocatore)"<<banco<<" a "<<giocatore<<endl<<"HAI PAREGGIATO!!!"<<endl;
    }
    Sleep(500);
    cout<<"Grazie per aver giocato, alla prossima!!!"<<endl<<" THE END "<<endl;
	system("PAUSE");
	return 0;
}
