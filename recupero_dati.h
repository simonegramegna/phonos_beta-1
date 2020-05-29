#ifndef RECUPERO_DATI_H_
#define RECUPERO_DATI_H_

/*
 * Funzione di ripristino dei dati nella tabella 
*/

// funzione per ripristinare i brani nella tabella
int ripristina_brani();

// funzione per ripristinare gli artisti nella tabella
int ripristina_artisti();

// funzione per ripristinare gli album nella tabella
int ripristina_album();

// funzione per ripristinare i generi nella tabella
int ripristina_generi();

// funzione per ripristinare le palylist di un utente
int ripristina_playlist_utente( int id_utente );

// funzione per ripristinare tutte le playlist di tutti gli utenti
int ripristina_playlist();

/*
 * Funzioni ripristino dati relazioni  
*/

// fuznione per ripristinare tutte le relazioni "brano_album"
int ripristina_tabella_branoAlbum();

// funzione per ripristinare tutte le relazioni "brano_album"
int ripristina_tabella_branoArtista();

// funzione per ripristinare tutte le relazioni "brano_genere"
int ripristina_tabella_branoGenere();

// funzione per ripristinare tutte le relazioni "playlist_brano"
int ripristina_tabella_playlistBrano();


/**************************************
 * 
 *  Funzioni backup dati
 * 
 *************************************/

// funzione per eseguire il backup della tabella brani
int backup_brani();

// funzione per eseguire il backup della tabella artisti
int backup_artisti();

// funzione per eseguire il backup della tabella album
int backup_album();

// funzione per eseguire il backup della tabella generi
int backup_generi();

// funzione per eseguire il backup della tabella playlist
int backup_playlist();

// funzione per stampare il file di backup
void stampa_backup_brani();

#endif /* RECUPERO_DATI_H_ */
