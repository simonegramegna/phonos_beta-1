#include <stdio.h>
#include <stdlib.h>


#include "gestione_brani.h"
#include "gestione_album.h"
#include "gestione_relazioni.h"

int main(){
	
	brano b1;

	scrivi_titolo_brano(&b1,"Felling good\0");
	scrivi_durata_brano(&b1, 125);
	scrivi_anno_brano(&b1, 2020);
	scrivi_ascolti_brano(&b1, 10);

	aggiungi_brano(&b1);

	album a1;
	scrivi_titolo_album(&a1,"good\0");
	scrivi_anno_album(&a1, 2020);

	aggiungi_album(&a1);

	mostra_brani();
	printf("\n");
	mostra_album();

	brano_album c1;

	elimina_brano(23);

	scrivi_relazione_branoAlbum(&c1, b1, a1);



	aggiungi_branoAlbum(&c1,b1,a1);

	printf("\n");

	stampa_relazioni();

	/*

	int x = id_brano_branoAlbum(c1);
	int y = id_album_branoAlbum(c1);

	printf("\nId relazione: brano %d , album %d \n",x,y);*/

	return 0;
}
