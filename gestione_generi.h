#ifndef GESTIONE_GENERI_H_
#define GESTIONE_GENERI_H_

// dimensione massima del nome di un genere 
#define DIMSTRING 30

// definisco tipo di dato genere
typedef struct{

	int id;
	char nome[DIMSTRING];
	int eliminato;

}genere;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere l'id di un genere
int leggi_id_genere( genere genere_selezionato );

// funzione per leggere il nome di un genere
void leggi_nome_genere( genere genere_selezionato, char *nome_letto );

// funzione per leggere il flag di eliminazione di un genere
int leggi_flag_eliminato_genere( genere genere_selezionato );

/* -------------------------
	Funzioni di scrittura
------------------------- */

// funzione per scrivere l'id di un genere
void scrivi_id_genere( genere *genere_selezionato, int id );

// funzione per scrivere il nome di un genere
void scrivi_nome_genere(genere *genere_selezionato, char *nome);

// funzione per scrivere il flag di eliminazione di genere
void scrivi_flag_eliminato_genere(genere *genere_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un genere alla tabella
int aggiungi_genere( genere *genere_selezionato );

// funzione per mostrare tutti i generi nella tabella
void mostra_generi();

// funzione per mostrare un determinato genere
void mostra_genere( genere genere_selezionato );

// funzione per cercare la poszione di un genere nella tabella
long posizione_genere( int id_genere );

// funzione per eliminare un genere
int elimina_genere( int id_genere );

// funzione per leggere un genere con determinato id 
genere cerca_genere( int id_genere );

// funzione per modificare un genere
int modifica_genere( genere genere_modificato );


#endif /* GESTIONE_GENERI_H_ */
