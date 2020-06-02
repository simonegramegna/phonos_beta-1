#include <stdio.h>
#include <stdlib.h>

#include  "gestione_brani.h"
#include "gestione_artisti.h"
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

	// creo l'artista
	artista a1;

	scrivi_nome_artista(&a1,"farrokh\0");
	scrivi_cognome_artista(&a1, "bulsara\0");
	scrivi_nome_arte_artista(&a1, "Freddie Mercury\0");

	// aggiungo l'artista 
	aggiungi_artista(&a1);

	printf("\n");

	// mostro la gli artisti inseriti
	mostra_artisti();

	// creo le relazioni tra i due brani e l'artista creato
	brano_artista r1, r2;

	scrivi_relazione_branoArtista(&r1, b1, a1);
	scrivi_relazione_branoArtista(&r2, b2, a1);

	// aggiungo le due relazioni alla base dati
	aggiungi_branoArtista(&r1);
	aggiungi_branoArtista(&r2);

	// stampo le relazioni create
	stampa_branoartista();




	return 0;
}
