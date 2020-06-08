#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// numero di secondi in un minuto
#define MINUTO 60

// valore minimo dell'anno
#define MIN_ANNO 1900

#include "ricerca.h"
#include "gestione_album.h"
#include "gestione_brani.h"
#include "gestione_generi.h"
#include "gestione_artisti.h"
#include "gestione_playlist.h"
#include "gestione_relazioni.h"


/********************************************************
 * 
 *  Funzioni di controllo per le ricerche
 * 
 ********************************************************/

int controllo_anno( int anno_inserito )
{
	int controllo;
	int anno_attuale;

	controllo = 0;

	// funzioni e variabili per ottenere l'anno corrente
	time_t tempo_iniziale;
	struct tm tempo_ottenuto;

	tempo_iniziale = time(NULL);
	tempo_ottenuto = *localtime(&tempo_iniziale);
	anno_attuale = tempo_ottenuto.tm_year + 1900; // anni rispetto al 1900

	if( anno_inserito > MIN_ANNO && anno_inserito <= anno_attuale )
	{
		controllo = 1;
	}

	return controllo;
}

int classe_durata_brano( int durata, int classe_durata)
{
	int risultato;

	risultato = 0;
	if( durata/MINUTO - classe_durata >= 0 && durata/MINUTO - classe_durata < 1 )
	{
		risultato = 1;
	}
	
	return risultato;
}


/********************************************************
 * 
 *  Funzioni di ricerca per brani
 * 
 ********************************************************/

void ricerca_brani_titolo( char *titolo_cercato )
{
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");

	if( tabella_brani != NULL )
	{
		brano brano_corrente;
		int contatore_brani;

		contatore_brani = 0;

		while( fread(&brano_corrente, sizeof(brano), 1, tabella_brani) )
		{
			// leggo il nome del brano appena letto
			char nome_titolo_confronto[DIMTITOLO_BRANO];
			leggi_titolo_brano(brano_corrente, nome_titolo_confronto);

			// verifico che i titoli coincidano
			if( strstr(nome_titolo_confronto, titolo_cercato) != NULL )
			{
				mostra_brano(brano_corrente);
				contatore_brani = contatore_brani + 1;
			}
		}

		if( contatore_brani == 0 )
		{
			printf("Nessun brano corrisponde al titolo cercato..\n");
		}
	}

	fclose(tabella_brani);
}

void ricerca_brani_anno( int anno_cercato )
{
	if( controllo_anno(anno_cercato) == 1 )
	{
		FILE* tabella_brani = fopen("brani.dat","rb");

		if( tabella_brani != NULL )
		{
			brano brano_corrente;
			int contatore_brani;

			contatore_brani = 0;

			while( fread(&brano_corrente, sizeof(brano), 1, tabella_brani) )
			{
				int anno_confronto;
				anno_confronto = leggi_anno_brano(brano_corrente);

				if( anno_cercato == anno_confronto )
				{
					mostra_brano(brano_corrente);

					contatore_brani = contatore_brani + 1;
				}
			}

			if( contatore_brani == 0 )
			{
				printf("Nessun brano corrisponde all'anno cercato..\n");
			}
		}

		fclose(tabella_brani);
	}
	else
	{
		printf("Anno cercato non valido!\n");
	}
}

void ricerca_brani_durata( int durata_cercata )
{
	if( durata_cercata > 0 )
	{
		FILE *tabella_brani;
		tabella_brani = fopen("brani.dat", "rb");

		if(tabella_brani != NULL)
		{
			brano brano_corrente;
			int contatore_brani;

			contatore_brani = 0;

			while( fread(&brano_corrente, sizeof(brano), 1, tabella_brani) ) 
			{
				int durata_brano;
				durata_brano = leggi_durata_brano(brano_corrente);

				if( classe_durata_brano(durata_brano, durata_cercata) == 1 )
				{
					mostra_brano(brano_corrente);
				}
			}

			if( contatore_brani == 0 )
			{
				printf("Nessun brano corrisponde alla durata inserita..\n");
			}
		}

		fclose(tabella_brani);
	}
	else
	{
		printf("Durata inserita non valida!\n");
	}
}

/********************************************************
 * 
 *  Funzioni di ricerca per artisti
 * 
 ********************************************************/

void ricerca_artisti_nome( char *nome_cercato )
{
	FILE *tabella_artisti;
	tabella_artisti = fopen("artisti.dat", "rb");

	if(tabella_artisti != NULL)
	{
		artista artista_corrente;
		int contatore_artisti;

		contatore_artisti = 0;

		while( fread(&artista_corrente, sizeof(artista), 1, tabella_artisti) )
		{
			// leggo il nome di un artista
			char nome_artista_confronto[DIMNOME_ARTISTA];
			leggi_nome_artista(artista_corrente, nome_artista_confronto);

			// verifico che i due nomi coincidano
			if( strstr(nome_artista_confronto, nome_cercato) != NULL )
			{
				mostra_artista(artista_corrente);

				contatore_artisti = contatore_artisti + 1;
			}
		}

		if( contatore_artisti ==  0 )
		{
			printf("Nessun artista corrsiponde al nome cercato..\n");
		}
	}

	fclose(tabella_artisti);
}

void ricerca_artisti_nome_arte( char *nome_arte_cerca )
{
	FILE* tabella_artisti;
	tabella_artisti = fopen("artisti.dat","rb");

	if( tabella_artisti != NULL )
	{
		artista artista_corrente;
		int contatore_artisti;

		contatore_artisti = 0;

		while( fread(&artista_corrente, sizeof(artista), 1, tabella_artisti) )
		{
			char nome_arte_corrente[DIMNOME_ARTISTA];
			leggi_nome_arte_artista(artista_corrente, nome_arte_corrente);

			if( strstr(nome_arte_corrente, nome_arte_cerca) != NULL )
			{
				mostra_artista(artista_corrente);

				contatore_artisti = contatore_artisti + 1;
			}
		}

		if( contatore_artisti == 0 )
		{
			printf("Nessun artista corrisponde al nome d'arte cercato..\n");
		}
	}

	fclose(tabella_artisti);
}

/********************************************************
 * 
 *  Funzioni di ricerca per album
 * 
 ********************************************************/

void ricerca_album_titolo( char *titolo_cercato )
{
	FILE* tabella_album;
	tabella_album = fopen("album.dat","rb");

	if( tabella_album != NULL )
	{
		album album_corrente;
		int contatore_album;

		contatore_album = 0;

		while( fread(&album_corrente, sizeof(album), 1, tabella_album) )
		{
			char titolo_confronto[DIMTITOLO_ALBUM];
			leggi_titolo_album(album_corrente, titolo_confronto);

			if( strstr(titolo_confronto, titolo_cercato) != NULL )
			{
				mostra_album_singolo(album_corrente);

				contatore_album = contatore_album + 1;
			}
		}

		if( contatore_album == 0 )
		{
			printf("Nessun album corrisponde al titolo cercato..\n");
		}
	}

	fclose(tabella_album);
}

void ricerca_album_anno( int anno_cercato )
{
	if( controllo_anno(anno_cercato) == 1 )
	{
		FILE* tabella_album;
		tabella_album = fopen("album.dat","rb");

		if( tabella_album != NULL )
		{
			album album_corrente;
			int contatore_album;

			contatore_album = 0;

			while( fread(&album_corrente, sizeof(album), 1, tabella_album) )
			{
				int anno_confronto;
				anno_confronto = leggi_anno_album(album_corrente);

				if( anno_cercato == anno_confronto )
				{
					mostra_album_singolo(album_corrente);

					contatore_album = contatore_album + 1;
				}
			}

			if( contatore_album == 0 )
			{
				printf("Nessun album corrsiponde all'anno cercato..\n");
			}
		}

		fclose(tabella_album);
	}
	else
	{
		printf("Anno cercato non valido!\n");
	}
}

/********************************************************
 * 
 *  Funzioni di ricerca per genere
 * 
 ********************************************************/

void ricerca_genere_nome( char *nome_genere_cercato )
{
	FILE* tabella_generi;
	tabella_generi = fopen("generi.dat","rb");

	if( tabella_generi != NULL )
	{
		genere genere_corrente;
		int contatore_genere;

		contatore_genere = 0;

		while( fread(&genere_corrente, sizeof(genere), 1, tabella_generi) )
		{
			char nome_confronto[DIMNOME_GENERE];
			leggi_nome_genere(genere_corrente, nome_confronto);

			if( strstr(nome_confronto, nome_genere_cercato) != NULL )
			{
				mostra_genere(genere_corrente);

				contatore_genere = contatore_genere + 1;
			}
		}

		if( contatore_genere == 0 )
		{
			printf("Nessun genere corrisponde al nome cercato..\n");
		}
	}

	fclose(tabella_generi);
}

/********************************************************
 * 
 *  Funzioni di ricerca per playlist
 * 
 ********************************************************/

void ricerca_playlist_nome( char* nome_cercato, int id_utente_cercato )
{
	FILE* tabella_playlist;
	tabella_playlist = fopen("playlists.dat","rb");

	if( tabella_playlist != NULL )
	{
		playlist playlist_corrente;
		int contatore_playlist;

		contatore_playlist = 0;

		while( fread(&playlist_corrente, sizeof(playlist), 1, tabella_playlist) )
		{
			int utente_playlist_confronto;
			utente_playlist_confronto = leggi_utente_playlist(playlist_corrente);

			// verifico la corrispondenza dell'utente che effetua la ricerca
			if( utente_playlist_confronto == id_utente_cercato )
			{
				char nome_confronto[DIMNOME_PLAYLIST];
				leggi_nome_playlist(playlist_corrente, nome_confronto);

				if( strstr(nome_confronto, nome_cercato) != NULL )
				{
					mostra_playlist(playlist_corrente);
					contatore_playlist = contatore_playlist + 1;
				}
			}
		}

		if( contatore_playlist == 0 )
		{
			printf("Nessuna playlist corrisponde al nome cercato..\n");
		}
	}

	fclose(tabella_playlist);
}

void ricerca_playlist_pubbliche_nome( char* nome_cercato )
{
	FILE* tabella_playlist;
	tabella_playlist = fopen("playlists.dat","rb");

	if( tabella_playlist != NULL )
	{
		playlist playlist_confronto;
		int contatore_playlist;

		contatore_playlist = 0;

		while( fread(&playlist_confronto, sizeof(playlist), 1, tabella_playlist) )
		{
			char nome_playlist_confronto[DIMNOME_PLAYLIST];
			int flag_pubblica_playlist;
			
			leggi_nome_playlist(playlist_confronto, nome_playlist_confronto);
			flag_pubblica_playlist = leggi_flag_pubblica_playlist(playlist_confronto);

			if( flag_pubblica_playlist == 1 && strstr(nome_playlist_confronto, nome_cercato) != NULL )
			{
				mostra_playlist(playlist_confronto);
				contatore_playlist = contatore_playlist + 1;
			} 
		}
		if( contatore_playlist == 0 )
		{
			printf("Non ho trovato alcuna playlist pubblica che corrsponde al nome %s che hai cercato..\n",nome_cercato);
		}
	}

	fclose(tabella_playlist);
}

void ricerca_playlist_pubbliche()
{
	FILE* tabella_playlist;
	tabella_playlist = fopen("playlists.dat","rb");

	if( tabella_playlist != NULL )
	{
		playlist playlist_confronto;
		int contatore_playlist;

		contatore_playlist = 0;

		while( fread(&playlist_confronto, sizeof(playlist), 1, tabella_playlist) )
		{
			int flag_pubblica_playlist;
			flag_pubblica_playlist = leggi_flag_pubblica_playlist(playlist_confronto);

			if( flag_pubblica_playlist == 1 )
			{
				mostra_playlist(playlist_confronto);
				contatore_playlist = contatore_playlist + 1;
			} 
		}
		if( contatore_playlist == 0 )
		{
			printf("Non ho trovato alcuna playlist pubblica..\n");
		}
	}

	fclose(tabella_playlist);
}


/********************************************************
 *
 *  Funzioni di ricerca per le relazioni
 *
 ********************************************************/

brano_artista cerca_relazione_branoArtista( int id_brano )
{
	brano_artista relazione_trovata;
	brano_artista relazione_corrente;
	int id_brano_corrente;
	int trovata;
	FILE *tabella_branoArtista;

	trovata = 0;
	tabella_branoArtista = fopen("brano_artista.dat", "rb");
	if(tabella_branoArtista != NULL){
		while( fread(&relazione_corrente, sizeof(brano_artista), 1, tabella_branoArtista) && trovata == 0 ){
			id_brano_corrente = id_brano_branoArtista(relazione_corrente);
			if(id_brano == id_brano_corrente){
				relazione_trovata = relazione_corrente;
				trovata = 1;
			}
		}
	}

	fclose(tabella_branoArtista);
	return relazione_trovata;
}

brano_album cerca_relazione_branoAlbum( int id_brano )
{
	int trovato;
	brano_album relazione_corrente;
	brano_album relazione_trovata;
	FILE *tabella_brano_album;

	trovato = 0;
	tabella_brano_album = fopen("brano_album.dat", "rb");

	if( tabella_brano_album != NULL )
	{
		trovato = 0;

		while( fread(&relazione_corrente, sizeof(brano_album), 1, tabella_brano_album) && trovato == 0 )
		{
			int id_brano_letto;
			id_brano_letto = id_brano_branoAlbum(relazione_corrente);

			if( id_brano_letto == id_brano )
			{
				relazione_trovata = relazione_corrente;
				trovato = 1;
			}
		}
	}

	fclose(tabella_brano_album);

	return relazione_trovata;
}

brano_genere cerca_relazione_branoGenere( int id_brano )
{
	int trovato;
	brano_genere relazione_corrente;
	brano_genere relazione_trovata;
	FILE *tabella_brano_genere;

	trovato = 0;
	tabella_brano_genere = fopen("brano_genere.dat", "rb");
	if(tabella_brano_genere != NULL)
	{
		while( fread(&relazione_corrente, sizeof(brano_genere), 1, tabella_brano_genere) && trovato == 0 )
		{
			int id_brano_letto;
			id_brano_letto = id_brano_branoGenere(relazione_corrente);

			if( id_brano_letto == id_brano )
			{
				relazione_trovata = relazione_corrente;
				trovato = 1;
			}
		}
	}

	fclose(tabella_brano_genere);

	return relazione_trovata;
}

int conta_brani_playlist( int id_brano )
{
	int occorrenze_brano;
	FILE* tabella_playlistBrano;

	occorrenze_brano = 0;
	tabella_playlistBrano = fopen("playlist_brani.dat","rb");

	if( tabella_playlistBrano != NULL )
	{
		playlist_brano relazione_letta;

		while( fread(&relazione_letta, sizeof(playlist_brano), 1, tabella_playlistBrano) )
		{
			int id_brano_letto;
			id_brano_letto = id_brano_playlistBrano(relazione_letta);

			if( id_brano == id_brano_letto )
			{
				occorrenze_brano = occorrenze_brano + 1;
			}
		}
	}
	fclose(tabella_playlistBrano);

	return occorrenze_brano;
}
