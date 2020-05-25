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
    int flag_brano;  
    int flag_album; 
    
    flag_brano = leggi_flag_eliminato_brano(brano_letto);
    flag_album = leggi_flag_eliminato_album(album_appartenenza);

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

void scrivi_flag_branoAlbum( brano_album* relazione_scritta, brano brano_letto, album album_appartenenza )
{
    // controllo i flag del brano e dell'album messi in relazione
    int flag_brano;  
    int flag_album; 
    
    flag_brano = leggi_flag_eliminato_brano(brano_letto);
    flag_album = leggi_flag_eliminato_album(album_appartenenza);

    /**
     * La relazione esiste se e solo se sia brano 
     * che album esistono
    */
    if( flag_brano == 0 && flag_album == 0 )
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
    int aggiunto;
    FILE* tabella_brano_album;

    aggiunto = 0;
    tabella_brano_album = fopen("brano_album.dat","ab+");

    if( tabella_brano_album != NULL )
    {
        scrivi_id_branoAlbum(relazione_inserita,genera_id());
        scrivi_flag_branoAlbum(relazione_inserita, brano_letto, album_appartenenza );

        fwrite(relazione_inserita, sizeof(brano_album), 1, tabella_brano_album );
        aggiunto = 1;
    }

    fclose(tabella_brano_album);

    return aggiunto;
}


long posizione_branoAlbum( int id_branoAlbum )
{
    long posizione; 
    FILE* tabella_branoAlbum;

    posizione = -1;
    tabella_branoAlbum = fopen("brano_album.dat","rb");

    if( tabella_branoAlbum != NULL )
    {
        while( !feof(tabella_branoAlbum) && posizione == -1 )
        {
            brano_album relazione_confronto;

            fread(&relazione_confronto,sizeof(brano_album),1, tabella_branoAlbum);

            if( id_branoAlbum == leggi_id_branoAlbum(relazione_confronto) )
            {
                posizione = ftell(tabella_branoAlbum) - sizeof(brano_album); // la ftell() restituisce blocco successsivo
            }
        }
    }
    fclose(tabella_branoAlbum);

    return posizione;
}

brano_album cerca_branoAlbum( int id_branoAlbum )
{
    brano_album relazione_trovata;
    FILE* tabella_branoAlbum;
    
    tabella_branoAlbum = fopen("brano_album.dat","rb");

    if( tabella_branoAlbum != NULL )
    {
        // cerco la posizione del record selezionato e posiziono la testina su quel record
        long posizione;
        posizione = posizione_branoAlbum(id_branoAlbum);

        fseek(tabella_branoAlbum, posizione, SEEK_SET);

        if( posizione != -1 )
        {
            fread(&relazione_trovata, sizeof(brano_album), 1, tabella_branoAlbum );
        } 
    }
    fclose(tabella_branoAlbum);

    return relazione_trovata;
}


int elimina_branoAlbum( int id_branoAlbum )
{
    int eliminato;
    long posizione;
    FILE* tabella_branoAlbum;
    
    eliminato = 0;
    posizione = posizione_branoAlbum(id_branoAlbum);
    
    tabella_branoAlbum = fopen("brano_album.dat","rb+");

    if( tabella_branoAlbum != NULL && posizione != -1 )
    {
        brano_album relazione_eliminata;
        brano brano_relazione;
        album album_relazione;

        // elimino il brano se o il brano oppure l'album non esiste
        relazione_eliminata = cerca_branoAlbum(id_branoAlbum);
        brano_relazione = cerca_brano( id_brano_branoAlbum(relazione_eliminata) );
        album_relazione = cerca_album( id_album_branoAlbum(relazione_eliminata) );

        scrivi_flag_branoAlbum(&relazione_eliminata, brano_relazione, album_relazione);

        // mi porto in posizione del branoalbum da eliminare
        fseek(tabella_branoAlbum, posizione, SEEK_SET );

        // scrivo la relazione eliminata 
        fwrite(&relazione_eliminata, sizeof(brano_album), 1, tabella_branoAlbum );

        // elimino il record branoalbum se o il brano oppure l'album non esiste
        if( leggi_flag_eliminato_brano(brano_relazione) == 1 || leggi_flag_eliminato_album(album_relazione) == 1 )
        {
            eliminato = 1;
            printf("La relazione selezionata e' stata eliminata \n");
        }
    }

    fclose(tabella_branoAlbum);

    return eliminato;
}

int modifica_branoAlbum( brano_album relazione_modificata )
{
    int modificato;
    FILE* tabella_branoAlbum;

    modificato = 0;
    tabella_branoAlbum = fopen("brano_album.dat","rb+");

    if( tabella_branoAlbum != NULL )
    {
        long posizione;
        int id_relazione_modificata;

        // cerco la posizione del record selezionato all'interno del file
        id_relazione_modificata = leggi_id_branoAlbum(relazione_modificata);
        posizione = posizione_branoAlbum( id_relazione_modificata );
        
        // verifico che il record esista e non sia stato eliminato
        if( posizione != -1 && leggi_flag_branoAlbum(relazione_modificata) == 0 )
        {
            fseek(tabella_branoAlbum, posizione, SEEK_SET);

            // scrivo nella tabella la relazione modificata
            fwrite(&relazione_modificata, sizeof(brano_album), 1, tabella_branoAlbum );

            modificato = 1;
        } 
    }

    fclose(tabella_branoAlbum);

    return modificato;
}



void stampa_relazioni()
{
    FILE* tab = fopen("brano_album.dat","rb");

    if( tab != NULL )
    {
        brano_album conf;
        while( fread(&conf, sizeof(brano_album), 1, tab ) )
        {
            int id_rel = leggi_id_branoAlbum(conf);
            int br = id_brano_branoAlbum(conf);
            int al = id_album_branoAlbum(conf);
            int f = leggi_flag_branoAlbum(conf);

            printf("Id: %d, brano: %d, album: %d, flag: %d \n",id_rel,br,al,f);
        }
    }
}