#ifndef GESTIONE_BRANI_H_
#define GESTIONE_BRANI_H_

// definisco dimensione massima del titolo di un brano
#define DIMTITOLO 60

// definisco tipo di dato brano
typedef struct{

	int id;
	char titolo[DIMTITOLO];
	int durata;
	int anno;
	int ascolti;
	int eliminato;

}brano;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere l'id di un brano
int leggi_id_brano(brano brano_selezionato);

// funzione per leggere il titolo di un brano 
void leggi_titolo_brano(brano brano_selezionato, char *titolo_letto);

// funzione per leggere la durata di un brano
int leggi_durata_brano(brano brano_selezionato);

// funzione per leggere l'anno di pubblicazione di un brano
int leggi_anno_brano(brano brano_selezionato);

// funzione per leggere il numero di ascolti di un brano 
int leggi_ascolti_brano(brano brano_selezionato);

// funzione per leggere il flag di eliminazione di un brano
int leggi_flag_eliminato_brano(brano brano_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */

// funzione per scrivere l'id di un brano
void scrivi_id_brano(brano *brano_selezionato, int id);

// funione per scrivere il titolo di un brano
void scrivi_titolo_brano(brano *brano_selezionato, char *titolo);

// funzione per scrivere la durata di un brano
void scrivi_durata_brano( brano *brano_selezionato, int durata );

// funzione per scrivere l'anno del brano
void scrivi_anno_brano( brano *brano_selezionato, int anno );

// funzione per scrivere il numero di ascolti del brano
void scrivi_ascolti_brano( brano *brano_selezionato, int ascolti );

// funzione per scrivere il flag di eliminazione del brano
void scrivi_flag_eliminato_brano( brano *brano_selezionato, int flag_eliminato );

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un brano alla tabella brani
int aggiungi_brano( brano *brano_selezionato );

// funzione per mostrare tutti i brani nella tabella brani
void mostra_brani();

// funzione per mostrare un brano
void mostra_brano( brano brano_selezionato );

// funzione per cercare la posizione di un brano nella tabella
long posizione_brano( int id_brano );

// funzione per eliminare un brano con determinato id 
int elimina_brano( int id_brano );

// funzione per leggere un brano con determinato id
brano cerca_brano( int id_brano );

// funzione per modificare un brano
int modifica_brano( brano brano_modificato );

#endif /* GESTIONE_BRANI_H_ */
