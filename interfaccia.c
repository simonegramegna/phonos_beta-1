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
#include "recupero_dati.h"
#include "interfaccia.h"

void leggere_intero(int *valore)
{
	scanf("%d", valore);
	while ((getchar()) != '\n');	// Rimuovo il newline
}

void leggere_stringa(char *stringa)
{
	scanf("%[^\n]s", stringa);		// Uso un'espressione regolare per leggere sia gli spazi, sia il newline
	while ((getchar()) != '\n');	// e rimuovo il newline
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
	titolo();

	utente utente_corrente;
	int admin;
	char username[DIMUSER];


	utente_corrente = leggi_utente_corrente();
	admin = leggi_admin_utente(utente_corrente);
	leggi_username_utente(utente_corrente, username);

	if(admin != -1)				printf("Bentornato, %s! \n\n", username);
	if(admin == 1)				interfaccia_admin();
	else if(admin == 0)			interfaccia_utente();
	else 						interfaccia_iniziale();
}

void interfaccia_iniziale()
{
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

void interfaccia_utente()
{
	int scelta;

	printf("[1] Visualizza tutti i brani		\n");
	printf("[2] Visualizza tutti gli artisti	\n");
	printf("[3] Visualizza tutti i generi		\n");
	printf("[4] Visualizza tutte le playlist	\n");
	printf("[5] Visualizza tutti gli album		\n");
	printf("[6] Aggiungi un brano				\n");
	printf("[7] Aggiungi un artista				\n");
	printf("[8] Aggiungi una playlist			\n");
	printf("[9] Aggiungi un album				\n");
	printf("[10] Ricerca						\n");
	printf("[11] Esci							\n");

	printf("\nScegli una delle opzioni: ");
	leggere_intero(&scelta);

	if (scelta == 1)			mostra_brani();
	else if (scelta == 2)		mostra_artisti();
	else if (scelta == 3)		mostra_generi();
	else if (scelta == 4)		mostra_playlists();
	else if (scelta == 5)		mostra_album();
	else if (scelta == 6)		interfaccia_inserimento_brano();
	else if (scelta == 7)		interfaccia_inserimento_artista();
	else if (scelta == 8)		interfaccia_inserimento_playlist();
	else if (scelta == 9)		interfaccia_inserimento_album();
	else if (scelta == 10)		interfaccia_ricerca();
	else if (scelta == 11)		return;
	else						printf("\nValore non valido, si prega di riprovare \n");

	replay();
}

void interfaccia_admin()
{
	int scelta;

	printf("[1] Visualizza tutti i brani				\n");
	printf("[2] Visualizza tutti gli artisti			\n");
	printf("[3] Visualizza tutti i generi				\n");
	printf("[4] Visualizza tutte le playlist			\n");
	printf("[5] Visualizza tutti gli album				\n");
	printf("[6] Aggiungi un brano						\n");
	printf("[7] Aggiungi un artista						\n");
	printf("[8] Aggiungi una playlist					\n");
	printf("[9] Aggiungi un genere						\n");
	printf("[10] Aggiungi un album						\n");
	printf("[11] Modifica un brano						\n");
	printf("[12] Modifica un artista					\n");
	printf("[13] Modifica una playlist					\n");
	printf("[14] Modifica un genere						\n");
	printf("[15] Modifica un album						\n");
	printf("[16] Ricerca								\n");
	printf("[17] Backup dei dati						\n");
	printf("[18] Ripristino dei dati					\n");
	printf("[19] Esci									\n");

	printf("\nScegli una delle opzioni: ");
	leggere_intero(&scelta);

	if (scelta == 1)			mostra_brani();
	else if (scelta == 2)		mostra_artisti();
	else if (scelta == 3)		mostra_generi();
	else if (scelta == 4)		mostra_playlists();
	else if (scelta == 5)		mostra_album();
	else if (scelta == 6)		interfaccia_inserimento_brano();
	else if (scelta == 7)		interfaccia_inserimento_artista();
	else if (scelta == 8)		interfaccia_inserimento_playlist();
	else if (scelta == 9)		interfaccia_inserimento_genere();
	else if (scelta == 10)		interfaccia_inserimento_album();
	else if (scelta == 11)		interfaccia_modifica_brano();
	else if (scelta == 12)		interfaccia_modifica_artista();
	else if (scelta == 13)		interfaccia_modifica_playlist();
	else if (scelta == 14)		interfaccia_modifica_genere();
	else if (scelta == 15)		interfaccia_modifica_album();
	else if (scelta == 16)		interfaccia_ricerca();
	else if (scelta == 17)		interfaccia_backup();
	else if (scelta == 18)		interfaccia_ripristino();
	else if (scelta == 19)		return;
	else						printf("\nValore non valido, si prega di riprovare \n");

	replay();
}

// Inserimenti
void interfaccia_inserimento_brano()
{
	brano nuovo_brano;
	brano_artista relazione_branoArtista;
	brano_genere relazione_branoGenere;
	brano_album relazione_branoAlbum;
	char titolo_brano[DIMTITOLO_BRANO];
	int anno_brano;
	int durata_brano;
	int id_brano;
	int id_artista;
	int id_genere;
	int id_album;
	int brano_aggiunto;
	int relazione_branoArtista_aggiunta;
	int relazione_branoGenere_aggiunta;
	int relazione_branoAlbum_aggiunta;

	titolo();

	printf("Qual e' il nome del brano? ");
	leggere_stringa(titolo_brano);

	printf("Qual e' l'anno di pubblicazione? ");
	leggere_intero(&anno_brano);

	printf("Indica la durata del brano (in secondi) ");
	leggere_intero(&durata_brano);

//	Scelta dell'artista
	titolo();
	printf("Scegli uno degli artisti presenti su Phonos \n\n");
	mostra_artisti();
	printf("ID artista: ");
	leggere_intero(&id_artista);

//	Scelta del genere
	titolo();
	printf("Scegli uno dei generi musicali presenti su Phonos \n\n");
	mostra_generi();
	printf("ID genere: ");
	leggere_intero(&id_genere);

//	Scelta dell'album
	titolo();
	printf("Scegli uno degli album presenti su Phonos \n\n");
	mostra_album();
	printf("ID album: ");
	leggere_intero(&id_album);

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
	scrivi_relazione_branoAlbum(&relazione_branoAlbum, id_brano, id_album);

//	Aggiungo il brano
	brano_aggiunto = aggiungi_brano(&nuovo_brano);

//	Aggiungo le relazioni
	relazione_branoArtista_aggiunta = aggiungi_branoArtista(&relazione_branoArtista);
	relazione_branoGenere_aggiunta = aggiungi_branoGenere(&relazione_branoGenere);
	relazione_branoAlbum_aggiunta = aggiungi_branoAlbum(&relazione_branoAlbum);

	if (brano_aggiunto == 1 && relazione_branoArtista_aggiunta == 1 && relazione_branoGenere_aggiunta == 1 && relazione_branoAlbum_aggiunta == 1)
	{
		printf("\nBrano aggiunto con successo! \n");
	}
	else
	{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}
}

void interfaccia_inserimento_artista()
{
	artista nuovo_artista;
	char nome_artista[DIMNOME_ARTISTA];
	char cognome_artista[DIMNOME_ARTISTA];
	char nome_arte_artista[DIMNOME_ARTISTA];
	int aggiunto;

	titolo();

	printf("Qual e' il nome dell'artista? ");
	leggere_stringa(nome_artista);

	printf("Qual e' il cognome dell'artista? ");
	leggere_stringa(cognome_artista);

	printf("Qual e' il nome d'arte dell'artista? ");
	leggere_stringa(nome_arte_artista);

	scrivi_id_artista(&nuovo_artista, genera_id());
	scrivi_nome_artista(&nuovo_artista, nome_artista);
	scrivi_cognome_artista(&nuovo_artista, cognome_artista);
	scrivi_nome_arte_artista(&nuovo_artista, nome_arte_artista);

	aggiunto = aggiungi_artista(&nuovo_artista);

	// controllo che l'aggiunta dell'artista sia avvenuta con successo
	if ( aggiunto == 1 )			printf("\nArtista aggiunto con successo! \n");
	else							printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_inserimento_genere()
{
	genere nuovo_genere;
	char nome_genere[DIMNOME_GENERE];
	int aggiunto;

	titolo();

	printf("Qual e' il nome del genere? ");
	leggere_stringa(nome_genere);

	scrivi_id_genere(&nuovo_genere, genera_id());
	scrivi_nome_genere(&nuovo_genere, nome_genere);

	aggiunto = aggiungi_genere(&nuovo_genere);

	// controllo che l'aggiunta del genere sia avvenuta con successo
	if ( aggiunto == 1 )			printf("\nGenere aggiunto con successo! \n");
	else							printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_inserimento_playlist()
{
	utente utente_corrente;
	playlist nuova_playlist;
	playlist_brano relazione_playlistBrano;
	char nome_playlist[DIMNOME_PLAYLIST];
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

//	Aggiunta brani
	if (playlist_aggiunta == 1)
	{
		printf("\nPlaylist aggiunta con successo! \n");
		do {
			titolo();
			printf("Scegli un brano da aggiungere alla playlist. \n\n");
			mostra_brani();
			printf("ID brano: (-1 per terminare) ");
			leggere_intero(&id_brano);

			if(id_brano != -1)		scrivi_relazione_playlistBrano(&relazione_playlistBrano, id_brano, id_playlist);

		} while (id_brano != -1);
	}
	else
	{
		printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
	}


}

void interfaccia_inserimento_album()
{
	album nuovo_album;
	char titolo_album[DIMTITOLO_ALBUM];
	int anno_album;
	int aggiunto;

	titolo();

	printf("Qual e' il titolo dell'album? ");
	leggere_stringa(titolo_album);

	printf("Qual e' l'anno di pubblicazione dell'album? ");
	leggere_intero(&anno_album);

	scrivi_id_album(&nuovo_album, genera_id());
	scrivi_titolo_album(&nuovo_album, titolo_album);
	scrivi_anno_album(&nuovo_album, anno_album);

	aggiunto = aggiungi_album(&nuovo_album);

	// controllo che l'aggiunta dell'album sia avvenuta con successo
	if ( aggiunto == 1 )			printf("\nAlbum aggiunto con successo! \n");
	else							printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

// Registrazione e login
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

//	Controllo se lo username ï¿½ stato giï¿½ preso
	if(username_esiste(nome_utente) == 0){
		aggiunto = aggiungi_utente(&nuovo_utente);
		if( aggiunto == 1 )			printf("\nUtente aggiunto con successo \n");
		else 						printf("\nQualcosa e' andato storto. Ti preghiamo di riprovare \n");
	} else {
		printf("\nLo username che hai scelto e' gia' stato preso. Prova a sceglierne un altro! \n");
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

// Ricerca
void interfaccia_ricerca(){
	titolo();

	int scelta;

	printf("Che tipo di ricerca vuoi effettuare? \n");

	printf("[1] Cerca brani				\n");
	printf("[2] Cerca artisti			\n");
	printf("[3] Cerca playlist			\n");
	printf("[4] Cerca album				\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_ricerca_brani();
	else if (scelta == 2)		interfaccia_ricerca_artisti();
	else if (scelta == 3)		interfaccia_ricerca_playlist();
	else if (scelta == 4)		interfaccia_ricerca_album();
	else						printf("\nValore non valido, si prega di riprovare \n");

}

void interfaccia_ricerca_brani(){
	titolo();

	int scelta;

	printf("Come preferisci cercare il brano? \n");

	printf("[1] Cerca per titolo					\n");
	printf("[2] Cerca per anno di pubblicazione		\n");
	printf("[3] Cerca per durata					\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_ricerca_brano_per_titolo();
	else if (scelta == 2)		interfaccia_ricerca_brano_per_anno();
	else if (scelta == 3)		interfaccia_ricerca_brano_per_durata();
	else						printf("\nValore non valido, si prega di riprovare \n");
}

void interfaccia_ricerca_brano_per_titolo(){
	titolo();

	char titolo[DIMTITOLO_BRANO];

	printf("Qual e' il titolo del brano? ");
	leggere_stringa(titolo);

	ricerca_brani_titolo(titolo);
}

void interfaccia_ricerca_brano_per_anno(){
	titolo();

	int anno;

	printf("Qual e' l'anno di pubblicazione che ti interessa? ");
	leggere_intero(&anno);

	ricerca_brani_anno(anno);
}

void interfaccia_ricerca_brano_per_durata(){
	titolo();

	int durata;

	printf("Indica una durata (in minuti) approssimativa ");
	leggere_intero(&durata);

	ricerca_brani_durata(durata);
}

void interfaccia_ricerca_artisti(){
	titolo();

	int scelta;

	printf("Come preferisci cercare l'artista? \n");

	printf("[1] Cerca per nome				\n");
	printf("[2] Cerca per nome d'arte		\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_ricerca_artista_per_nome();
	else if (scelta == 2)		interfaccia_ricerca_artista_per_nome_arte();
	else						printf("\nValore non valido, si prega di riprovare \n");
}

void interfaccia_ricerca_artista_per_nome(){
	titolo();

	char nome[DIMNOME_ARTISTA];

	printf("Qual e' il nome dell'artista? ");
	leggere_stringa(nome);

	ricerca_artisti_nome(nome);
}

void interfaccia_ricerca_artista_per_nome_arte(){
	titolo();

	char nome_arte[DIMNOMEARTE_ARTISTA];

	printf("Qual e' il nome d'arte dell'artista? ");
	leggere_stringa(nome_arte);

	ricerca_artisti_nome_arte(nome_arte);
}

void interfaccia_ricerca_playlist(){
	titolo();

	char nome[DIMNOME_PLAYLIST];

	printf("Qual e' il nome della playlist? ");
	leggere_stringa(nome);

	ricerca_playlist_pubbliche_nome(nome);
}

void interfaccia_ricerca_album(){
	titolo();

	int scelta;

	printf("Come preferisci cercare l'album? \n");

	printf("[1] Cerca per titolo					\n");
	printf("[2] Cerca per anno di pubblicazione		\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_ricerca_album_per_titolo();
	else if (scelta == 2)		interfaccia_ricerca_album_per_anno();
	else						printf("\nValore non valido, si prega di riprovare \n");
}

void interfaccia_ricerca_album_per_titolo(){
	titolo();

	char titolo[DIMTITOLO_BRANO];

	printf("Qual e' il titolo dell'album? ");
	leggere_stringa(titolo);

	ricerca_album_titolo(titolo);
}

void interfaccia_ricerca_album_per_anno(){
	titolo();

	int anno;

	printf("Qual e' l'anno di pubblicazione che ti interessa? ");
	leggere_intero(&anno);

	ricerca_album_anno(anno);
}

// Backup e ripristino
void interfaccia_backup(){
	titolo();

	int scelta;

	printf("Che tipo di backup vuoi effettuare? \n");

	printf("[1] Backup brani			\n");
	printf("[2] Backup artisti			\n");
	printf("[3] Backup playlist			\n");
	printf("[4] Backup album				\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_backup_brani();
	else if (scelta == 2)		interfaccia_backup_artisti();
	else if (scelta == 3)		interfaccia_backup_playlist();
	else if (scelta == 4)		interfaccia_backup_album();
	else						printf("\nValore non valido, si prega di riprovare \n");
}

void interfaccia_backup_brani(){
	int esito;
	esito = backup_brani();

	if(esito == 1)		printf("Backup dei brani effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_backup_artisti(){
	int esito;
	esito = backup_artisti();

	if(esito == 1)		printf("Backup degli artisti effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_backup_playlist(){
	int esito;
	esito = backup_playlist();

	if(esito == 1)		printf("Backup delle playlist effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_backup_album(){
	int esito;
	esito = backup_album();

	if(esito == 1)		printf("Backup degli album effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_ripristino(){
	titolo();

	int scelta;

	printf("Cosa desideri ripristinare? \n");

	printf("[1] Ripristina brani			\n");
	printf("[2] Ripristina artisti			\n");
	printf("[3] Ripristina playlist			\n");
	printf("[4] Ripristina album			\n");

	leggere_intero(&scelta);

	if (scelta == 1)			interfaccia_ripristino_brani();
	else if (scelta == 2)		interfaccia_ripristino_artisti();
	else if (scelta == 3)		interfaccia_ripristino_playlist();
	else if (scelta == 4)		interfaccia_ripristino_album();
	else						printf("\nValore non valido, si prega di riprovare \n");
}

void interfaccia_ripristino_brani(){
	int esito;
	esito = ripristina_brani();

	if(esito == 1)		printf("Ripristino dei brani effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_ripristino_artisti(){
	int esito;
	esito = ripristina_artisti();

	if(esito == 1)		printf("Ripristino degli artisti effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_ripristino_playlist(){
	int esito;
	esito = ripristina_playlist();

	if(esito == 1)		printf("Ripristino delle playlist effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_ripristino_album(){
	int esito;
	esito = ripristina_album();

	if(esito == 1)		printf("Ripristino degli album effettuato con successo \n");
	else				printf("Qualcosa è andato storto, ti preghiamo di riprovare \n");
}

// Modifica
void interfaccia_modifica_brano(){
	titolo();

	int id_brano;
	brano brano_trovato;
	char titolo_brano[DIMTITOLO_BRANO];
	int anno_brano;
	int durata_brano;
	int esito;

	mostra_brani();
	printf("ID del brano da modificare: ");
	leggere_intero(&id_brano);

	brano_trovato = cerca_brano(id_brano);
	leggi_titolo_brano(brano_trovato, titolo_brano);
	anno_brano = leggi_anno_brano(brano_trovato);
	durata_brano = leggi_durata_brano(brano_trovato);

	printf("Titolo [%s]:", titolo_brano);
	leggere_stringa(titolo_brano);
	scrivi_titolo_brano(&brano_trovato, titolo_brano);

	printf("Anno [%d]:", anno_brano);
	leggere_intero(&anno_brano);
	scrivi_anno_brano(&brano_trovato, anno_brano);

	printf("Durata [%d]:", durata_brano);
	leggere_intero(&durata_brano);
	scrivi_durata_brano(&brano_trovato, durata_brano);

	esito = modifica_brano(brano_trovato);

	if(esito == 1)		printf("\nBrano modificato con successo \n");
	else				printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_modifica_artista(){
	titolo();

	int id_artista;
	artista artista_trovato;
	char nome_artista[DIMNOME_ARTISTA];
	char cognome_artista[DIMCOGNOME_ARTISTA];
	char nome_arte_artista[DIMNOMEARTE_ARTISTA];
	int esito;

	mostra_artisti();
	printf("ID dell'artista da modificare: ");
	leggere_intero(&id_artista);

	artista_trovato = cerca_artista(id_artista);
	leggi_nome_artista(artista_trovato, nome_artista);
	leggi_cognome_artista(artista_trovato, cognome_artista);
	leggi_nome_arte_artista(artista_trovato, nome_arte_artista);

	printf("Nome [%s]:", nome_artista);
	leggere_stringa(nome_artista);
	scrivi_nome_artista(&artista_trovato, nome_artista);

	printf("Cognome [%s]:", cognome_artista);
	leggere_stringa(cognome_artista);
	scrivi_cognome_artista(&artista_trovato, cognome_artista);

	printf("Nome d'arte [%s]:", nome_arte_artista);
	leggere_stringa(nome_arte_artista);
	scrivi_nome_arte_artista(&artista_trovato, nome_arte_artista);

	esito = modifica_artista(artista_trovato);

	if(esito == 1)		printf("\nArtista modificato con successo \n");
	else				printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_modifica_playlist(){
	titolo();

	int id_playlist;
	playlist playlist_trovata;
	char nome_playlist[DIMNOME_PLAYLIST];
	char descrizione_playlist[DIMDESC];
	int esito;

	mostra_playlists();
	printf("ID della playlist da modificare: ");
	leggere_intero(&id_playlist);

	playlist_trovata = cerca_playlist(id_playlist);
	leggi_nome_playlist(playlist_trovata, nome_playlist);
	leggi_descrizione_playlist(playlist_trovata, descrizione_playlist);

	printf("Nome [%s]:", nome_playlist);
	leggere_stringa(nome_playlist);
	scrivi_nome_playlist(&playlist_trovata, nome_playlist);

	printf("Descrizione [%s]:", descrizione_playlist);
	leggere_stringa(descrizione_playlist);
	scrivi_descrizione_playlist(&playlist_trovata, descrizione_playlist);

	esito = modifica_playlist(playlist_trovata);

	if(esito == 1)		printf("\nPlaylist modificata con successo \n");
	else				printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_modifica_genere(){
	titolo();

	int id_genere;
	genere genere_trovato;
	char nome_genere[DIMNOME_GENERE];
	int esito;

	mostra_generi();
	printf("ID del genere da modificare: ");
	leggere_intero(&id_genere);

	genere_trovato = cerca_genere(id_genere);
	leggi_nome_genere(genere_trovato, nome_genere);

	printf("Nome [%s]:", nome_genere);
	leggere_stringa(nome_genere);
	scrivi_nome_genere(&genere_trovato, nome_genere);

	esito = modifica_genere(genere_trovato);

	if(esito == 1)		printf("\nGenere modificato con successo \n");
	else				printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}

void interfaccia_modifica_album(){
	titolo();

	int id_album;
	album album_trovato;
	char titolo_album[DIMTITOLO_ALBUM];
	int esito;

	mostra_album();
	printf("ID dell'album da modificare: ");
	leggere_intero(&id_album);

	album_trovato = cerca_album(id_album);
	leggi_titolo_album(album_trovato, titolo_album);
	scrivi_titolo_album(&album_trovato, titolo_album);

	printf("Titolo [%s]:", titolo_album);
	leggere_stringa(titolo_album);
	scrivi_titolo_album(&album_trovato, titolo_album);

	esito = modifica_album(album_trovato);

	if(esito == 1)		printf("\nAlbum modificato con successo \n");
	else				printf("\nQualcosa e' andato storto, ti preghiamo di riprovare \n");
}
