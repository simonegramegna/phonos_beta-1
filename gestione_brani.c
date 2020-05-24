#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_brani.h"
#include "genera_id.h"

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
	scrivi_id_brano(brano_selezionato, genera_id());
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
void mostra_brani(){
	brano brano_corrente;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");
	if(tabella_brani != NULL){
		while(fread(&brano_corrente, sizeof(brano), 1, tabella_brani)){
			mostra_brano(brano_corrente);
		}
	}

	fclose(tabella_brani);
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
long posizione_brano(int id_brano){
    long posizione;
    FILE *tabella_brani;
    brano brano_corrente;
    int id_corrente;

    posizione = -1;
    tabella_brani = fopen("brani.dat", "rb");
    if (tabella_brani != NULL){
        while(!feof(tabella_brani) && posizione == -1){
            fread(&brano_corrente, sizeof(brano), 1, tabella_brani);
            id_corrente = leggi_id_brano(brano_corrente);
            if(id_corrente == id_brano){
                posizione = ftell(tabella_brani) - sizeof(brano); // perche' la ftell restituisce blocco successivo
            }
        }
    }

    fclose(tabella_brani);

    return posizione;
}
int elimina_brano(int id_brano){
	long posizione;
	FILE *tabella_brani;
	int eliminato;
	brano brano_trovato;

	eliminato = 0;
	posizione = posizione_brano(id_brano);
	brano_trovato = cerca_brano(id_brano);
	scrivi_flag_eliminato_brano(&brano_trovato, 1);
	tabella_brani = fopen("brani.dat", "rb+");
	if(tabella_brani != NULL){
		if(posizione != -1){
			fseek(tabella_brani, posizione, SEEK_SET);
			fwrite(&brano_trovato, sizeof(brano), 1, tabella_brani);
		} else {
			printf("Brano non trovato \n");
		}
		eliminato = 1;
	}

	return eliminato;
}
brano cerca_brano(int id_brano){
	long posizione;
	FILE *tabella_brani;
	brano brano_trovato;

	posizione = posizione_brano(id_brano);
	tabella_brani = fopen("brani.dat", "rb");
	if(tabella_brani != NULL){
		fseek(tabella_brani, posizione, SEEK_SET);
		fread(&brano_trovato, sizeof(brano), 1, tabella_brani);
	}

	return brano_trovato;
}
int modifica_brano(int id_brano, brano brano_modificato){
	long posizione;
	FILE *tabella_brani;
	int modificato;
	brano brano_trovato;

	modificato = 0;
	posizione = posizione_brano(id_brano);
	brano_trovato = cerca_brano(id_brano);

	scrivi_titolo_brano(&brano_trovato, brano_modificato.titolo);
	scrivi_durata_brano(&brano_trovato, brano_modificato.durata);
	scrivi_anno_brano(&brano_trovato, brano_modificato.anno);
	scrivi_ascolti_brano(&brano_trovato, brano_modificato.ascolti);
	scrivi_flag_eliminato_brano(&brano_trovato, brano_modificato.eliminato);


	tabella_brani = fopen("brani.dat", "rb+");
	if(tabella_brani != NULL){
		fseek(tabella_brani, posizione, SEEK_SET);
		fwrite(&brano_trovato, sizeof(brano), 1, tabella_brani);
		modificato = 1;
	}

	return modificato;
}


