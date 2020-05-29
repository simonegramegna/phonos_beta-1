#include <stdio.h>
#include <stdlib.h>

#include "recupero_dati.h"

#include "gestione_relazioni.h"
#include "gestione_playlist.h"
#include "gestione_artisti.h"
#include "gestione_generi.h"
#include "gestione_brani.h"
#include "gestione_album.h"


int ripristina_brani()
{
    FILE* tabella_brani;
    int ripristinato;

    tabella_brani = fopen("brani.dat", "rb+");
    ripristinato = 0;

    if( tabella_brani != NULL )
    {
        brano brano_ripristinato;

        while( fread(&brano_ripristinato, sizeof(brano), 1, tabella_brani) )
        {
            scrivi_flag_eliminato_brano(&brano_ripristinato, 0);

            modifica_brano(brano_ripristinato);
            ripristinato = 1;
        }
    }
    fclose(tabella_brani);

    return ripristinato;
}

int ripristina_artisti()
{
    FILE* tabella_artisti;
    int ripristinato;

    tabella_artisti = fopen("artisti.dat","rb+");
    ripristinato = 0;

    if( tabella_artisti != NULL )
    {
        artista artista_ripristinato;

        while( fread(&artista_ripristinato, sizeof(artista), 1, tabella_artisti) )
        {
            scrivi_flag_eliminato_artista(&artista_ripristinato, 0);

            modifica_artista(artista_ripristinato);
            ripristinato = 1;
        }
    }
    fclose(tabella_artisti);

    return ripristinato;
}

int ripristina_album()
{
    FILE* tabella_album;
    int ripristinato;

    tabella_album = fopen("album.dat","rb+");
    ripristinato = 0;

    if( tabella_album != NULL )
    {
        album album_ripristinato;

        while( fread(&album_ripristinato, sizeof(album), 1, tabella_album) )
        {
            scrivi_flag_eliminato_album(&album_ripristinato, 0);

            modifica_album(album_ripristinato);
            ripristinato = 1;
        }
    }

    fclose(tabella_album);

    return ripristinato;
}

int ripristina_generi()
{
    FILE* tabella_generi;
   int ripristinato;

    tabella_generi = fopen("generi.dat","rb+");
    ripristinato = 0;

    if( tabella_generi != NULL )
    {
        genere genere_ripristinato;

        while( fread(&genere_ripristinato, sizeof(genere), 1, tabella_generi) )
        {
            scrivi_flag_eliminato_genere(&genere_ripristinato, 0);

            modifica_genere(genere_ripristinato);
            ripristinato = 1;
        }
    }
    fclose(tabella_generi);

    return 0;
}

int ripristina_playlist_utente( int id_utente )
{
    FILE* tabella_playlist;
    int ripristinato;

    tabella_playlist = fopen("playlists.dat","rb+");
    ripristinato = 0;

    if( tabella_playlist != NULL )
    {
        playlist playlist_ripristinata;

        while( fread(&playlist_ripristinata, sizeof(playlist), 1, tabella_playlist) )
        {
            int id_utente_confronto = leggi_utente_playlist(playlist_ripristinata);

            if( id_utente == id_utente_confronto )
            {
                scrivi_flag_eliminato_playlist(&playlist_ripristinata, 0);

                modifica_playlist(playlist_ripristinata);
                ripristinato = 1;
            }
        }
    }
    fclose(tabella_playlist);

    return ripristinato;
}

int ripristina_playlist()
{
    FILE* tabella_playlist;
    int ripristinato;

    tabella_playlist = fopen("playlists.dat","rb+");
    ripristinato = 0;

    if( tabella_playlist != NULL )
    {
        playlist playlist_ripristinata;

        while( fread(&playlist_ripristinata, sizeof(playlist), 1, tabella_playlist) )
        {
            scrivi_flag_eliminato_playlist(&playlist_ripristinata, 0);

            modifica_playlist(playlist_ripristinata);
            ripristinato = 1;
        }
    }
    fclose(tabella_playlist);

    return ripristinato;
}

/*
 * Funzioni ripristino dati relazioni  
*/

int ripristina_tabella_branoAlbum()
{
    FILE* tabella_brano_album;
    int ripristinata;

    tabella_brano_album = fopen("brano_album.dat","rb+");
    ripristinata =  0;

    if( tabella_brano_album != NULL )
    {
        brano_album relazione_ripristinata;

        while( fread(&relazione_ripristinata, sizeof(brano_album), 1, tabella_brano_album) )
        {
            scrivi_flag_branoAlbum(&relazione_ripristinata, 0);

            modifica_branoAlbum(relazione_ripristinata);
            ripristinata = 1;
        }
    }
    fclose(tabella_brano_album);

    return ripristinata;
}

int ripristina_tabella_branoArtista()
{
    FILE* tabella_brano_artista;
    int ripristinata;

    tabella_brano_artista = fopen("brano_artista.dat","rb+");
    ripristinata = 0;

    if( tabella_brano_artista != NULL )
    {
        brano_artista relazione_ripristinata;

        while( fread(&relazione_ripristinata, sizeof(brano_artista), 1, tabella_brano_artista) )
        {
            scrivi_flag_branoArtista(&relazione_ripristinata, 0);

            modifica_branoArtista(relazione_ripristinata);
            ripristinata = 1;
        }
    }
    fclose(tabella_brano_artista);

    return ripristinata;
}

int ripristina_tabella_branoGenere()
{
    FILE* tabella_brano_genere;
    int ripristinata;

    tabella_brano_genere = fopen("brano_genere.dat","rb+");
    ripristinata = 0;

    if( tabella_brano_genere != NULL )
    {
        brano_genere relazione_ripristinata;

        while( fread(&relazione_ripristinata, sizeof(brano_genere), 1, tabella_brano_genere) )
        {
            scrivi_flag_branoGenere(&relazione_ripristinata, 0);

            modifica_branoGenere(relazione_ripristinata);
            ripristinata = 1;
        }
    }
    fclose(tabella_brano_genere);

    return ripristinata;
}

int ripristina_tabella_playlistBrano()
{
    FILE* tabella_playlist_brano;
    int ripristinata;

    tabella_playlist_brano = fopen("playlist_brani.dat","rb+");
    ripristinata = 0;

    if( tabella_playlist_brano != NULL )
    {
        playlist_brano relazione_modificata;

        while( fread(&relazione_modificata, sizeof(playlist_brano), 1, tabella_playlist_brano) )
        {
            scrivi_flag_playlistBrano(&relazione_modificata, 0);

            modifica_playlistBrano(relazione_modificata);
            ripristinata = 1;
        }
    }
    fclose(tabella_playlist_brano);

    return ripristinata;
}

/**************************************
 * 
 *  Funzioni backup dati
 * 
 *************************************/