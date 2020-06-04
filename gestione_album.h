#ifndef GESTIONE_ALBUM_H_
#define GESTIONE_ALBUM_H_

// dimensione massima del titolo di un album
#define DIMTITOLO_ALBUM 30

// definisco tipo di dato album
typedef struct {
	int id;
	char titolo[DIMTITOLO_ALBUM];
	int anno;
	int eliminato;
}album;

/* -------------------------
	Funzioni di lettura
------------------------- */

// lettura dell'identificativo di un album
int leggi_id_album( album album_selezionato );

// lettura del titolo di un album 
void leggi_titolo_album( album album_selezionato, char *titolo_letto );

// lettura dell'anno di un album
int leggi_anno_album( album album_selezionato );

// lettura del flag di eliminazione di un album
int leggi_flag_eliminato_album( album album_selezionato );

/* -------------------------
	Funzioni di scrittura
------------------------- */

// scrittura dell'identificativo di un album
void scrivi_id_album( album *album_selezionato, int id );

// scrittura del titolo di un album 
void scrivi_titolo_album( album *album_selezionato, char *titolo );

// scrittura del titolo di un album
void scrivi_anno_album( album *album_selezionato, int anno );

// scrittura del flag di eliminazione di un album
void scrivi_flag_eliminato_album( album *album_selezionato, int flag_eliminato );

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un album nella tabella
int aggiungi_album(album *album_selezionato);

// funzione per mostrare tutti gli album 
void mostra_album();

// funzione per mostrare le informazioni di un singolo album
void mostra_album_singolo( album album_selezionato );

// funzione per cercare la posizione di un album nella tabella 
long posizione_album( int id_album );

// funzione per eliminare un album nella tabella 
int elimina_album( int id_album );

// funzione per leggere un album con un determinato id
album cerca_album( int id_album );

// funzione per modificare un determinato album
int modifica_album( album album_modificato );


#endif /* GESTIONE_ALBUM_H_ */
