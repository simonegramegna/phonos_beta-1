#include <stdio.h>
#include <stdlib.h>

#include "gestione_relazioni.h"
#include "gestione_brani.h"
#include "gestione_album.h"
#include "gestione_generi.h"
#include "gestione_artisti.h"
#include "genera_id.h"


int leggi_id_branoAlbum( brano_album relazione_letta )
{
    return relazione_letta.id_brano_album;
}

void scrivi_id_branoAlbum( brano_album* relazione_scritta, int id_assegnato )
{
    relazione_scritta->id_brano_album = id_assegnato;
}

int id_album_branoAlbum( brano_album relazione_letta )
{
    return relazione_letta.id_album;
}

int id_brano_branoAlbum( brano_album relazione_letta )
{
    return relazione_letta.id_brano;
}

void scrivi_relazione_branoAlbum( brano_album* relazione_scritta, brano brano_letto, album album_appartenenza )
{
    int flag_brano =  leggi_flag_eliminato_brano(brano_letto);
    int flag_album  = leggi_flag_eliminato_album(album_appartenenza);

    // verifico che sia il brano che l'album esistano
    if( flag_brano == 0 && flag_album == 0 )
    {
        int id_brano = leggi_id_brano(brano_letto);
        int id_album = leggi_id_album(album_appartenenza);

        relazione_scritta->id_brano = id_brano;
        relazione_scritta->id_album = id_album;
    }
}

int leggi_flag_branoAlbum( brano_album relazione_letta )
{
    return relazione_letta.flag_brano_album;
}

void scrivi_flag_branoAlbum( brano_album* relazione_scritta, brano brano_letto, album album_appartenenza, int flag_branoAlbum )
{
    // controllo i flag del brano e dell'album messi in relazione
    int flag_brano = leggi_flag_eliminato_brano(brano_letto);
    int flag_album = leggi_flag_eliminato_album(album_appartenenza);

    /**
     * La relazione esiste se e solo se sia brano 
     * che album esistono
    */
    if( flag_brano == 0 && flag_album == 0 && flag_branoAlbum == 0 )
    {
        relazione_scritta->flag_brano_album = 0;
    }
    else
    {
        relazione_scritta->flag_brano_album = 1;
    }
}

/**
 * Operazioni su file branoAlbum
*/

int aggiungi_branoAlbum( brano_album* relazione_inserita, brano brano_letto, album album_appartenenza )
{
    int aggiunto = 0;
    FILE* tabella_brano_album = fopen("brano_album.dat","ab");

    if( tabella_brano_album != NULL )
    {
        scrivi_id_branoAlbum(relazione_inserita,genera_id());
        scrivi_flag_branoAlbum(relazione_inserita, brano_letto, album_appartenenza, 0);

        fwrite(relazione_inserita, sizeof(brano_album), 1, tabella_brano_album );
        aggiunto = 1;
    }

    fclose(tabella_brano_album);

    return aggiunto;
}

void stampa_relazioni()
{
    FILE* tab = fopen("brano_album.dat","rb");

    if( tab != NULL )
    {
        while( !feof(tab) )
        {
            brano_album conf;

            fread(&conf, sizeof(brano_album), 1, tab );

            int id_rel = leggi_id_branoAlbum(conf);
            int br = id_brano_branoAlbum(conf);
            int al = id_album_branoAlbum(conf);
            int f = leggi_flag_branoAlbum(conf);

            printf("Id: %d, brano: %d, album: %d, flag: %d \n",id_rel,br,al,f);
        }
    }
}