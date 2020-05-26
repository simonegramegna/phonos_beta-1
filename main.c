#include <stdio.h>
#include <stdlib.h>

#include "gestione_brani.h"
#include "gestione_artisti.h"
#include "gestione_relazioni.h"

int main()
{
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

	// mi creo l'artista
	artista a1;

	scrivi_nome_artista(&a1, "tommaso\0");
	scrivi_cognome_artista(&a1, "paradiso\0");
	scrivi_nome_arte_artista(&a1, "the giornalisti\0");

	// inserisco l'artista
	aggiungi_artista(&a1);

	printf("Stampa brani..\n");

	mostra_brani();

	printf("Stampa artisti..");

	mostra_artisti();

	// mi creo le relazioni
	brano_artista ba1, ba2;

	scrivi_relazione_branoArtista(&ba1,b1,a1);
	scrivi_relazione_branoArtista(&ba2, b2, a1);

	aggiungi_branoArtista(&ba1);
	aggiungi_branoArtista(&ba2);

	printf("\n\n");

	//stampa_brano_artista();

	// provo a modificare una relazione brano_artista dandogli un artista diverso
	artista vasco;


	scrivi_nome_artista(&vasco, "vasco\0");
	scrivi_cognome_artista(&vasco, "rossi\0");
	scrivi_nome_arte_artista(&vasco, "kom\0");

	aggiungi_artista(&vasco);

	printf("nuovo_artista..\n");

	mostra_artisti();

	scrivi_relazione_branoArtista(&ba1,b1,vasco);

	modifica_branoArtista(ba1);

	printf("relazione modificata...\n");

	//stampa_brano_artista();



	

	return 0;
}
