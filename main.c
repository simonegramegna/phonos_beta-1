#include <stdio.h>
#include <stdlib.h>


#include "gestione_brani.h"
#include "gestione_album.h"
#include "gestione_relazioni.h"

int main()
{
	// scrivo 3 brani
	brano b1, b2, b3;

	scrivi_titolo_brano(&b1,"Hotel California\0");
	scrivi_anno_brano(&b1, 1980);
	scrivi_durata_brano(&b1, 300);
	scrivi_ascolti_brano(&b1, 5000);

	scrivi_titolo_brano(&b2,"Bohemian Rhapsody \0");
	scrivi_anno_brano(&b2, 1975);
	scrivi_durata_brano(&b2, 300);
	scrivi_ascolti_brano(&b2, 50000);

	scrivi_titolo_brano(&b3,"Stairway to heaven \0");
	scrivi_anno_brano(&b3, 1970);
	scrivi_durata_brano(&b3, 400);
	scrivi_ascolti_brano(&b3, 50000);

	// scrivo 2 album 
	album a1,a2;

	scrivi_titolo_album(&a1, "rock");
	scrivi_anno_album(&a1, 1970);

	scrivi_titolo_album(&a2, "classic\0");
	scrivi_anno_album(&a2, 1975);

	// inserisco i brani nelle basi dati
	aggiungi_brano(&b1);
	aggiungi_brano(&b2);
	aggiungi_brano(&b3);

	// inserisco gli album 
	aggiungi_album(&a1);
	aggiungi_album(&a2);

	// creo le relazioni 
	brano_album r1;
	brano_album r2;
	brano_album r3;

	// metto in relaione b3 e b1 con a1
	scrivi_relazione_branoAlbum(&r3, b1, a1);
	scrivi_relazione_branoAlbum(&r1, b3, a1);

	// metto in realzione 
	scrivi_relazione_branoAlbum(&r2, b2, a2);

	// aggiungo le relazioni alle basi dati
	aggiungi_branoAlbum(&r3,b1,a1);
	aggiungi_branoAlbum(&r1,b3,a1);
	aggiungi_branoAlbum(&r2,b2, a2);


	// stampo i risultati dell'inserimento
	mostra_brani();

	printf("\n");

	mostra_album();

	printf("\n");

	stampa_relazioni();



	return 0;
}
