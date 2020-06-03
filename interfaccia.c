#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genera_id.h"
#include "gestione_brani.h"
#include "gestione_generi.h"
#include "gestione_utenti.h"
#include "gestione_artisti.h"
#include "gestione_playlist.h"
#include "gestione_relazioni.h"
#include "ricerca.h"
#include "interfaccia.h"

void leggere_intero(int *valore)
{
	scanf("%d", valore);
	while ((getchar()) != '\n')
		; // Rimuovo il newline
}

void leggere_stringa(char *stringa)
{
	scanf("%[^\n]s", stringa); // Uso un'espressione regolare per leggere sia gli spazi, sia il newline
	while ((getchar()) != '\n')
		; // e rimuovo il newline
}

void pulisci_schermo()
{
	system("@cls||clear");
}

void logo()
{
	printf(" _____  _                           			\n");
	printf("|  __ \\| |                          			\n");
	printf("| |__) | |__   ___  _ __   ___  ___ 			\n");
	printf("|  ___/| '_ \\ / _ \\| '_ \\ / _ \\/ __|		\n");
	printf("| |    | | | | (_) | | | | (_) \\__ \\			\n");
	printf("|_|    |_| |_|\\___/|_| |_|\\___/|___/			\n");

	printf("\n\n");
}

void titolo()
{
	pulisci_schermo();
	logo();
}

void replay()
{
	system("pause");
	titolo();
	interfaccia_principale();
}

void interfaccia_principale()
{
	utente utente_corrente;

	titolo();

	utente_corrente = leggi_utente_corrente();

	if(utente_corrente.admin == 1){
		interfaccia_admin();
	} else if(utente_corrente.admin == 0){
		interfaccia_utente();
	} else {
		interfaccia_iniziale();
	}
}

void interfaccia_iniziale(){
	int scelta;

	printf("[1] Login				\n");
	printf("[2] Registrati			\n");

	printf("\nScegli una delle opzioni: ");
	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_login();
	else if (scelta == 2)		interfaccia_registrazione();
	else						printf("\nValore non valido, si prega di riprovare \n");

	replay();
}

void interfaccia_utente(){
	int scelta;

	titolo();

	printf("[1] Visualizza tutti i brani		\n");
	printf("[2] Visualizza tutti gli artisti	\n");
	printf("[3] Visualizza tutti i generi		\n");
	printf("[4] Visualizza tutte le playlist	\n");
	printf("[5] Aggiungi un brano				\n");
	printf("[6] Aggiungi un artista				\n");
	printf("[7] Aggiungi una playlist			\n");

	printf("\nScegli una delle opzioni: ");
	leggere_intero(&scelta);

	if (scelta == 1)			mostra_brani();
	else if (scelta == 2)		mostra_artisti();
	else if (scelta == 3)		mostra_generi();
	else if (scelta == 4)		mostra_playlists();
	else if (scelta == 5)		interfaccia_inserimento_brano();
	else if (scelta == 6)		interfaccia_inserimento_artista();
	else if (scelta == 7)		interfaccia_inserimento_playlist();
	else						printf("\nValore non valido, si prega di riprovare \n");

	replay();
}

void interfaccia_admin(){
	printf("\nDa fare :)\n");
}

void interfaccia_inserimento_brano()
{
	brano nuovo_brano;
	brano_artista relazione_branoArtista;
	brano_genere relazione_branoGenere;
	char titolo_brano[DIMSTRING];
	int anno_brano;
	int durata_brano;
	int id_brano;
	int id_artista;
	int id_genere;
	int brano_aggiunto;
	int relazione_branoArtista_aggiunta;
	int relazione_branoGenere_aggiunta;

	titolo();

	printf("Qual e' il nome del brano? ");
	leggere_stringa(titolo_brano);

	printf("Qual e' l'anno di pubblicazione? ");
	leggere_intero(&anno_brano);

	printf("Indica la durata del brano (in secondi) ");
	leggere_intero(&durata_brano);

	printf("Scegli uno degli artisti presenti su Phonos \n\n");
	mostra_artisti();
	printf("ID artista: ");
	leggere_intero(&id_artista);

	printf("Scegli uno dei generi musicali presenti su Phonos \n\n");
	mostra_generi();
	printf("ID genere: ");
	leggere_intero(&id_genere);

//	Scrivo le informazioni del brano
	id_brano = genera_id();
	scrivi_id_brano(&nuovo_brano, id_brano);
	scrivi_titolo_brano(&nuovo_brano, titolo_brano);
	scrivi_anno_brano(&nuovo_brano, anno_brano);
	scrivi_durata_brano(&nuovo_brano, durata_brano);
	scrivi_ascolti_brano(&nuovo_brano, 0);

//	Definisco le relazioni
	scrivi_relazione_branoArtista(&relazione_branoArtista, id_brano, id_artista);
	scrivi_relazione_branoGenere(&relazione_branoGenere, id_brano, id_genere);

//	Aggiungo il brano
	brano_aggiunto = aggiungi_brano(&nuovo_brano);

//	Aggiungo le relazioni
	relazione_branoArtista_aggiunta = aggiungi_branoArtista(&relazione_branoArtista);
	relazione_branoGenere_aggiunta = aggiungi_branoGenere(&relazione_branoGenere);

	if (brano_aggiunto == 1 && relazione_branoArtista_aggiunta == 1 && relazione_branoGenere_aggiunta == 1){
		printf("\nBrano aggiunto con successo! \n");
	}
	else{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}
}

void interfaccia_inserimento_artista()
{
	artista nuovo_artista;
	char nome_artista[DIMSTRING];
	char cognome_artista[DIMSTRING];
	char nome_arte_artista[DIMSTRING];
	int aggiunto;

	titolo();

	printf("Qual e' il nome dell'artista? ");
	leggere_stringa(nome_artista);

	printf("Qual e' il cognome dell'artista? ");
	leggere_stringa(cognome_artista);

	printf("Qual e' il nome d'arte dell'artista? ");
	leggere_stringa(nome_arte_artista);

	scrivi_nome_artista(&nuovo_artista, nome_artista);
	scrivi_cognome_artista(&nuovo_artista, cognome_artista);
	scrivi_nome_arte_artista(&nuovo_artista, nome_arte_artista);

	aggiunto = aggiungi_artista(&nuovo_artista);

	// controllo che l'aggiunta dell'artista sia avvenuta con successo
	if ( aggiunto == 1 )
	{
		printf("\nArtista aggiunto con successo! \n");
	}
	else
	{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}
}

void interfaccia_inserimento_genere()
{
	genere nuovo_genere;
	char nome_genere[DIMSTRING];
	int aggiunto;

	titolo();

	printf("Qual e' il nome del genere? ");
	leggere_stringa(nome_genere);

	scrivi_nome_genere(&nuovo_genere, nome_genere);

	aggiunto = aggiungi_genere(&nuovo_genere);

	// controllo che l'aggiunta del genere sia avvenuta con successo
	if ( aggiunto == 1 )
	{
		printf("\nGenere aggiunto con successo! \n");
	}
	else
	{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}
}

void interfaccia_inserimento_playlist()
{
	utente utente_corrente;
	playlist nuova_playlist;
	playlist_brano relazione_playlistBrano;
	char nome_playlist[DIMSTRING];
	char descrizione_playlist[DIMDESC];
	int id_playlist;
	int pubblica;
	int playlist_aggiunta;
	int id_brano;

	titolo();

	utente_corrente = leggi_utente_corrente();

	printf("Qual e' il nome della playlist? ");
	leggere_stringa(nome_playlist);

	printf("Scrivi una breve descrizione della playlist ");
	leggere_stringa(descrizione_playlist);

	printf("La playlist e'	\n");
	printf("[1] Pubblica	\n");
	printf("[2] Privata		\n");
	leggere_intero(&pubblica);

//	Scrivo i dati della playlist
	id_playlist = genera_id();
	scrivi_id_playlist(&nuova_playlist, id_playlist);
	scrivi_nome_playlist(&nuova_playlist, nome_playlist);
	scrivi_descrizione_playlist(&nuova_playlist, descrizione_playlist);
	scrivi_utente_playlist(&nuova_playlist, utente_corrente.id);
	if (pubblica == 2)		scrivi_flag_pubblica_playlist(&nuova_playlist, 0);
	else					scrivi_flag_pubblica_playlist(&nuova_playlist, 1);

//	Aggiungo la playlist
	playlist_aggiunta = aggiungi_playlist(&nuova_playlist);

	if (playlist_aggiunta == 1)
	{
		printf("\nPlaylist aggiunta con successo! \n");
		do {
			printf("Scegli un brano da aggiungere alla playlist. \n\n");
			mostra_brani();
			printf("ID brano: (-1 per terminare) ");
			leggere_intero(&id_brano);

			if(id_brano != -1){
				scrivi_relazione_playlistBrano(&relazione_playlistBrano, id_brano, id_playlist);
			}

		} while (id_brano != -1);
	}
	else
	{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}


}

void interfaccia_registrazione()
{
	utente nuovo_utente;
	char nome_utente[DIMUSER];
	char password[DIMPASS];
	int aggiunto;

	titolo();

	printf("Scegli un nome utente ");
	leggere_stringa(nome_utente);

	printf("Scegli una password sicura ");
	leggere_stringa(password);

	scrivi_username_utente(&nuovo_utente, nome_utente);
	scrivi_password_utente(&nuovo_utente, password);

//	Controllo se lo username � stato gi� preso
	if(username_esiste(nome_utente) == 0){
		aggiunto = aggiungi_utente(&nuovo_utente);
		if( aggiunto == 1 )			printf("\nUtente aggiunto con successo \n");
		else 						printf("\nQualcosa e' andato storto. Ti preghiamo di riprovare \n");
	} else {
		printf("\nLo username che hai scelto � gi� stato preso. Prova a sceglierne un altro! \n");
	}
}

void interfaccia_login()
{
	utente utente_login;
	char nome_utente[DIMUSER];
	char password[DIMPASS];
	int utente_esiste;
	int autenticato;

	titolo();

	printf("Nome utente: ");
	leggere_stringa(nome_utente);

	printf("Password: ");
	leggere_stringa(password);

	scrivi_username_utente(&utente_login, nome_utente);
	scrivi_password_utente(&utente_login, password);

	utente_esiste = controllo_presenza_utente(utente_login);

	if( utente_esiste == 1 )
	{
		autenticato = controllo_credenziali(nome_utente, password);
		if(autenticato == 1)
		{
			printf("\nBentornato, %s \n", nome_utente);
		} 
		else 
		{
			printf("\nControlla le credenziali e riprova \n");
		}
	} 
	else 
	{
		printf("\nL'utente non esiste \n");
	}
}
