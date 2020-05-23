#include <stdio.h>
#include <stdlib.h>

#include "genera_id.h"

int genera_id()
{
    int id_generato = 0;

    FILE* generatore_id = fopen("id.txt", "r+");

    if ( generatore_id != NULL )
    {
        fscanf( generatore_id, "%d", &id_generato );

        rewind(generatore_id);

        fprintf( generatore_id, "%d", id_generato + 1 );
    }
    else
    {
    	perror("fopen");
    }

    fclose(generatore_id);

    return id_generato;
}
