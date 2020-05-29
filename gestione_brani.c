#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestione_brani.h"
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
		scrivi_id_brano(brano_selezionato, genera_id());
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
	//if( brano_selezionato.eliminato != 1 )
	//{
		printf("ID: %d				\n", brano_selezionato.id);
		printf("Titolo: %s			\n", brano_selezionato.titolo);
		printf("Anno: %d 			\n", brano_selezionato.anno);
		printf("Durata: %d secondi	\n", brano_selezionato.durata);
		printf("Ascoltato %d volte	\n", brano_selezionato.ascolti);
		printf("Eliminato: %d		\n", brano_selezionato.eliminato);
	//}
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


