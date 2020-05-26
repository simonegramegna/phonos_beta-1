#include <stdio.h>
#include <stdlib.h>

#include "gestione_brani.h"
#include "gestione_generi.h"
#include "gestione_utenti.h"
#include "gestione_artisti.h"
#include "interfaccia.h"

void pulisci_schermo(){
	system("@cls||clear");
}

void logo(){
	printf(" _____  _                           			\n");
	printf("|  __ \\| |                          			\n");
	printf("| |__) | |__   ___  _ __   ___  ___ 			\n");
	printf("|  ___/| '_ \\ / _ \\| '_ \\ / _ \\/ __|		\n");
	printf("| |    | | | | (_) | | | | (_) \\__ \\			\n");
	printf("|_|    |_| |_|\\___/|_| |_|\\___/|___/			\n");
}

void titolo()
{
	pulisci_schermo();
	logo();
}

void interfaccia_principale()
{
	int scelta;

	titolo();

	printf("[1] Visualizza tutti i brani		\n");
	printf("[2] Visualizza tutti gli artisti	\n");
	printf("[3] Visualizza tutti i generi		\n");
	printf("[4] Visualizza tutte le playlist	\n");
	printf("[5] Aggiungi un brano				\n");
	printf("[6] Aggiungi un artista				\n");
	printf("[7] Aggiungi un genere				\n");
	printf("[8] Aggiungi una playlist			\n");
	printf("[9] Registrati						\n");
	printf("[10] Accedi							\n");

	printf("\nScegli una delle opzioni: ");
	scanf("%d", &scelta);

	if(scelta == 1)
	{
		mostra_brani();
	}
	else if(scelta == 2)
	{ 
		mostra_artisti();
	}
	else if(scelta == 3)
	{ 
		mostra_generi();
	}
	else if(scelta == 4)
	{
		//mostra_playlists();
	}
	else if(scelta == 5)
	{
		interfaccia_inserimento_brano();
	} 
	else if(scelta == 6)
	{
		//interfaccia_inserimento_artista();
	}
	else if(scelta == 7)
	{
	 	//interfaccia_inserimento_genere();
	}
	else if(scelta == 8)
	{
		//interfaccia_inserimento_playlist();
	}
	else if(scelta == 9)
	{
		//interfaccia_registrazione();
	}
	else if(scelta == 10)
	{ 
		//interfaccia_login();
	}
	else
	{
		printf("Valore non valido, si prega di riprovare \n");
		titolo();
		interfaccia_principale();
	}
}

void interfaccia_inserimento_brano(){
	brano nuovo_brano;
	char titolo_brano[DIMTITOLO];
	int anno_brano;
	int durata_brano;
	int aggiunto;

	titolo();
	printf("Qual e' il nome del brano? ");
	scanf("%s", titolo_brano);

	printf("Qual e' l'anno di pubblicazione? ");
	scanf("%d", &anno_brano);

	printf("Indica la durata del brano (in secondi) ");
	scanf("%d", &durata_brano);

	scrivi_titolo_brano(&nuovo_brano, titolo_brano);
	scrivi_anno_brano(&nuovo_brano, anno_brano);

	aggiunto = aggiungi_brano(&nuovo_brano);
	if(aggiunto == 1){
		printf("\n Brano aggiunto con successo! \n");
	} else {
		printf("\n Qualcosa e' andato storto, ti preghiamo di riprovare \n");
	}
}

