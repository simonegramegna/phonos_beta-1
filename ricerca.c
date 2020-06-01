#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ricerca.h"
#include "gestione_brani.h"
#include "gestione_artisti.h"

/*--------------------
	Ricerca brani
--------------------*/
void ricerca_brani_per_titolo(char *titolo){
	brano brano_corrente;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");
	if(tabella_brani != NULL){
		while(fread(&brano_corrente, sizeof(brano), 1, tabella_brani)){
			if(strcmp(brano_corrente.titolo, titolo) == 0){
				mostra_brano(brano_corrente);
			}
		}
	}

	fclose(tabella_brani);
}

void ricerca_brani_per_durata(int durata){
	brano brano_corrente;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");
	if(tabella_brani != NULL){
		while(fread(&brano_corrente, sizeof(brano), 1, tabella_brani)){
			if(classe_durata_brano(brano_corrente.durata, durata)){
				mostra_brano(brano_corrente);
			}
		}
	}

	fclose(tabella_brani);
}

int classe_durata_brano(int durata, int classe_durata){
	int risultato;

	risultato = 0;
	if(durata/60-classe_durata >= 0 && durata/60-classe_durata < 1){
		risultato = 1;
	}

	return risultato;
}

/*--------------------
	Ricerca artisti
--------------------*/
void ricerca_artisti_per_nome(char *nome){
	artista artista_corrente;
	FILE *tabella_artisti;

	tabella_artisti = fopen("artisti.dat", "rb");
	if(tabella_artisti != NULL){
		while(fread(&artista_corrente, sizeof(artista), 1, tabella_artisti)){
			if(strcmp(artista_corrente.nome, nome) == 0){
				mostra_artista(artista_corrente);
			}
		}
	}

	fclose(tabella_artisti);
}
