#ifndef GESTIONE_BRANI_H_
#define GESTIONE_BRANI_H_

// definisco dimensione massima del titolo di un brano
#define DIMTITOLO_BRANO 60

// definisco tipo di dato brano
typedef struct{

	int id;
	char titolo[DIMTITOLO_BRANO];
	int durata;
	int anno;
	int ascolti;
	int eliminato;

}brano;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere l'id di un brano
int leggi_id_brano( brano brano_selezionato );

// funzione per leggere il titolo di un brano
void leggi_titolo_brano( brano brano_selezionato, char *titolo_letto );

// funzione per leggere la durata di un brano
int leggi_durata_brano( brano brano_selezionato );

// funzione per leggere l'anno di un brano
int leggi_anno_brano( brano brano_selezionato );

// funzione per leggere il numero di ascolti di un brano
int leggi_ascolti_brano( brano brano_selezionato );

// funzione per leggere il flag di eliminazione di un brano
int leggi_flag_eliminato_brano( brano brano_selezionato );

/* -------------------------
	Funzioni di scrittura
------------------------- */

// funzione per scrivere l'id di un brano
void scrivi_id_brano( brano *brano_selezionato, int id );

// funzione per scrivere il titolo di un brano
void scrivi_titolo_brano( brano *brano_selezionato, char *titolo );

// funzione per scrivere la durata di un brano
void scrivi_durata_brano( brano *brano_selezionato, int durata );

// funzione per scrivere l'anno di un brano
void scrivi_anno_brano( brano *brano_selezionato, int anno );

// funzione per scrivere gli ascolti di un brano
void scrivi_ascolti_brano( brano *brano_selezionato, int ascolti );

// funzione per scrivere il flag di eliminazione di un brano
void scrivi_flag_eliminato_brano(brano *brano_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un brano alla tabella dei brani
int aggiungi_brano(brano *brano_selezionato);

// funzione per stampare a video tutti i brani della tabella
void mostra_brani();

// funzione per stampare a video un determinato brano
void mostra_brano( brano brano_selezionato );

// funzione per cercare la posizione di un brano nella tabella con determinato id
long posizione_brano( int id_brano );

// funzione per eliminare un brano con determinato id
int elimina_brano( int id_brano );

// funzione per leggere un brano con determinato id
brano cerca_brano( int id_brano );

// funzione per modificare un brano nella tabella dei brani
int modifica_brano( brano brano_modificato);


#endif /* GESTIONE_BRANI_H_ */
