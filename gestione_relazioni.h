#ifndef GESTIONE_RELAZIONI_H_
#define GESTIONE_RELAZIONI_H_

#include "gestione_brani.h"
#include "gestione_album.h"
#include "gestione_generi.h"
#include "gestione_artisti.h"

// definisco tipo di dato branoAlbum
typedef struct{

    int id_brano_album;
    int id_album;
    int id_brano;
    int flag_brano_album;

}brano_album;

/*
 * Operazioni su campi brano_album
*/

// funzione per leggere l'id del brano contenuto in branoalbum
int leggi_id_branoAlbum( brano_album relazione_letta );

// funzione per scrivere l'identificativo del branoalbum
void scrivi_id_branoAlbum( brano_album* relazione_scritta, int id_assegnato );

// funzione per leggere l'id dell'album contenuto in branoalbum
int id_album_branoAlbum( brano_album relazione_letta );

// funzione per leggere l'id del brano contenuto in branoAlbum
int id_brano_branoAlbum( brano_album relazione_letta );

// funnzione per scrivere l'id dell'album contenuto nel branoAlbum
void scrivi_relazione_branoAlbum( brano_album* relazione_scritta, brano brano_letto, album album_appartenenza );

// funzione per leggere il flag di eliminazione di un branoAlbum
int leggi_flag_branoAlbum( brano_album relazione_letta );

// funzione per scrivere il flag di un brano album in base ad album e brano in input
void scrivi_flag_branoAlbum( brano_album* relazione_scritta, int flag_relazione );

/**
 * Operazioni su file per brano_album
*/

// funzione per aggiungere una relazione branoAlbum 
int aggiungi_branoAlbum( brano_album* relazione_inserita );

// funzione per cercare la posizione di un branoAlbum con determinato id
long posizione_branoAlbum( int id_branoAlbum );

// funzione per eliminare un brano album
int elimina_branoAlbum( int id_branoAlbum );

// funzione per leggere una branoAlbum con un determinato identificativo
brano_album cerca_branoAlbum( int id_branoAlbum );

// funzione per modificare un branoAlbum con un determinato identificativo
int modifica_branoAlbum( brano_album relazione_modificata );


// funzione di test per stampare tutti i recor
void stampa_relazioni();


#endif /* GESTIONE_RELAZIONI_H_ */
