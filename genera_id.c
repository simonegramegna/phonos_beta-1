#include <stdio.h>
#include <stdlib.h>
#include "genera_id.h"

int genera_id(){
    int id;
    FILE *generatore_id;

    id = 0;
    generatore_id = fopen("id.txt", "r+");
    if ( generatore_id != NULL ){
        fscanf( generatore_id, "%d", &id);
        rewind(generatore_id);
        fprintf( generatore_id, "%d", id+1);
    }

    fclose(generatore_id);

    return id;
}
