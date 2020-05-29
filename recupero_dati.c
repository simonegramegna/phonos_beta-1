#include <stdio.h>
#include <stdlib.h>

#include "recupero_dati.h"

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
        }
    }

    fclose(tabella_album);

    return ripristinato;
}