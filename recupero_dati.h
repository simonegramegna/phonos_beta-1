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
void ripristina_generi();

// funzione per ripristinare le palylist di un utente
void ripristina_playlist_utente( int id_utente );

// funzione per ripristinare tutte le playlist di tutti gli utenti




#endif /* RECUPERO_DATI_H_ */
