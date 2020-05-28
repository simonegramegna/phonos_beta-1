#include <stdio.h>
#include <stdlib.h>

#include "interfaccia.h"
#include "gestione_brani.h"
#include "recupero_dati.h"

int main()
{
	//interfaccia_principale();

	
	brano b1, b2;

	scrivi_titolo_brano(&b1, "felicita' puttana\0");
	scrivi_durata_brano(&b1, 200);
	scrivi_anno_brano(&b1, 2018);
	scrivi_ascolti_brano(&b1, 12);

	scrivi_titolo_brano(&b2, "felicita' troia\0");
	scrivi_durata_brano(&b2, 200);
	scrivi_anno_brano(&b2, 2019);
	scrivi_ascolti_brano(&b2, 12);

	aggiungi_brano(&b1);
	aggiungi_brano(&b2);

	mostra_brani();

	//elimina_brano(9);
	elimina_brano(12);

	printf("eliminati..\n");
	mostra_brani();

	ripristina_brani();

	printf("\n brani ripristinati \n");

	mostra_brani();


	return 0;
}
