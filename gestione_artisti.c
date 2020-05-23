#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_artisti.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_artista(artista artista_selezionato){
	return artista_selezionato.id;
}
void leggi_nome_artista(artista artista_selezionato, char *nome_letto){
	strcpy(nome_letto, artista_selezionato.nome);
}
void leggi_cognome_artista(artista artista_selezionato, char *cognome_letto){
	strcpy(cognome_letto, artista_selezionato.cognome);
}
void leggi_nome_arte_artista(artista artista_selezionato, char *nome_arte_letto){
	strcpy(nome_arte_letto, artista_selezionato.nome_arte);
}
int leggi_flag_eliminato_artista(artista artista_selezionato){
	return artista_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_artista(artista *artista_selezionato, int id){
	artista_selezionato->id = id;
}
void scrivi_nome_artista(artista *artista_selezionato, char *nome){
    strcpy(artista_selezionato->nome, nome);
}
void scrivi_cognome_artista(artista *artista_selezionato, char *cognome){
    strcpy(artista_selezionato->cognome, cognome);
}
void scrivi_nome_arte_artista(artista *artista_selezionato, char *nome_arte){
    strcpy(artista_selezionato->nome_arte, nome_arte);
}
void scrivi_flag_eliminato_artista(artista *artista_selezionato, int flag_eliminato){
	artista_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_artista(artista *artista_selezionato){
	// TODO: genera id
	scrivi_flag_eliminato_artista(artista_selezionato, 0);
	FILE *tabella_artisti;
	int aggiunto = 0;

	tabella_artisti = fopen("artisti.dat", "ab");
	if(tabella_artisti != NULL){
		fwrite(artista_selezionato, sizeof(artista), 1, tabella_artisti);
		aggiunto = 1;
	}

	fclose(tabella_artisti);

	return aggiunto;
}
void mostra_artisti(){
	artista artista_corrente;
	FILE *tabella_artisti;

	tabella_artisti = fopen("artisti.dat", "rb");
	if(tabella_artisti != NULL){
		while(fread(&artista_corrente, sizeof(artista), 1, tabella_artisti)){
			mostra_artista(artista_corrente);
		}
	}

	fclose(tabella_artisti);
}
void mostra_artista(artista artista_selezionato){
	if(artista_selezionato.eliminato != 1){
		printf("ID: %d				\n", artista_selezionato.id);
		printf("Nome: %s			\n", artista_selezionato.nome);
		printf("Cognome: %s			\n", artista_selezionato.cognome);
		printf("Nome d'arte: %s		\n", artista_selezionato.nome_arte);
	}
	printf("\n");
}
long posizione_artista(int id_artista){
    long posizione;
    FILE *tabella_artisti;
    artista artista_corrente;
    int id_corrente;

    posizione = -1;
    tabella_artisti = fopen("artisti.dat", "rb");
    if (tabella_artisti != NULL){
        while(!feof(tabella_artisti) && posizione == -1){
            fread(&artista_corrente, sizeof(artista), 1, tabella_artisti);
            id_corrente = leggi_id_artista(artista_corrente);
            if(id_corrente == id_artista){
                posizione = ftell(tabella_artisti) - sizeof(artista); // perche' la ftell restituisce blocco successivo
            }
        }
    }

    fclose(tabella_artisti);

    return posizione;
}
int elimina_artista(int id_artista){
	long posizione;
	FILE *tabella_artisti;
	int eliminato;
	artista artista_trovato;

	eliminato = 0;
	posizione = posizione_artista(id_artista);
	artista_trovato = cerca_artista(id_artista);
	scrivi_flag_eliminato_artista(&artista_trovato, 1);
	tabella_artisti = fopen("artisti.dat", "rb+");
	if(tabella_artisti != NULL){
		fseek(tabella_artisti, posizione, SEEK_SET);
		fwrite(&artista_trovato, sizeof(artista), 1, tabella_artisti);
		eliminato = 1;
	}

	return eliminato;
}
artista cerca_artista(int id_artista){
	long posizione;
	FILE *tabella_artisti;
	artista artista_trovato;

	posizione = posizione_artista(id_artista);
	tabella_artisti = fopen("artisti.dat", "rb");
	if(tabella_artisti != NULL){
		if(posizione != -1){
			fseek(tabella_artisti, posizione, SEEK_SET);
			fread(&artista_trovato, sizeof(artista), 1, tabella_artisti);
		} else {
			printf("Artista non trovato \n");
		}
	}

	return artista_trovato;
}
int modifica_artista(int id_artista, artista artista_modificato){
	long posizione;
	FILE *tabella_artisti;
	int modificato;
	artista artista_trovato;

	modificato = 0;
	posizione = posizione_artista(id_artista);
	artista_trovato = cerca_artista(id_artista);

	scrivi_nome_artista(&artista_trovato, artista_modificato.nome);
	scrivi_cognome_artista(&artista_trovato, artista_modificato.cognome);
	scrivi_nome_arte_artista(&artista_trovato, artista_modificato.nome_arte);
	scrivi_flag_eliminato_artista(&artista_trovato, artista_modificato.eliminato);


	tabella_artisti = fopen("artisti.dat", "rb+");
	if(tabella_artisti != NULL){
		fseek(tabella_artisti, posizione, SEEK_SET);
		fwrite(&artista_trovato, sizeof(artista), 1, tabella_artisti);
		modificato = 1;
	}

	return modificato;
}
