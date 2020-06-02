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
        int id_brano;
        int id_album;
         
        id_brano = leggi_id_brano(brano_letto);
        id_album = leggi_id_album(album_appartenenza);

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

/*
 * Operazioni su campi brano_artista
*/

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
            fread( &confronto, sizeof(brano_artista), 1, tabella_branoArtista );

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

        // mi porto in posizione del record da eliminare
        fseek(tabella_branoArtisti, posizione, SEEK_SET);

        fwrite(&relazione_eliminata, sizeof(brano_artista), 1, tabella_branoArtisti);
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

        // mi porto nella poszione del record modificato
        fseek(tabella_branoArtista, posizione, SEEK_SET);

        fwrite(&relazione_modificata, sizeof(brano_artista), 1, tabella_branoArtista );
        modificato = 1;

    }
    fclose(tabella_branoArtista);

    return modificato;
}

/*********************************************
 * 
 * Funzioni BranoGenere
 * 
 *********************************************/

/*
 * Operazioni su campi brano_genere 
*/

int leggi_id_branoGenere( brano_genere relazione_letta )
{
    return relazione_letta.id_branoGenere;
}

void scrivi_id_branoGenere( brano_genere* relazione_scritta, int id_assegnato )
{
    relazione_scritta->id_branoGenere = id_assegnato;
}

int id_brano_branoGenere( brano_genere relazione_letta )
{
    return relazione_letta.id_brano;
}

int id_genere_branoGenere( brano_genere relazione_letta )
{
    return relazione_letta.id_genere;
}

void scrivi_relazione_branoGenere( brano_genere* relazione_scritta, brano brano_letto, genere genere_appartenenza )
{
    int flag_brano;
    int flag_genere;

    flag_brano = leggi_flag_eliminato_brano(brano_letto);
    flag_genere = leggi_flag_eliminato_genere(genere_appartenenza);

    // verifico che sia il brano che il genere esistano nella base dati
    if( flag_brano == 0 && flag_genere == 0 )
    {
        int id_brano;
        int id_genere;
        
        id_brano = leggi_id_brano(brano_letto);
        id_genere = leggi_id_genere(genere_appartenenza);

        relazione_scritta->id_brano = id_brano;
        relazione_scritta->id_genere = id_genere;
    }
}

int leggi_flag_branoGenere( brano_genere relazione_letta )
{
    return relazione_letta.flag_brano_genere;
}

void scrivi_flag_branoGenere( brano_genere* relazione_scritta, int flag_relazione )
{
    relazione_scritta->flag_brano_genere = flag_relazione;
}

/*
 * Operazioni su file per brano_genere
*/

int aggiungi_branoGenere( brano_genere* relazione_inserita )
{
    int aggiunto;
    FILE* tabella_brano_genere;

    aggiunto = 0;
    tabella_brano_genere = fopen("brano_genere.dat","ab");

    if( tabella_brano_genere != NULL )
    {
        scrivi_id_branoGenere( relazione_inserita, genera_id() );
        scrivi_flag_branoGenere( relazione_inserita, 0 );

        fwrite(relazione_inserita, sizeof(brano_genere), 1, tabella_brano_genere );
        aggiunto = 1;
    }
    fclose(tabella_brano_genere);

    return aggiunto;
}

long posizione_branoGenere( int id_branoGenere )
{
    long posizione;
    FILE* tabella_brano_genere;

    posizione = -1;
    tabella_brano_genere = fopen("brano_genere.dat","rb");

    if( tabella_brano_genere != NULL )
    {
        while( !feof(tabella_brano_genere) && posizione == -1 )
        {
            brano_genere confronto;
            fread( &confronto, sizeof(brano_genere), 1, tabella_brano_genere );

            if( leggi_id_branoGenere(confronto) == id_branoGenere )
            {
                posizione = ftell(tabella_brano_genere) - sizeof(brano_genere); // la ftell prende il blocco successivo
            }
        }
    }
    fclose(tabella_brano_genere);

    return posizione;
}

int elimina_branoGenere( int id_branoGenere )
{
    int eliminato;
    FILE* tabella_branoGenere;

    eliminato = 0;
    tabella_branoGenere = fopen("brano_genere.dat","rb+");

    if( tabella_branoGenere != NULL )
    {
        long posizione;
        brano_genere relazione_eliminata;

        posizione = posizione_branoGenere(id_branoGenere);
        relazione_eliminata = cerca_branoGenere(id_branoGenere);

        // imposto il flag a eliminato
        scrivi_flag_branoGenere(&relazione_eliminata,1);

        // mi porto in posizione del record da eliminare
        fseek(tabella_branoGenere, posizione, SEEK_SET);

        fwrite(&relazione_eliminata, sizeof(brano_genere), 1, tabella_branoGenere);
        eliminato = 1;
    }
    fclose(tabella_branoGenere);

    return eliminato;
}

brano_genere cerca_branoGenere( int id_branoGenere )
{
    brano_genere relazione_trovata;
    FILE* tabella_branoGenere;

    tabella_branoGenere = fopen("brano_genere.dat","rb");

    if( tabella_branoGenere != NULL )
    {
        long posizione;
        posizione = posizione_branoGenere( id_branoGenere );

        // posiziono la testina sul record del file
        fseek( tabella_branoGenere, posizione, SEEK_SET );

        fread(&relazione_trovata, sizeof(brano_genere), 1, tabella_branoGenere);
    }
    fclose(tabella_branoGenere);

    return relazione_trovata;
}

int modifica_branoGenere( brano_genere relazione_modificata )
{
    int modificato;
    FILE* tabella_branoGenere;

    modificato = 0;
    tabella_branoGenere = fopen("brano_genere.dat","rb+");

    if( tabella_branoGenere != NULL )
    {
       int id_relazione;
       long posizione;

       id_relazione = leggi_id_branoGenere(relazione_modificata);
       posizione = posizione_branoGenere(id_relazione);

        // mi porto nella poszione del record modificato
        fseek(tabella_branoGenere, posizione, SEEK_SET );

        fwrite(&relazione_modificata, sizeof(brano_genere), 1, tabella_branoGenere);
        modificato = 1; 
   
    }
    fclose(tabella_branoGenere);

    return modificato;
}


/*********************************************
 * 
 * Funzioni PlaylistBrano
 * 
 *********************************************/

/*
 * Operazioni su campi playlist_brano 
*/

int leggi_id_playlistBrano( playlist_brano relazione_letta )
{
    return relazione_letta.id_playlistBrano;
}

void scrivi_id_playlistBrano( playlist_brano* relazione_scritta, int id_assegnato )
{
    relazione_scritta->id_playlistBrano = id_assegnato;
}

int id_playlist_playlistBrano( playlist_brano relazione_letta )
{
    return relazione_letta.id_playlist;
}

int id_brano_playlistBrano( playlist_brano relazione_letta )
{
    return relazione_letta.id_brano;
}

void scrivi_relazione_playlistBrano( playlist_brano* relazione_scritta, brano brano_letto, playlist playlist_appartenenza )
{
    int flag_brano;
    int flag_playlist;

    flag_brano = leggi_flag_eliminato_brano(brano_letto);
    flag_playlist = leggi_flag_eliminato_playlist(playlist_appartenenza);

    if( flag_brano == 0 && flag_playlist == 0 )
    {
        int id_brano;
        int id_playlist;

        id_brano = leggi_id_brano(brano_letto);
        id_playlist = leggi_id_playlist(playlist_appartenenza);

        relazione_scritta->id_brano = id_brano;
        relazione_scritta->id_playlist = id_playlist;
    }
}

int leggi_flag_playlistBrano( playlist_brano relazione_letta )
{
    return relazione_letta.flag_playlist_brano;
}

void scrivi_flag_playlistBrano( playlist_brano* relazione_scritta, int flag_relazione )
{
    relazione_scritta->flag_playlist_brano = flag_relazione;
}

/*
 * Operazioni su file 
*/

int aggiungi_playlistBrano( playlist_brano* relazione_aggiunta )
{
    FILE* tabella_playlist_brani;
    int aggiunto;

    tabella_playlist_brani = fopen("playlist_brani.dat","ab");
    aggiunto = 0;

    if( tabella_playlist_brani != NULL )
    {
        scrivi_id_playlistBrano( relazione_aggiunta, genera_id() );
        scrivi_flag_playlistBrano( relazione_aggiunta, 0 );

        fwrite(relazione_aggiunta, sizeof(playlist_brano), 1, tabella_playlist_brani);
        aggiunto = 1;
    }
    fclose(tabella_playlist_brani);

    return aggiunto;
}

long posizione_playlistBrano( int id_playlistBrano )
{
    long posizione;
    FILE* tabella_playlist_brani;

    tabella_playlist_brani = fopen("playlist_brani.dat","rb");
    posizione = -1;

    if( tabella_playlist_brani != NULL )
    {
        while( !feof(tabella_playlist_brani) && posizione == -1 )
        {
            playlist_brano confronto;

            fread(&confronto, sizeof(playlist_brano), 1, tabella_playlist_brani);

            if( leggi_id_playlistBrano(confronto) == id_playlistBrano )
            {
                posizione = ftell(tabella_playlist_brani) - sizeof(playlist_brano); // la ftell prende il blocco successivo
            }
        }
    }
    fclose(tabella_playlist_brani);

    return posizione;
}

playlist_brano cerca_playlistBrano( int id_playlistBrano )
{
    playlist_brano relazione_trovata;
    FILE* tabella_playlist_brano;

    tabella_playlist_brano = fopen("playlist_brani.dat","rb");

    if( tabella_playlist_brano != NULL )
    {
        long posizione;
        posizione = posizione_playlistBrano(id_playlistBrano);

        // mi porto nella posizione del record selezionato
        fseek(tabella_playlist_brano, posizione, SEEK_SET);

        fread(&relazione_trovata, sizeof(playlist_brano), 1, tabella_playlist_brano);
    }
    fclose(tabella_playlist_brano);

    return relazione_trovata;
}

int elimina_playlistBrano( int id_playlistBrano )
{
    int eliminato;
    FILE* tabella_playlist_brano;

    tabella_playlist_brano = fopen("playlist_brani.dat","rb+");
    eliminato = 0;

    if( tabella_playlist_brano != NULL )
    {
        long posizione;
        playlist_brano relazione_eliminata;

        posizione = posizione_playlistBrano(id_playlistBrano);
        relazione_eliminata = cerca_playlistBrano(id_playlistBrano);

        // imposto il flag a eliminato
        scrivi_flag_playlistBrano(&relazione_eliminata,1);

        // mi porto nella posizione del record
        fseek(tabella_playlist_brano, posizione, SEEK_SET);

        fwrite(&relazione_eliminata, sizeof(playlist_brano), 1, tabella_playlist_brano);
        eliminato = 1;
    }
    fclose(tabella_playlist_brano);

    return eliminato;
}

int modifica_playlistBrano( playlist_brano relazione_modificata )
{
    int modificato;
    FILE* tabella_playlist_brano;

    tabella_playlist_brano = fopen("playlist_brani.dat","rb+");
    modificato = 0;

    if( tabella_playlist_brano != NULL )
    {
        int id_relazione;
        long posizione;

        id_relazione = leggi_id_playlistBrano(relazione_modificata);
        posizione = posizione_playlistBrano(id_relazione);
        
        // mi porto nella posizione del record da modificare
        fseek(tabella_playlist_brano, posizione, SEEK_SET);

        fwrite(&relazione_modificata, sizeof(playlist_brano), 1, tabella_playlist_brano);
        modificato = 1;
    }
    fclose(tabella_playlist_brano);

    return modificato;
}

void stampa_playlist_brano()
{
    FILE* tab = fopen("playlist_brani.dat","rb");

    if( tab != NULL )
    {
        playlist_brano conf;

        while( fread(&conf, sizeof(playlist_brano), 1, tab) )
        {
            int id_rel = leggi_id_playlistBrano(conf);
            int brano = id_brano_playlistBrano(conf);
            int play = id_playlist_playlistBrano(conf);
            int flag = leggi_flag_playlistBrano(conf);

            printf("id: %d, id_brano: %d, id_playlist: %d, flag: %d\n" ,id_rel, brano, play, flag);
        }
    }
    fclose(tab);
}
