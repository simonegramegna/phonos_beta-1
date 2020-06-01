#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// numero di secondi in un minuto
#define MINUTO 60 

#include "ricerca.h"
#include "gestione_brani.h"
#include "gestione_generi.h"
#include "gestione_artisti.h"
#include "gestione_playlist.h"


/********************************************************
 * 
 *  Funzioni di ricerca per brani
 * 
********************************************************/

void ricerca_brani_per_titolo( char *titolo_cercato )
{
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");

	if(tabella_brani != NULL)
	{
		brano brano_corrente;

		while( fread(&brano_corrente, sizeof(brano), 1, tabella_brani) )
		{
			// leggo il nome del brano appena letto
			char nome_titolo_confronto[DIMTITOLO];
			leggi_titolo_brano(brano_corrente, nome_titolo_confronto);

			// verifico che i titoli coincidano
			if( strcmp(nome_titolo_confronto, titolo_cercato) == 0 )
			{
				mostra_brano(brano_corrente);
			}
		}
	}

	fclose(tabella_brani);
}

void ricerca_brani_per_durata( int durata_cercata )
{
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");

	if(tabella_brani != NULL)
	{
		brano brano_corrente;

		while(fread(&brano_corrente, sizeof(brano), 1, tabella_brani))
		{
			if( classe_durata_brano(brano_corrente.durata, durata_cercata) )
			{
				mostra_brano(brano_corrente);
			}
		}
	}

	fclose(tabella_brani);
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
 *  Funzioni di ricerca per artisti
 * 
********************************************************/

void ricerca_artisti_per_nome( char *nome_cercato )
{
	FILE *tabella_artisti;

	tabella_artisti = fopen("artisti.dat", "rb");

	if(tabella_artisti != NULL)
	{
		artista artista_corrente;

		while( fread(&artista_corrente, sizeof(artista), 1, tabella_artisti) )
		{
			// leggo il nome di un artista
			char nome_artista_confronto[DIMNOME];
			leggi_nome_artista(artista_corrente, nome_artista_confronto);

			// verifico che i due nomi coincidano
			if( strcmp(nome_artista_confronto, nome_cercato) == 0 )
			{
				mostra_artista(artista_corrente);
			}
		}
	}
	fclose(tabella_artisti);
}
