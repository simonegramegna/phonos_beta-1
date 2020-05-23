#ifndef GESTIONE_ALBUM_H_
#define GESTIONE_ALBUM_H_

#define DIMSTRING 30

typedef struct {
	int id;
	char titolo[DIMSTRING];
	int anno;
	int eliminato;
} album;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_album(album album_selezionato);
void leggi_titolo_album(album album_selezionato, char *titolo_letto);
int leggi_anno_album(album album_selezionato);
int leggi_flag_eliminato_album(album album_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_album(album *album_selezionato, int id);
void scrivi_titolo_album(album *album_selezionato, char *titolo);
void scrivi_anno_album(album *album_selezionato, int anno);
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
int modifica_album(int id_album, album album_modificato);


#endif /* GESTIONE_ALBUM_H_ */
