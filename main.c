#include <stdio.h>
#include <stdlib.h>

#include "interfaccia.h"
#include "gestione_album.h"
#include "recupero_dati.h"
#include "gestione_playlist.h"

int main()
{
	//interfaccia_principale();


	playlist p1, p2;

	scrivi_utente_playlist(&p1, 10);
	scrivi_nome_playlist(&p1, "ciao\0");
	scrivi_descrizione_playlist(&p1, "e' bella \0");
	scrivi_flag_pubblica_playlist(&p1, 1);

	scrivi_utente_playlist(&p2, 101);
	scrivi_nome_playlist(&p2, "hello\0");
	scrivi_descrizione_playlist(&p2, "e' bella \0");
	scrivi_flag_pubblica_playlist(&p2, 1);

	aggiungi_playlist(&p1);
	aggiungi_playlist(&p2);
	
	printf("playlist aggiunte \n");

	mostra_playlists();

	printf("playlist eliminate \n");

	//elimina_playlist(8);
	elimina_playlist(9);

	mostra_playlists();

	printf("playlist ripristinate.. \n");

	ripristina_playlist_utente(101);

	mostra_playlists();


	return 0;
}
