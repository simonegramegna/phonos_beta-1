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
            int flag_eliminazione = leggi_flag_eliminato_brano(brano_ripristinato);

            if( flag_eliminazione != 0 )
            {
                scrivi_flag_eliminato_brano(&brano_ripristinato, 0);

                fwrite(&brano_ripristinato, sizeof(brano), 1, tabella_brani);
                ripristinato = 1;
            }
        }
    }
    fclose(tabella_brani);

    return ripristinato;
}
