#ifndef GESTIONE_GENERI_H_
#define GESTIONE_GENERI_H_

#define DIMSTRING 30

typedef struct {
	int id;
	char nome[DIMSTRING];
	int eliminato;
} genere;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_genere(genere genere_selezionato);
void leggi_nome_genere(genere genere_selezionato, char *nome_letto);
int leggi_flag_eliminato_genere(genere genere_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_genere(genere *genere_selezionato, int id);
void scrivi_nome_genere(genere *genere_selezionato, char *nome);
void scrivi_flag_eliminato_genere(genere *genere_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_genere(genere *genere_selezionato);
void mostra_generi();
void mostra_genere(genere genere_selezionato);
long posizione_genere(int id_genere);
int elimina_genere(int id_genere);
genere cerca_genere(int id_genere);
int modifica_genere(genere genere_modificato);


#endif /* GESTIONE_GENERI_H_ */
