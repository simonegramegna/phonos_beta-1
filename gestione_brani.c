#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_brani.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_brano(brano brano_selezionato){
	return brano_selezionato.id;
}

void leggi_titolo_brano(brano brano_selezionato, char *titolo_letto){
	strcpy(titolo_letto, brano_selezionato.titolo);
}

int leggi_durata_brano(brano brano_selezionato){
	return brano_selezionato.durata;
}

int leggi_anno_brano(brano brano_selezionato){
	return brano_selezionato.anno;
}

int leggi_ascolti_brano(brano brano_selezionato){
	return brano_selezionato.ascolti;
}

int leggi_flag_eliminato_brano(brano brano_selezionato){
	return brano_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_brano(brano *brano_selezionato, int id){
	brano_selezionato->id = id;
}
void scrivi_titolo_brano(brano *brano_selezionato, char *titolo){
    strcpy(brano_selezionato->titolo, titolo);
}
void scrivi_durata_brano(brano *brano_selezionato, int durata){
	brano_selezionato->durata = durata;
}
void scrivi_anno_brano(brano *brano_selezionato, int anno){
	brano_selezionato->anno = anno;
}
void scrivi_ascolti_brano(brano *brano_selezionato, int ascolti){
	brano_selezionato->ascolti = ascolti;
}
void scrivi_flag_eliminato_brano(brano *brano_selezionato, int flag_eliminato){
	brano_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */

int aggiungi_brano(brano *brano_selezionato){
	// TODO: genera id
	scrivi_flag_eliminato_brano(brano_selezionato, 0);
	FILE *tabella_brani;
	int aggiunto = 0;

	tabella_brani = fopen("brani.dat", "ab");
	if(tabella_brani != NULL){
		fwrite(brano_selezionato, sizeof(brano), 1, tabella_brani);
		aggiunto = 1;
	}

	fclose(tabella_brani);

	return aggiunto;
}

int rimuovi_brano(int id_brano){
	FILE *tabella_brani;
	brano brano_corrente;
	int rimosso = 0;

	tabella_brani = fopen("brani.dat", "rb+");
	if(tabella_brani != NULL){
		while(!feof(tabella_brani) && rimosso == 0){
			fread(&brano_corrente, sizeof(brano), 1, tabella_brani);
			if(leggi_id_brano(brano_corrente) == id_brano){
				scrivi_flag_eliminato_brano(&brano_corrente, 1);
				fwrite(&brano_corrente, sizeof(brano), 1, tabella_brani);
				rimosso = 1;
			}
		}
	}

	fclose(tabella_brani);

	return rimosso;
}

void mostra_brani(){
	brano brano_corrente;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");
	if(tabella_brani != NULL){
		while(fread(&brano_corrente, sizeof(brano), 1, tabella_brani)){
			mostra_brano(brano_corrente);
		}
	}
}

void mostra_brano(brano brano_selezionato){
	if(brano_selezionato.eliminato != 1){
		printf("ID: %d				\n", brano_selezionato.id);
		printf("Titolo: %s			\n", brano_selezionato.titolo);
		printf("Anno: %d 			\n", brano_selezionato.anno);
		printf("Durata: %d secondi	\n", brano_selezionato.durata);
		printf("Ascoltato %d volte	\n", brano_selezionato.ascolti);
		printf("Eliminato: %d		\n", brano_selezionato.eliminato);
	}
	printf("\n");
}
