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

// definisco tipo di dato branoGenere
typedef struct{

    int id_branoGenere;
    int id_brano;
    int id_genere;
    int flag_brano_genere;

}brano_genere;

// definisco tipo di dato playlistBrano
typedef struct{

    int id_playlistBrano;
    int id_playlist;
    int id_brano;
    int flag_playlist_brano;

}playlist_brano;


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

// funzione per scrivere la relazione branoalbum
void scrivi_relazione_branoAlbum( brano_album* relazione_scritta, brano brano_letto, album album_appartenenza );

// funzione per leggere il flag di eliminazione di un branoAlbum
int leggi_flag_branoAlbum( brano_album relazione_letta );

// funzione per scrivere il flag di un brano album in base ad album e brano in input
void scrivi_flag_branoAlbum( brano_album* relazione_scritta, int flag_relazione );

/*
 * Operazioni su file per brano_album
*/

// funzione per aggiungere alla tabella una relazione branoAlbum 
int aggiungi_branoAlbum( brano_album* relazione_inserita );

// funzione per cercare la posizione di un branoAlbum con determinato id
long posizione_branoAlbum( int id_branoAlbum );

// funzione per eliminare un branoAlbum
int elimina_branoAlbum( int id_branoAlbum );

// funzione per leggere una branoAlbum con un determinato identificativo
brano_album cerca_branoAlbum( int id_branoAlbum );

// funzione per modificare nella tabella un branoAlbum 
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


/*********************************************
 * 
 * Funzioni BranoGenere
 * 
 *********************************************/

/*
 * Operazioni su campi brano_genere 
*/

// funzione per leggere l'id del branogenere
int leggi_id_branoGenere( brano_genere relazione_letta );

// funzione per scrivere l'id del branogenere
void scrivi_id_branoGenere( brano_genere* relazione_scritta, int id_assegnato );

// funzione per leggere l'id del brano contenuto in branogenere
int id_brano_branoGenere( brano_genere relazione_letta );

// funzione per leggere l'id del genere contenuto in branogenere
int id_genere_branoGenere( brano_genere relazione_letta );

// funzione per scrivere la relazione branogenere
void scrivi_relazione_branoGenere( brano_genere* relazione_scritta, brano brano_letto, genere genere_appartenenza );

// funzione per leggere il flag di eliminazione di un branogenere
int leggi_flag_branoGenere( brano_genere relazione_letta );

// funzione per scrivere il flag di eliminazione di un branogenere
void scrivi_flag_branoGenere( brano_genere* relazione_scritta, int flag_relazione );

/*
 * Operazioni su file per brano_genere
*/

// funzione per aggiungere alla tabella una relazione branoGenere
int aggiungi_branoGenere( brano_genere* relazione_inserita );

// funzione per cercare la posizione di un record branoGenere con determinato id
long posizione_branoGenere( int id_branoGenere );

// funzione per eliminare una relazione branoGenere
int elimina_branoGenere( int id_branoGenere );

// funzione per leggere un brenoGenere con determinato id
brano_genere cerca_branoGenere( int id_branoGenere );

// funzione per modificare nella tabella un branoGenere
int modifica_branoGenere( brano_genere relazione_modificata );


/*********************************************
 * 
 * Funzioni PlaylistBrano
 * 
 *********************************************/

/*
 * Operazioni su campi playlist_brano 
*/

// funzione per leggere l'id della relazione playlistBrano
int leggi_id_playlistBrano( playlist_brano relazione_letta );

// funzione per scrivere l'id della relazione playlistBrano
void scrivi_id_playlistBrano( playlist_brano* relazione_scritta, int id_assegnato );

// funzione per leggere l'id della playlist contenuto in playlistBrano
int id_playlist_playlistBrano( playlist_brano relazione_letta );

// funzione per leggere l'id del brano in playlistBrano
int id_brano_playlistBrano( playlist_brano relazione_letta );

// funzione per scrivere una relazione playlistBrano
void scrivi_relazione_playlistBrano( playlist_brano* relazione_scritta, brano brano_letto, playlist playlist_appartenenza );

// funzione per leggere il flag di eliminazione della relazione playlistBrano
int leggi_flag_playlistBrano( playlist_brano relazione_letta );

// funzione per scrivere il flag di eliminazione della relazione playlistBrano
void scrivi_flag_playlistBrano( playlist_brano* relazione_scritta, int flag_relazione );

/*
 * Operazioni su file 
*/

// funzione per aggiungere alla tabella una relazione playlistBrano
int aggiungi_playlistBrano( playlist_brano* relazione_aggiunta );

// funzione per cercare la posizione di un record playlistBrano con un determinato id
long posizione_playlistBrano( int id_playlistBrano );

// funzione per eliminare una relazione playlistBrano con determinato id
int elimina_playlistBrano( int id_playlistBrano );

// funzione per leggere una relazione playlistBrano con determinato id
playlist_brano cerca_playlistBrano( int id_playlistBrano );

// funzione per modificare una relazione playlistBrano
int modifica_playlistBrano( playlist_brano relazione_modificata );

// funzione di test per la stampa
void stampa_playlist_brano();

#endif /* GESTIONE_RELAZIONI_H_ */
