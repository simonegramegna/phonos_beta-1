#ifndef GESTIONE_ARTISTI_H_
#define GESTIONE_ARTISTI_H_

#define DIMSTRING 30

typedef struct {
	int id;
	char nome[DIMSTRING];
	char cognome[DIMSTRING];
	char nome_arte[DIMSTRING];
	int eliminato;
} artista;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_artista(artista artista_selezionato);
void leggi_nome_artista(artista artista_selezionato, char *nome_letto);
void leggi_cognome_artista(artista artista_selezionato, char *cognome_letto);
void leggi_nome_arte_artista(artista artista_selezionato, char *nome_arte_letto);
int leggi_flag_eliminato_artista(artista artista_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_artista(artista *artista_selezionato, int id);
void scrivi_nome_artista(artista *artista_selezionato, char *nome);
void scrivi_cognome_artista(artista *artista_selezionato, char *cognome);
void scrivi_nome_arte_artista(artista *artista_selezionato, char *nome_arte);
void scrivi_flag_eliminato_artista(artista *artista_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_artista(artista *artista_selezionato);
void mostra_artisti();
void mostra_artista(artista artista_selezionato);
long posizione_artista(int id_artista);
int elimina_artista(int id_artista);
artista cerca_artista(int id_artista);
int modifica_artista(artista artista_modificato);

#endif /* GESTIONE_ARTISTI_H_ */
