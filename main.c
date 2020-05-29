#include <stdio.h>
#include <stdlib.h>

#include "interfaccia.h"
#include "gestione_brani.h"
#include "recupero_dati.h"

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

	printf("brani inseriti..\n");
	mostra_brani();
	
	printf("\n\n");

	printf("elimino_brano 1..");

	elimina_brano(2);
	elimina_brano(3);

	mostra_brani();

	printf("..\n riprisitno ..\n\n");

	ripristina_brani();

	mostra_brani();


	return 0;
}
