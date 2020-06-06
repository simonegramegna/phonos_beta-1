#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_playlist.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_playlist(playlist playlist_selezionata)
{
	return playlist_selezionata.id;
}
int leggi_utente_playlist(playlist playlist_selezionata)
{
	return playlist_selezionata.utente;
}
void leggi_nome_playlist(playlist playlist_selezionata, char *nome_letto)
{
	strcpy(nome_letto, playlist_selezionata.nome);
}
void leggi_descrizione_playlist(playlist playlist_selezionata, char *descrizione_letta)
{
	strcpy(descrizione_letta, playlist_selezionata.descrizione);
}
int leggi_flag_pubblica_playlist(playlist playlist_selezionata)
{
	return playlist_selezionata.pubblica;
}
int leggi_flag_eliminato_playlist(playlist playlist_selezionata)
{
	return playlist_selezionata.eliminata;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */

void scrivi_id_playlist( playlist *playlist_selezionata, int id )
{
	playlist_selezionata->id = id;
}

void scrivi_utente_playlist( playlist *playlist_selezionata, int utente )
{
	playlist_selezionata->utente= utente;
}

void scrivi_flag_pubblica_playlist( playlist *playlist_selezionata, int flag_pubblica )
{
	playlist_selezionata->pubblica = flag_pubblica;
}

void scrivi_nome_playlist( playlist *playlist_selezionata, char *nome )
{
    strcpy(playlist_selezionata->nome, nome);
}

void scrivi_descrizione_playlist( playlist *playlist_selezionata, char *descrizione )
{
    strcpy(playlist_selezionata->descrizione, descrizione);
}

void scrivi_flag_eliminato_playlist(playlist *playlist_selezionata, int flag_eliminato)
{
	playlist_selezionata->eliminata = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */

int aggiungi_playlist( playlist *playlist_selezionata )
{
	FILE *tabella_playlist;
	int aggiunto;
	
	aggiunto = 0;
	tabella_playlist = fopen("playlists.dat", "ab");

	if(tabella_playlist != NULL)
	{
		scrivi_id_playlist(playlist_selezionata, genera_id());
		scrivi_flag_eliminato_playlist(playlist_selezionata, 0);

		fwrite(playlist_selezionata, sizeof(playlist), 1, tabella_playlist);
		aggiunto = 1;
	}
	fclose(tabella_playlist);

	return aggiunto;
}

void mostra_playlists()
{
	FILE *tabella_playlist;
	tabella_playlist = fopen("playlists.dat", "rb");

	if(tabella_playlist != NULL)
	{
		playlist playlist_corrente;

		while( fread(&playlist_corrente, sizeof(playlist), 1, tabella_playlist) )
		{
			mostra_playlist(playlist_corrente);
		}
	}
	fclose(tabella_playlist);
}

void mostra_playlist(playlist playlist_selezionata)
{
	int flag_eliminazione_playlist;
	flag_eliminazione_playlist = leggi_flag_eliminato_playlist(playlist_selezionata);

	if( flag_eliminazione_playlist != 1 )
	{
		int id_playlist_letta;
		char nome_playlist_letta[DIMNOME_PLAYLIST];
		char descrizione_playlist_letta[DIMDESC];
		int utente_playlist_letta;
		int flag_pubblica_playlist_letta;


		// leggo i dati dai campi della playlist
		id_playlist_letta = leggi_id_playlist(playlist_selezionata);
		leggi_nome_playlist(playlist_selezionata, nome_playlist_letta);
		leggi_descrizione_playlist(playlist_selezionata, descrizione_playlist_letta);
		utente_playlist_letta = leggi_utente_playlist(playlist_selezionata);
		flag_pubblica_playlist_letta = leggi_flag_pubblica_playlist(playlist_selezionata);

		// stampo i dati della playlist
		printf("ID: %d				\n", id_playlist_letta);
		printf("Nome: %s			\n", nome_playlist_letta);
		printf("Descrizione: %s		\n", descrizione_playlist_letta);
		printf("Utente: %d 			\n", utente_playlist_letta);
		printf("Pubblica: %d		\n", flag_pubblica_playlist_letta);
	}
	printf("\n");
}

long posizione_playlist(int id_playlist)
{
    long posizione;
    FILE *tabella_playlist;
    
    posizione = -1;
    tabella_playlist = fopen("playlists.dat", "rb");

    if (tabella_playlist != NULL)
	{
        while( !feof(tabella_playlist) && posizione == -1 )
		{
			playlist playlist_corrente;
    		int id_corrente;
			
			fread(&playlist_corrente, sizeof(playlist), 1, tabella_playlist);
            id_corrente = leggi_id_playlist(playlist_corrente);

            if(id_corrente == id_playlist)
			{
                posizione = ftell(tabella_playlist) - sizeof(playlist); // perche' la ftell restituisce blocco successivo
            }
        }
    }
	fclose(tabella_playlist);

    return posizione;
}

int elimina_playlist(int id_playlist)
{
	FILE *tabella_playlist;
	int eliminato;

	eliminato = 0;
	tabella_playlist = fopen("playlists.dat", "rb+");

	if(tabella_playlist != NULL)
	{
		long posizione;
		posizione = posizione_playlist(id_playlist);
		
		if(posizione != -1)
		{
			playlist playlist_trovata;

			playlist_trovata = cerca_playlist(id_playlist);
			scrivi_flag_eliminato_playlist(&playlist_trovata, 1);

			// mi porto nella poszione della playlist da eliminare
			fseek(tabella_playlist, posizione, SEEK_SET);
			
			fwrite(&playlist_trovata, sizeof(playlist), 1, tabella_playlist);
		} 
		else 
		{
			printf("playlist non trovata \n");
		}
		eliminato = 1;
	}
	fclose(tabella_playlist);

	return eliminato;
}

playlist cerca_playlist(int id_playlist)
{
	FILE *tabella_playlist;
	playlist playlist_trovata;

	tabella_playlist = fopen("playlists.dat", "rb");

	if(tabella_playlist != NULL)
	{
		long posizione;
		posizione = posizione_playlist(id_playlist);

		// mi porto nella posizione della playlist da leggere
		fseek(tabella_playlist, posizione, SEEK_SET);

		fread(&playlist_trovata, sizeof(playlist), 1, tabella_playlist);
	}
	fclose(tabella_playlist);

	return playlist_trovata;
}

int modifica_playlist(playlist playlist_modificata)
{
	FILE *tabella_playlist;
	int modificato;
	
	tabella_playlist = fopen("playlists.dat", "rb+");
	modificato = 0;
	
	if(tabella_playlist != NULL)
	{
		long posizione;
		int id_playlist;

		// cerco la poszione della playlist
		id_playlist = leggi_id_playlist(playlist_modificata);
		posizione = posizione_playlist(id_playlist);

		fseek(tabella_playlist, posizione, SEEK_SET);

		fwrite(&playlist_modificata, sizeof(playlist), 1, tabella_playlist);
		modificato = 1;
	}
	fclose(tabella_playlist);

	return modificato;
}

