#include <stdio.h>
#include <stdlib.h>

#include "interfaccia.h"
#include "gestione_album.h"
#include "recupero_dati.h"
#include "gestione_brani.h"
#include "gestione_playlist.h"

int main()
{
	//interfaccia_principale();

	brano b1;

	scrivi_titolo_brano(&b1, "hello");
	scrivi_durata_brano(&b1, 500);
	scrivi_anno_brano(&b1, 1987);
	scrivi_ascolti_brano(&b1, 5);

	brano b2;

	scrivi_titolo_brano(&b2, "hello");
	scrivi_durata_brano(&b2, 500);
	scrivi_anno_brano(&b2, 1987);
	scrivi_ascolti_brano(&b2, 5);

	aggiungi_brano(&b1);
	aggiungi_brano(&b2);

	mostra_brani();

	backup_brani();

	stampa_backup_brani();





	return 0;
}
