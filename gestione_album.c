#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_album.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_album(album album_selezionato){
	return album_selezionato.id;
}
void leggi_titolo_album(album album_selezionato, char *titolo_letto){
	strcpy(titolo_letto, album_selezionato.titolo);
}
int leggi_anno_album(album album_selezionato){
	return album_selezionato.anno;
}
int leggi_flag_eliminato_album(album album_selezionato){
	return album_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_album(album *album_selezionato, int id){
	album_selezionato->id = id;
}
void scrivi_titolo_album(album *album_selezionato, char *titolo){
    strcpy(album_selezionato->titolo, titolo);
}
void scrivi_anno_album(album *album_selezionato, int anno){
	album_selezionato->anno = anno;
}
void scrivi_flag_eliminato_album(album *album_selezionato, int flag_eliminato){
	album_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_album(album *album_selezionato){
	scrivi_id_album(album_selezionato, genera_id());
	scrivi_flag_eliminato_album(album_selezionato, 0);
	FILE *tabella_album;
	int aggiunto = 0;

	tabella_album = fopen("album.dat", "ab");
	if(tabella_album != NULL){
		fwrite(album_selezionato, sizeof(album), 1, tabella_album);
		aggiunto = 1;
	}

	fclose(tabella_album);

	return aggiunto;
}
void mostra_album(){
	album album_corrente;
	FILE *tabella_album;

	tabella_album = fopen("album.dat", "rb");
	if(tabella_album != NULL){
		while(fread(&album_corrente, sizeof(album), 1, tabella_album)){
			mostra_album_singolo(album_corrente);
		}
	}

	fclose(tabella_album);
}
void mostra_album_singolo(album album_selezionato){
	//if(album_selezionato.eliminato != 1){
		printf("ID: %d				\n", album_selezionato.id);
		printf("Titolo: %s			\n", album_selezionato.titolo);
		printf("Anno: %d			\n", album_selezionato.anno);
		printf("flag: %d\n", album_selezionato.eliminato);
	//}
	printf("\n");
}
long posizione_album(int id_album){
    long posizione;
    FILE *tabella_album;
    album album_corrente;
    int id_corrente;

    posizione = -1;
    tabella_album = fopen("album.dat", "rb");
    if (tabella_album != NULL){
        while(!feof(tabella_album) && posizione == -1){
            fread(&album_corrente, sizeof(album), 1, tabella_album);
            id_corrente = leggi_id_album(album_corrente);
            if(id_corrente == id_album){
                posizione = ftell(tabella_album) - sizeof(album); // perche' la ftell restituisce blocco successivo
            }
        }
    }

    fclose(tabella_album);

    return posizione;
}
int elimina_album(int id_album){
	long posizione;
	FILE *tabella_album;
	int eliminato;
	album album_trovato;

	eliminato = 0;
	posizione = posizione_album(id_album);
	album_trovato = cerca_album(id_album);
	scrivi_flag_eliminato_album(&album_trovato, 1);
	tabella_album = fopen("album.dat", "rb+");
	if(tabella_album != NULL){
		fseek(tabella_album, posizione, SEEK_SET);
		fwrite(&album_trovato, sizeof(album), 1, tabella_album);
		eliminato = 1;
	}
	fclose(tabella_album);

	return eliminato;
}
album cerca_album(int id_album){
	long posizione;
	FILE *tabella_album;
	album album_trovato;

	posizione = posizione_album(id_album);
	tabella_album = fopen("album.dat", "rb");
	if(tabella_album != NULL){
		if(posizione != -1){
			fseek(tabella_album, posizione, SEEK_SET);
			fread(&album_trovato, sizeof(album), 1, tabella_album);
		} else {
			printf("album non trovato \n");
		}
	}

	return album_trovato;
}
int modifica_album(album album_modificato)
{
	
	FILE *tabella_album;
	int modificato;
	

	modificato = 0;
	tabella_album = fopen("album.dat", "rb+");

	if(tabella_album != NULL)
	{
		long posizione;
		int id_album = leggi_id_album(album_modificato);
		posizione = posizione_album(id_album);

		fseek(tabella_album, posizione, SEEK_SET);
		fwrite(&album_modificato, sizeof(album), 1, tabella_album);
		modificato = 1;
	}
	fclose(tabella_album);


	return modificato;
}
