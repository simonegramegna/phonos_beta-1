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
	playlist p1;

	scrivi_utente_playlist(&p1, 101);
	scrivi_nome_playlist(&p1, "una su mille me la da'\0");
	scrivi_descrizione_playlist(&p1, "una su centomila\0");
	scrivi_flag_pubblica_playlist(&p1, 1);

	aggiungi_playlist(&p1);

	mostra_playlists();

	int id_brano1 = leggi_id_brano(b1);
	int id_brano2 = leggi_id_brano(b2);
	int id_play = leggi_id_playlist(p1);

	playlist_brano r1,r2;

	scrivi_relazione_playlistBrano(&r1, id_brano1, id_play);
	scrivi_relazione_playlistBrano(&r2, id_brano2, id_play);

	aggiungi_playlistBrano(&r1);
	aggiungi_playlistBrano(&r2);

	printf("\n\n");

	stampa_playlist_brano();

	// modifica relazione
	brano b3;

	scrivi_titolo_brano(&b3," bycicle race\0");
	scrivi_durata_brano(&b3, 300);
	scrivi_anno_brano(&b3, 1986);
	scrivi_ascolti_brano(&b3, 2500);

	aggiungi_brano(&b3);

	printf("\n\nbrani insweriti 2..\n");
	mostra_brani();

	// leggo l'id del brano aggiunto
	int id3 = leggi_id_brano(b3);

	// modifico una relazione
	scrivi_relazione_playlistBrano(&r2, id3, id_play);

	modifica_playlistBrano(r2);

	printf("stampa modifica...\n");

	stampa_playlist_brano();


	printf("elimino relazione 45...\n");
	elimina_playlistBrano(45);


	stampa_playlist_brano();




	return 0;
}
