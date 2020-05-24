#ifndef GESTIONE_PLAYLIST_H_
#define GESTIONE_PLAYLIST_H_

#define DIMNOME 30
#define DIMDESC 250

typedef struct {
	int id;
	int utente;
	char nome[DIMNOME];
	char descrizione[DIMDESC];
	int pubblica;
	int eliminata;
} playlist;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_playlist(playlist playlist_selezionata);
int leggi_utente_playlist(playlist playlist_selezionata);
void leggi_nome_playlist(playlist playlist_selezionata, char *nome_letto);
void leggi_descrizione_playlist(playlist playlist_selezionata, char *descrizione_letta);
int leggi_flag_eliminato_playlist(playlist playlist_selezionata);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_playlist(playlist *playlist_selezionata, int id);
void scrivi_utente_playlist(playlist *playlist_selezionata, int utente);
void scrivi_nome_playlist(playlist *playlist_selezionata, char *nome);
void scrivi_descrizione_playlist(playlist *playlist_selezionata, char *descrizione);
void scrivi_flag_eliminato_playlist(playlist *playlist_selezionata, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_playlist(playlist *playlist_selezionata);
void mostra_playlists();
void mostra_playlist(playlist playlist_selezionata);
long posizione_playlist(int id_playlist);
int elimina_playlist(int id_playlist);
playlist cerca_playlist(int id_playlist);
int modifica_playlist(int id_playlist, playlist playlist_modificato);

#endif /* GESTIONE_PLAYLIST_H_ */
