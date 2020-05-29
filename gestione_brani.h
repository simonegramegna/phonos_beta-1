#ifndef GESTIONE_BRANI_H_
#define GESTIONE_BRANI_H_

#define DIMTITOLO 60

typedef struct {
	int id;
	char titolo[DIMTITOLO];
	int durata;
	int anno;
	int ascolti;
	int eliminato;
} brano;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_brano(brano brano_selezionato);
void leggi_titolo_brano(brano brano_selezionato, char *titolo_letto);
int leggi_durata_brano(brano brano_selezionato);
int leggi_anno_brano(brano brano_selezionato);
int leggi_ascolti_brano(brano brano_selezionato);
int leggi_flag_eliminato_brano(brano brano_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_brano(brano *brano_selezionato, int id);
void scrivi_titolo_brano(brano *brano_selezionato, char *titolo);
void scrivi_durata_brano(brano *brano_selezionato, int durata);
void scrivi_anno_brano(brano *brano_selezionato, int anno);
void scrivi_ascolti_brano(brano *brano_selezionato, int ascolti);
void scrivi_flag_eliminato_brano(brano *brano_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_brano(brano *brano_selezionato);
void mostra_brani();
void mostra_brano(brano brano_selezionato);
long posizione_brano(int id_brano);
int elimina_brano(int id_brano);
brano cerca_brano(int id_brano);
int modifica_brano( brano brano_modificato);

#endif /* GESTIONE_BRANI_H_ */
