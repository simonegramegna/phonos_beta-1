#ifndef GESTIONE_ARTISTI_H_
#define GESTIONE_ARTISTI_H_

// definisco dimensione massima del nome di un artista
#define DIMSTRING 30

// definisco tipo di dato artista
typedef struct{

	int id;
	char nome[DIMSTRING];
	char cognome[DIMSTRING];
	char nome_arte[DIMSTRING];
	int eliminato;

}artista;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere l'id di un artista
int leggi_id_artista( artista artista_selezionato );

// funzione per leggere il nome di una artista
void leggi_nome_artista( artista artista_selezionato, char *nome_letto );

// funzione per leggere il cognome di un artista
void leggi_cognome_artista( artista artista_selezionato, char *cognome_letto );

// funzione per leggere il nome d'arte di un artista
void leggi_nome_arte_artista( artista artista_selezionato, char *nome_arte_letto );

// funzione per leggere il flag di eliminazione di un artista
int leggi_flag_eliminato_artista( artista artista_selezionato );

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_artista(artista *artista_selezionato, int id);
void scrivi_nome_artista(artista *artista_selezionato, char *nome);

// funzione per scrivere il cognome di un artista
void scrivi_cognome_artista( artista *artista_selezionato, char *cognome );

// funzione per scrivere il nome d'arte di un artista
void scrivi_nome_arte_artista( artista *artista_selezionato, char *nome_arte );

// funzione per scrivere il flag di eliminazione di un artista
void scrivi_flag_eliminato_artista( artista *artista_selezionato, int flag_eliminato );

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un artista alla tabella
int aggiungi_artista( artista *artista_selezionato );

// funzione per mostrare tutti gli artisti nella tabella
void mostra_artisti();

// funzione per mostrare a video l'artista selezionato
void mostra_artista( artista artista_selezionato );

// funzione per cercare la poszione di una artista con determinato id nella tabella
long posizione_artista( int id_artista );

// funzione per eliminare un artista con un determinato id
int elimina_artista( int id_artista );

// funzione per leggere un artista con determinato id
artista cerca_artista( int id_artista );

// funzione per modificare un artista
int modifica_artista( artista artista_modificato );

#endif /* GESTIONE_ARTISTI_H_ */
