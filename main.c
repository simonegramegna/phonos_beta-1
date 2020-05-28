#include <stdio.h>
#include <stdlib.h>

#include "gestione_brani.h"
#include "gestione_playlist.h"
#include "gestione_relazioni.h"

int main()
{
	/*
	 * Test funzioni playlistbrano
	*/


	// creo due brani di uno stesso artista
	brano b1, b2;

	scrivi_titolo_brano(&b1, "felicita' puttana\0");
	scrivi_anno_brano(&b1, 2018);
	scrivi_ascolti_brano(&b1, 3000);

	scrivi_titolo_brano(&b2, "riccione\0");
	scrivi_anno_brano(&b2, 2016);
	scrivi_ascolti_brano(&b2, 2016);

	aggiungi_brano(&b1);
	aggiungi_brano(&b2);

	// mi creo una playlist e ci inserisco i 2 brani
	playlist p1;

	

	

	return 0;
}
