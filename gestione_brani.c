#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestione_brani.h"
#include "gestione_relazioni.h"
#include "ricerca.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_brano(brano brano_selezionato)
{
	return brano_selezionato.id;
}

void leggi_titolo_brano(brano brano_selezionato, char *titolo_letto)
{
	strcpy(titolo_letto, brano_selezionato.titolo);
}

int leggi_durata_brano(brano brano_selezionato)
{
	return brano_selezionato.durata;
}

int leggi_anno_brano(brano brano_selezionato)
{
	return brano_selezionato.anno;
}

int leggi_ascolti_brano(brano brano_selezionato)
{
	return brano_selezionato.ascolti;
}

int leggi_flag_eliminato_brano(brano brano_selezionato)
{
	return brano_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */

void scrivi_id_brano(brano *brano_selezionato, int id)
{
	brano_selezionato->id = id;
}

void scrivi_titolo_brano(brano *brano_selezionato, char *titolo)
{
    strcpy(brano_selezionato->titolo, titolo);
}

void scrivi_durata_brano(brano *brano_selezionato, int durata)
{
	brano_selezionato->durata = durata;
}

void scrivi_anno_brano(brano *brano_selezionato, int anno)
{
	brano_selezionato->anno = anno;
}

void scrivi_ascolti_brano(brano *brano_selezionato, int ascolti)
{
	brano_selezionato->ascolti = ascolti;
}

void scrivi_flag_eliminato_brano(brano *brano_selezionato, int flag_eliminato)
{
	brano_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */

int aggiungi_brano(brano *brano_selezionato)
{
	FILE *tabella_brani;
	int aggiunto;

	aggiunto = 0;
	tabella_brani = fopen("brani.dat", "ab");

	if(tabella_brani != NULL)
	{
		scrivi_flag_eliminato_brano(brano_selezionato, 0);

		fwrite(brano_selezionato, sizeof(brano), 1, tabella_brani);
		aggiunto = 1;
	}
	fclose(tabella_brani);

	return aggiunto;
}

void mostra_brani()
{
	brano brano_corrente;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");

	if(tabella_brani != NULL)
	{
		while( fread(&brano_corrente, sizeof(brano), 1, tabella_brani) )
		{
			mostra_brano(brano_corrente);
		}
	}
	fclose(tabella_brani);
}

void mostra_brano(brano brano_selezionato)
{
	int flag_eliminazione_brano;

	flag_eliminazione_brano = leggi_flag_eliminato_brano(brano_selezionato);

	if(flag_eliminazione_brano != 1 )
	{
		// relazioni in cui compare il brano da leggere
		brano_artista relazione_branoArtista;
		brano_album relazione_branoAlbum;
		brano_genere relazione_branoGenere;

		// dati sull'artista
		artista artista_trovato;
		char nome_arte_artista[DIMNOMEARTE_ARTISTA];

		// dati sull'album
		album album_trovato;
		char titolo_album[DIMTITOLO_ALBUM];

		// dati sul genere
		genere genere_trovato;
		char nome_genere[DIMNOME_GENERE];

		// dati sul brano
		int id_brano_letto;
		char titolo_brano_letto[DIMTITOLO_BRANO];
		int anno_brano_letto;
		int durata_brano_letto;
		int ascolti_brano_letto;

		// leggo i dati dai campi del brano
		id_brano_letto = leggi_id_brano(brano_selezionato);
		leggi_titolo_brano(brano_selezionato, titolo_brano_letto);
		anno_brano_letto = leggi_anno_brano(brano_selezionato);
		durata_brano_letto = leggi_durata_brano(brano_selezionato);
		ascolti_brano_letto = leggi_ascolti_brano(brano_selezionato);

		// leggo le relazioni associate al brano
		relazione_branoArtista = cerca_relazione_branoArtista(id_brano_letto);
		relazione_branoAlbum = cerca_relazione_branoAlbum(id_brano_letto);
		relazione_branoGenere = cerca_relazione_branoGenere(id_brano_letto);
		
		// leggo l'artista
		artista_trovato = cerca_artista(relazione_branoArtista.id_artista);
		leggi_nome_arte_artista(artista_trovato, nome_arte_artista);

		// leggo l'album
		album_trovato = cerca_album(relazione_branoAlbum.id_album);
		leggi_titolo_album(album_trovato, titolo_album);

		// leggo il genere
		genere_trovato = cerca_genere(relazione_branoGenere.id_genere);
		leggi_nome_genere(genere_trovato, nome_genere);

		// stampo i dati letti
		printf("ID: %d				\n", id_brano_letto);
		printf("Titolo: %s			\n", titolo_brano_letto);
		printf("Artista: %s			\n", nome_arte_artista);
		printf("Album: %s			\n", titolo_album);
		printf("Genere: %s			\n", nome_genere);
		printf("Anno: %d 			\n", anno_brano_letto);
		printf("Durata: %d secondi	\n", durata_brano_letto);
		printf("Ascoltato %d volte	\n", ascolti_brano_letto);
	}

	printf("\n");
}

long posizione_brano(int id_brano)
{
    long posizione;
    FILE *tabella_brani;
   
    posizione = -1;
    tabella_brani = fopen("brani.dat", "rb");

    if (tabella_brani != NULL)
	{
		brano brano_corrente;

        while(!feof(tabella_brani) && posizione == -1)
		{
            fread(&brano_corrente, sizeof(brano), 1, tabella_brani);

           	if( leggi_id_brano(brano_corrente) == id_brano)
			{
                posizione = ftell(tabella_brani) - sizeof(brano); // perche' la ftell restituisce blocco successivo
            }
        }
    }
	fclose(tabella_brani);

    return posizione;
}

int elimina_brano(int id_brano)
{
	FILE *tabella_brani;
	int eliminato;
	
	tabella_brani = fopen("brani.dat", "rb+");
	eliminato = 0;

	if(tabella_brani != NULL)
	{
		brano brano_trovato;
		long posizione;

		posizione = posizione_brano(id_brano);
		brano_trovato = cerca_brano(id_brano);
	
		if( posizione != -1 )
		{
			// mi porto nella posizione del record
			fseek(tabella_brani, posizione, SEEK_SET);

			// imposto il flag di eliminazione
			scrivi_flag_eliminato_brano(&brano_trovato, 1);

			fwrite(&brano_trovato, sizeof(brano), 1, tabella_brani);
		} 
		else 
		{
			printf("Brano non trovato \n");
		}
		eliminato = 1;
	}
	fclose(tabella_brani);

	return eliminato;
}

brano cerca_brano(int id_brano)
{
	brano brano_trovato;
	FILE *tabella_brani;

	tabella_brani = fopen("brani.dat", "rb");

	if( tabella_brani != NULL )
	{
		long posizione;
		posizione = posizione_brano(id_brano);

		fseek(tabella_brani, posizione, SEEK_SET);

		fread(&brano_trovato, sizeof(brano), 1, tabella_brani);
	}
	fclose(tabella_brani);

	return brano_trovato;
}

int modifica_brano(brano brano_modificato)
{
	FILE *tabella_brani;
	int modificato;

	tabella_brani = fopen("brani.dat", "rb+");
	modificato = 0;

	if(tabella_brani != NULL)
	{
		int id_brano;
		long posizione;

		// cerco la poszione del brano nella tabella
		id_brano = leggi_id_brano(brano_modificato);

		posizione = posizione_brano(id_brano);
		fseek(tabella_brani, posizione, SEEK_SET);

		fwrite(&brano_modificato, sizeof(brano), 1, tabella_brani);
		modificato = 1;
	}
	fclose(tabella_brani);

	return modificato;
}


