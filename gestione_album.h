#ifndef GESTIONE_ALBUM_H_
#define GESTIONE_ALBUM_H_

// dimensione massima del titolo di un album
#define DIMSTRING 30

// definisco tipod di dato album
typedef struct {
	int id;
	char titolo[DIMSTRING];
	int anno;
	int eliminato;
}album;

/* -------------------------
	Funzioni di lettura
------------------------- */

// lettura dell'identificativo di un album
int leggi_id_album(album album_selezionato);

// lettura del titolo di un album 
void leggi_titolo_album(album album_selezionato, char *titolo_letto);

// lettura dell'anno di un album
int leggi_anno_album(album album_selezionato);

// lettura del flag di eliminazione di un album
int leggi_flag_eliminato_album(album album_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */

// scrittura dell'identificativo di un album
void scrivi_id_album(album *album_selezionato, int id);

// scrittura del titolo di un album 
void scrivi_titolo_album(album *album_selezionato, char *titolo);

// scrittura del titolo di un album
void scrivi_anno_album(album *album_selezionato, int anno);

// scrittura del flag di eliminazione di un album
void scrivi_flag_eliminato_album(album *album_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_album(album *album_selezionato);
void mostra_album();
void mostra_album_singolo(album album_selezionato);
long posizione_album(int id_album);
int elimina_album(int id_album);
album cerca_album(int id_album);
int modifica_album( album album_modificato );


#endif /* GESTIONE_ALBUM_H_ */
