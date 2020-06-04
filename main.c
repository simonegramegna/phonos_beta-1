#include <stdio.h>
#include <stdlib.h>

#include  "gestione_brani.h"
#include "gestione_playlist.h"
#include "gestione_relazioni.h"

int main()
{
	brano b1, b2;

	// scrivo informazioni del brano b1
	scrivi_titolo_brano(&b1,"under pressure\0");
	scrivi_durata_brano(&b1, 300);
	scrivi_anno_brano(&b1, 1980);
	scrivi_ascolti_brano(&b1, 2500);

	// scrivo le informazioni del brano b2
	scrivi_titolo_brano(&b2,"we are the champions\0");
	scrivi_durata_brano(&b2, 190);
	scrivi_anno_brano(&b2, 1977);
	scrivi_ascolti_brano(&b2, 2500);

	// inserisco i due brani nella base dati
	aggiungi_brano(&b1);
	aggiungi_brano(&b2);


	// mostro i brani
	mostra_brani();


	// creo una playlist
	





	return 0;
}
