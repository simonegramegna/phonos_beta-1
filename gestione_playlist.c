#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_playlist.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_playlist(playlist playlist_selezionata){
	return playlist_selezionata.id;
}
int leggi_utente_playlist(playlist playlist_selezionata){
	return playlist_selezionata.utente;
}
void leggi_nome_playlist(playlist playlist_selezionata, char *nome_letto){
	strcpy(nome_letto, playlist_selezionata.nome);
}
void leggi_descrizione_playlist(playlist playlist_selezionata, char *descrizione_letta){
	strcpy(descrizione_letta, playlist_selezionata.descrizione);
}
int leggi_flag_pubblica_playlist(playlist playlist_selezionata){
	return playlist_selezionata.pubblica;
}
int leggi_flag_eliminato_playlist(playlist playlist_selezionata){
	return playlist_selezionata.eliminata;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_playlist(playlist *playlist_selezionata, int id){
	playlist_selezionata->id = id;
}
void scrivi_utente_playlist(playlist *playlist_selezionata, int utente){
	playlist_selezionata->utente= utente;
}
void scrivi_flag_pubblica_playlist(playlist *playlist_selezionata, int flag_pubblica){
	playlist_selezionata->pubblica= flag_pubblica;
}
void scrivi_nome_playlist(playlist *playlist_selezionata, char *nome){
    strcpy(playlist_selezionata->nome, nome);
}
void scrivi_descrizione_playlist(playlist *playlist_selezionata, char *descrizione){
    strcpy(playlist_selezionata->descrizione, descrizione);
}
void scrivi_flag_eliminato_playlist(playlist *playlist_selezionata, int flag_eliminato){
	playlist_selezionata->eliminata = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_playlist(playlist *playlist_selezionata){
	scrivi_id_playlist(playlist_selezionata, genera_id());
	scrivi_flag_eliminato_playlist(playlist_selezionata, 0);
	FILE *tabella_playlists;
	int aggiunto = 0;

	tabella_playlists = fopen("playlists.dat", "ab");
	if(tabella_playlists != NULL){
		fwrite(playlist_selezionata, sizeof(playlist), 1, tabella_playlists);
		aggiunto = 1;
	}

	fclose(tabella_playlists);

	return aggiunto;
}
void mostra_playlists(){
	playlist playlist_corrente;
	FILE *tabella_playlists;

	tabella_playlists = fopen("playlists.dat", "rb");
	if(tabella_playlists != NULL){
		while(fread(&playlist_corrente, sizeof(playlist), 1, tabella_playlists)){
			mostra_playlist(playlist_corrente);
		}
	}

	fclose(tabella_playlists);
}
void mostra_playlist(playlist playlist_selezionata){
	if(playlist_selezionata.eliminata != 1){
		printf("ID: %d				\n", playlist_selezionata.id);
		printf("Nome: %s			\n", playlist_selezionata.nome);
		printf("Descrizione: %s		\n", playlist_selezionata.descrizione);
		printf("Utente: %d 			\n", playlist_selezionata.utente);
		printf("Pubblica: %d		\n", playlist_selezionata.pubblica);
		printf("Eliminata: %d		\n", playlist_selezionata.eliminata);
	}
	printf("\n");
}
long posizione_playlist(int id_playlist){
    long posizione;
    FILE *tabella_playlists;
    playlist playlist_corrente;
    int id_corrente;

    posizione = -1;
    tabella_playlists = fopen("playlists.dat", "rb");
    if (tabella_playlists != NULL){
        while(!feof(tabella_playlists) && posizione == -1){
            fread(&playlist_corrente, sizeof(playlist), 1, tabella_playlists);
            id_corrente = leggi_id_playlist(playlist_corrente);
            if(id_corrente == id_playlist){
                posizione = ftell(tabella_playlists) - sizeof(playlist); // perche' la ftell restituisce blocco successivo
            }
        }
    }

    fclose(tabella_playlists);

    return posizione;
}
int elimina_playlist(int id_playlist){
	long posizione;
	FILE *tabella_playlists;
	int eliminato;
	playlist playlist_trovata;

	eliminato = 0;
	posizione = posizione_playlist(id_playlist);
	playlist_trovata = cerca_playlist(id_playlist);
	scrivi_flag_eliminato_playlist(&playlist_trovata, 1);
	tabella_playlists = fopen("playlists.dat", "rb+");
	if(tabella_playlists != NULL){
		if(posizione != -1){
			fseek(tabella_playlists, posizione, SEEK_SET);
			fwrite(&playlist_trovata, sizeof(playlist), 1, tabella_playlists);
		} else {
			printf("playlist non trovata \n");
		}
		eliminato = 1;
	}

	return eliminato;
}
playlist cerca_playlist(int id_playlist){
	long posizione;
	FILE *tabella_playlists;
	playlist playlist_trovata;

	posizione = posizione_playlist(id_playlist);
	tabella_playlists = fopen("playlists.dat", "rb");
	if(tabella_playlists != NULL){
		fseek(tabella_playlists, posizione, SEEK_SET);
		fread(&playlist_trovata, sizeof(playlist), 1, tabella_playlists);
	}

	return playlist_trovata;
}
int modifica_playlist(int id_playlist, playlist playlist_modificato){
	long posizione;
	FILE *tabella_playlists;
	int modificato;
	playlist playlist_trovata;

	modificato = 0;
	posizione = posizione_playlist(id_playlist);
	playlist_trovata = cerca_playlist(id_playlist);

	scrivi_nome_playlist(&playlist_trovata, playlist_modificato.nome);
	scrivi_descrizione_playlist(&playlist_trovata, playlist_modificato.descrizione);
	scrivi_flag_eliminato_playlist(&playlist_trovata, playlist_modificato.eliminata);


	tabella_playlists = fopen("playlists.dat", "rb+");
	if(tabella_playlists != NULL){
		fseek(tabella_playlists, posizione, SEEK_SET);
		fwrite(&playlist_trovata, sizeof(playlist), 1, tabella_playlists);
		modificato = 1;
	}

	return modificato;
}

