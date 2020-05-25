#ifndef GESTIONE_RELAZIONI_H_
#define GESTIONE_RELAZIONI_H_

#include "gestione_brani.h"
#include "gestione_album.h"
#include "gestione_generi.h"
#include "gestione_artisti.h"
#include "gestione_playlist.h"

// definisco tipo di dato branoAlbum
typedef struct{

    int id_brano_album;
    int id_album;
    int id_brano;
    int flag_brano_album;

}brano_album;


// definisco tipo di dato branoArtista
typedef struct{

    int id_brano_artista;
    int id_brano;
    int id_artista;
    int flag_brano_artista;

}brano_artista;


/*********************************************
 * 
 * Funzioni BranoAlbum
 * 
 *********************************************/

/*
 * Operazioni su campi brano_album
*/

// funzione per leggere l'id del branoalbum
int leggi_id_branoAlbum( brano_album relazione_letta );

// funzione per scrivere l'id del branoalbum
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


/*********************************************
 * 
 * Funzioni BranoArtista
 * 
 *********************************************/

/*
 * Operazioni su campi brano_artista
*/

// funzione per leggere l'id del brano_artista
int leggi_id_branoArtista( brano_artista relazione_letta );

// funzione per scrivere l'id del brano_artista
void scrivi_id_branoArtista( brano_artista* relazione_scritta, int id_assegnato );

// funzione per leggere l'id del brano contenuto nella relazione brano_artista
int id_brano_branoArtista( brano_artista relazione_letta );

// funzione per leggere l'id dell'artista nella relazione brano_artista
int id_artista_branoArtista( brano_artista relazione_letta );

// funzione per scrivere una relazione brano_artista
void scrivi_relazione_branoArtista( brano_artista* relazione_scritta, brano brano_letto, artista artista_appartenenza );

// funzione per leggere il flag del brano artista
int leggi_flag_branoArtista( brano_artista relazione_letta );

// funzione per scrivere il flag del brano_artista
void scrivi_flag_branoArtista( brano_artista* relazione_scritta, int flag_relazione );

/**
 * Operazioni su file per brano_artista
*/

// funzione per aggiungere una relazione branoArtista
int aggiungi_branoArtista( brano_artista* relazione_inserita );

// funzione per cercare la posizione nella tabella di un record branoArtista con un determinato id
long posizione_branoArtista( int id_branoArtista );

// funzione per eliminare un record branoArtista
int elimina_branoArtista( int id_branoArtista );

// funzione per leggere un branoArtista con determinato identificativo
brano_artista cerca_branoArtista( int id_branoArtista );

// funzione per modificare una relazione brano_artista
int modifica_branoArtista( brano_artista relazione_modificata );

// test stampa relazioni
void stampa_brano_artista();

/*********************************************
 * 
 * Funzioni BranoGenere
 * 
 *********************************************/



#endif /* GESTIONE_RELAZIONI_H_ */
