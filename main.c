#include <stdio.h>
#include <stdlib.h>

#include "gestione_brani.h"
#include "gestione_generi.h"
#include "gestione_relazioni.h"

int main()
{
	/*
	 * Test funzioni playlist
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

	// creo un generecon 2 brani
	genere g1;

	scrivi_nome_genere(&g1,"pop\0");

	aggiungi_genere(&g1);

	brano_genere bg1,bg2;

	// scrivo le relazioni
	scrivi_relazione_branoGenere(&bg1,b1,g1);
	scrivi_relazione_branoGenere(&bg2,b2, g1);

	aggiungi_branoGenere(&bg1);
	aggiungi_branoGenere(&bg2);

	
	printf("brani...\n");
	mostra_brani();

	printf("generi...\n");
	mostra_generi();

	printf("\n\nRelazioni \n");
	stampa_branogenere();

	// modifico un brano genere
	//brano_genere br2;
	brano six;

	scrivi_titolo_brano(&six, "diocane\0");
	scrivi_anno_brano(&six, 2016);
	scrivi_ascolti_brano(&six, 2016);

	aggiungi_brano(&six);

	modifica_branoGenere(bg2);

	printf("\n\nModifica\n");

	mostra_brani();

	printf("relazioni\n");
	stampa_branogenere();

	return 0;
}
