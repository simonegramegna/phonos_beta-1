#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_generi.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_genere(genere genere_selezionato){
	return genere_selezionato.id;
}
void leggi_nome_genere(genere genere_selezionato, char *nome_letto){
	strcpy(nome_letto, genere_selezionato.nome);
}
int leggi_flag_eliminato_genere(genere genere_selezionato){
	return genere_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_genere(genere *genere_selezionato, int id){
	genere_selezionato->id = id;
}
void scrivi_nome_genere(genere *genere_selezionato, char *nome){
    strcpy(genere_selezionato->nome, nome);
}
void scrivi_flag_eliminato_genere(genere *genere_selezionato, int flag_eliminato){
	genere_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_genere(genere *genere_selezionato){
	scrivi_id_genere(genere_selezionato, genera_id());
	scrivi_flag_eliminato_genere(genere_selezionato, 0);
	FILE *tabella_generi;
	int aggiunto = 0;

	tabella_generi = fopen("generi.dat", "ab");
	if(tabella_generi != NULL){
		fwrite(genere_selezionato, sizeof(genere), 1, tabella_generi);
		aggiunto = 1;
	}

	fclose(tabella_generi);

	return aggiunto;
}
void mostra_generi(){
	genere genere_corrente;
	FILE *tabella_generi;

	tabella_generi = fopen("generi.dat", "rb");
	if(tabella_generi != NULL){
		while(fread(&genere_corrente, sizeof(genere), 1, tabella_generi)){
			mostra_genere(genere_corrente);
		}
	}

	fclose(tabella_generi);
}
void mostra_genere(genere genere_selezionato){
	if(genere_selezionato.eliminato != 1){
		printf("ID: %d				\n", genere_selezionato.id);
		printf("Nome: %s			\n", genere_selezionato.nome);
		printf("Eliminato: %d		\n", genere_selezionato.eliminato);
	}
	printf("\n");
}
long posizione_genere(int id_genere){
    long posizione;
    FILE *tabella_generi;
    genere genere_corrente;
    int id_corrente;

    posizione = -1;
    tabella_generi = fopen("generi.dat", "rb");
    if (tabella_generi != NULL){
        while(!feof(tabella_generi) && posizione == -1){
            fread(&genere_corrente, sizeof(genere), 1, tabella_generi);
            id_corrente = leggi_id_genere(genere_corrente);
            if(id_corrente == id_genere){
                posizione = ftell(tabella_generi) - sizeof(genere); // perche' la ftell restituisce blocco successivo
            }
        }
    }

    fclose(tabella_generi);

    return posizione;
}
int elimina_genere(int id_genere){
	long posizione;
	FILE *tabella_generi;
	int eliminato;
	genere genere_trovato;

	eliminato = 0;
	posizione = posizione_genere(id_genere);
	genere_trovato = cerca_genere(id_genere);
	scrivi_flag_eliminato_genere(&genere_trovato, 1);
	tabella_generi = fopen("generi.dat", "rb+");
	if(tabella_generi != NULL){
		if(posizione != -1){
			fseek(tabella_generi, posizione, SEEK_SET);
			fwrite(&genere_trovato, sizeof(genere), 1, tabella_generi);
		} else {
			printf("genere non trovato \n");
		}
		eliminato = 1;
	}

	return eliminato;
}
genere cerca_genere(int id_genere){
	long posizione;
	FILE *tabella_generi;
	genere genere_trovato;

	posizione = posizione_genere(id_genere);
	tabella_generi = fopen("generi.dat", "rb");
	if(tabella_generi != NULL){
		fseek(tabella_generi, posizione, SEEK_SET);
		fread(&genere_trovato, sizeof(genere), 1, tabella_generi);
	}

	return genere_trovato;
}
int modifica_genere(genere genere_modificato){
	long posizione;
	FILE *tabella_generi;
	int modificato;
	

	modificato = 0;
	int id_genere= leggi_id_genere(genere_modificato);
	posizione = posizione_genere(id_genere);
	

	tabella_generi = fopen("generi.dat", "rb+");
	if(tabella_generi != NULL){
		fseek(tabella_generi, posizione, SEEK_SET);
		fwrite(&genere_modificato, sizeof(genere), 1, tabella_generi);
		modificato = 1;
	}

	return modificato;
}
