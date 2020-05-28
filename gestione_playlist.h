#ifndef GESTIONE_PLAYLIST_H_
#define GESTIONE_PLAYLIST_H_

// dimensione massima del nome di una playlist 
#define DIMNOME 30

// dimensione massima della descrizione di una playlist
#define DIMDESC 250

// definisco tipo di dato playlist
typedef struct {

	int id;
	int utente;
	char nome[DIMNOME];
	char descrizione[DIMDESC];
	int pubblica;
	int eliminata;

}playlist;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere  l'id di una playlist
int leggi_id_playlist(playlist playlist_selezionata);

// funzione per leggere l'utente di una playlist 
int leggi_utente_playlist(playlist playlist_selezionata);

// funzione per leggere il nome di una playlist
void leggi_nome_playlist(playlist playlist_selezionata, char *nome_letto);

// funzione per leggere la descrizione di una playlist
void leggi_descrizione_playlist(playlist playlist_selezionata, char *descrizione_letta);

// funzione per leggere il flag pubblica di una playlist
int leggi_flag_pubblica_playlist(playlist playlist_selezionata);

// funzione per leggere il flag di eliminazione di una playlist
int leggi_flag_eliminato_playlist(playlist playlist_selezionata);

/* -------------------------
	Funzioni di scrittura
------------------------- */

// funzione per scrivere l'id di una playlist
void scrivi_id_playlist(playlist *playlist_selezionata, int id);

// funzione per scrivere l'utente di una playlist
void scrivi_utente_playlist(playlist *playlist_selezionata, int utente);

// funzione per scrivere il nome di una playlist 
void scrivi_nome_playlist(playlist *playlist_selezionata, char *nome);

// funzione per scrivere la descrizione di una playlist
void scrivi_descrizione_playlist(playlist *playlist_selezionata, char *descrizione);

// funzione per rendere pubblica o privata una playlist
void scrivi_flag_pubblica_playlist(playlist *playlist_selezionata, int flag_pubblica);

// funzione per scrivere il flag di eliminazione di una playlist
void scrivi_flag_eliminato_playlist(playlist *playlist_selezionata, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere una playlist alla tabella
int aggiungi_playlist(playlist *playlist_selezionata);

// funzione per mostrare tutte le playlist della tabella
void mostra_playlists();

// funzione per stampare i dati di una palylist 
void mostra_playlist(playlist playlist_selezionata);

// funzione per cercare la posizione di una playlist all'interno della tabella
long posizione_playlist(int id_playlist);

// funzione per eliminare una playlist con un determinato id 
int elimina_playlist(int id_playlist);

// funzione per cercare una playlist con un determinato id
playlist cerca_playlist(int id_playlist);

// funzione per modificare una playlist
int modifica_playlist( playlist playlist_modificata );

#endif /* GESTIONE_PLAYLIST_H_ */
