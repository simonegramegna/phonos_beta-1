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

void scrivi_flag_branoAlbum( brano_album* relazione_scritta, int flag_relazione )
{
    relazione_scritta->flag_brano_album = flag_relazione;
}

/**
 * Operazioni su file branoAlbum
*/

int aggiungi_branoAlbum( brano_album* relazione_inserita )
{
    int aggiunto;
    FILE* tabella_brano_album;

    aggiunto = 0;
    tabella_brano_album = fopen("brano_album.dat","ab+");

    if( tabella_brano_album != NULL )
    {
        scrivi_id_branoAlbum( relazione_inserita, genera_id() );
        scrivi_flag_branoAlbum( relazione_inserita, 0 );

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

    // posizione del record da eliminare
    posizione = posizione_branoAlbum(id_branoAlbum);
    
    tabella_branoAlbum = fopen("brano_album.dat","rb+");

    if( tabella_branoAlbum != NULL && posizione != -1 )
    {
        brano_album relazione_eliminata;
        relazione_eliminata = cerca_branoAlbum(id_branoAlbum);

        // imposto a eliminato il record
        scrivi_flag_branoAlbum(&relazione_eliminata, 1 );

        // mi porto in posizione del branoalbum da eliminare
        fseek(tabella_branoAlbum, posizione, SEEK_SET );

        // scrivo la relazione eliminata 
        fwrite(&relazione_eliminata, sizeof(brano_album), 1, tabella_branoAlbum );
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


/*********************************************
 * 
 * Funzioni BranoArtista
 * 
 *********************************************/

int leggi_id_branoArtista( brano_artista relazione_letta )
{
    return relazione_letta.id_brano_artista;
}

void scrivi_id_branoArtista( brano_artista* relazione_scritta, int id_assegnato )
{
    relazione_scritta->id_brano_artista = id_assegnato;
}

int id_brano_branoArtista( brano_artista relazione_letta )
{
    return relazione_letta.id_brano;
}

int id_artista_branoArtista( brano_artista relazione_letta )
{
    return relazione_letta.id_artista;
}

void scrivi_relazione_branoArtista( brano_artista* relazione_scritta, brano brano_letto, artista artista_appartenenza )
{
    int flag_brano;
    int flag_artista; 
    
    flag_brano = leggi_flag_eliminato_brano(brano_letto); 
    flag_artista = leggi_flag_eliminato_artista(artista_appartenenza);

    // verifico che il brano e l'artista esistano
    if( flag_brano == 0 && flag_artista == 0 )
    {
        int id_brano = leggi_id_brano(brano_letto);
        int id_artista = leggi_id_artista(artista_appartenenza);

        relazione_scritta->id_brano = id_brano;
        relazione_scritta->id_artista = id_artista;
    }
}

int leggi_flag_branoArtista( brano_artista relazione_letta )
{
    return relazione_letta.flag_brano_artista;
}

void scrivi_flag_branoArtista( brano_artista* relazione_scritta, int flag_relazione )
{
    relazione_scritta->flag_brano_artista = flag_relazione;
}

/*
 * Operazioni su file per brano_artista
*/

int aggiungi_branoArtista( brano_artista* relazione_inserita )
{
    int aggiunto;
    FILE* tabella_brano_artista;

    aggiunto = 0;
    tabella_brano_artista = fopen("brano_artista.dat","ab");

    if( tabella_brano_artista != NULL )
    {
        scrivi_id_branoArtista( relazione_inserita, genera_id() );
        scrivi_flag_branoArtista( relazione_inserita, 0 );

        fwrite(relazione_inserita, sizeof(brano_artista), 1, tabella_brano_artista);
        aggiunto = 1;
    }
    fclose(tabella_brano_artista);

    return aggiunto;
}

long posizione_branoArtista( int id_branoArtista )
{
    long posizione;
    FILE* tabella_branoArtista;

    posizione = -1;
    tabella_branoArtista = fopen("brano_artista.dat","rb");

    if( tabella_branoArtista != NULL )
    {
        while( !feof(tabella_branoArtista) && posizione == -1 )
        {
            brano_artista confronto;
            fread(&confronto, sizeof(brano_artista), 1, tabella_branoArtista );

            if( leggi_id_branoArtista(confronto) == id_branoArtista )
            {
                posizione = ftell(tabella_branoArtista) - sizeof(brano_artista); // la ftell prende il blocco successivo
            }
        }
    }
    fclose(tabella_branoArtista);

    return posizione;
}

brano_artista cerca_branoArtista( int id_branoArtista )
{
    brano_artista relazione_trovata;
    FILE* tabella_branoArtista;

    tabella_branoArtista = fopen("brano_artista.dat","rb");

    if( tabella_branoArtista != NULL )
    {
        long posizione;
        posizione = posizione_branoArtista( id_branoArtista );

        // posiziono la testina sul record nel file
        fseek( tabella_branoArtista, posizione, SEEK_SET );

        fread(&relazione_trovata, sizeof(brano_artista), 1, tabella_branoArtista); 
    }
    fclose(tabella_branoArtista);

    return relazione_trovata;
}

int elimina_branoArtista( int id_branoArtista )
{
    int eliminato;
    FILE* tabella_branoArtisti;

    eliminato = 0;
    tabella_branoArtisti = fopen("brano_artista.dat","rb+");

    if( tabella_branoArtisti != NULL )
    {
        long posizione;
        brano_artista relazione_eliminata;

        posizione = posizione_branoArtista(id_branoArtista);
        relazione_eliminata = cerca_branoArtista(id_branoArtista);

        // imposto il flag a eliminato
        scrivi_flag_branoArtista(&relazione_eliminata,1);

        // mi porto in posizione del recor da eliminare
        fseek(tabella_branoArtisti, posizione, SEEK_SET);

        fwrite(&relazione_eliminata, sizeof(brano_artista), 1, tabella_branoArtisti );
        eliminato = 1;
    }
    fclose(tabella_branoArtisti);

    return eliminato;
}

int modifica_branoArtista( brano_artista relazione_modificata )
{
    int modificato;
    FILE* tabella_branoArtista;

    modificato = 0;
    tabella_branoArtista = fopen("brano_artista.dat","rb+");

    if( tabella_branoArtista != NULL )
    {
        int id_relazione;
        long posizione;

        id_relazione = leggi_id_branoArtista(relazione_modificata);
        posizione = posizione_branoArtista(id_relazione);

        // mi porto nella poszione del recor modificato
        fseek( tabella_branoArtista, posizione, SEEK_SET );

        fwrite(&relazione_modificata, sizeof(brano_artista), 1, tabella_branoArtista );
        modificato = 1;

    }
    fclose(tabella_branoArtista);

    return modificato;
}

void stampa_brano_artista()
{
    FILE* tab = fopen("brano_artista.dat","rb");

    if( tab != NULL )
    {
        brano_artista letto;

        while( fread(&letto, sizeof(brano_artista), 1, tab) )
        {
            int id = leggi_id_branoArtista(letto);
            int art = id_artista_branoArtista(letto);
            int br = id_brano_branoArtista(letto);
            int flag = leggi_flag_branoArtista(letto);

            printf("id: %d, artista: %d, brano: %d, flag: %d\n",id,art,br,flag);
        }
    }
    fclose(tab);
}
