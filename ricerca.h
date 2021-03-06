#ifndef RICERCA_H_
#define RICERCA_H_

#include "gestione_relazioni.h"

/********************************************************
 * 
 *  Funzioni di controllo per le ricerche
 * 
********************************************************/

// funzione per il controllo di validita' di un anno inserito
int controllo_anno( int anno_inserito );

// funzione per verificare l'aèèartenenza della durata di un brano ad una classe di equivalenza (di durata)
int classe_durata_brano(int durata_cercata, int classe_durata);


/********************************************************
 * 
 *  Funzioni di ricerca per brani
 * 
********************************************************/

// funzione per cercare un brano per titolo
void ricerca_brani_titolo(char *titolo_cercato);

// funzione per cercare un brano per durata
void ricerca_brani_durata( int durata_cercata );

// funzione per ceercare brani in base ad un determinato anno
void ricerca_brani_anno( int anno_cercato );

/********************************************************
 * 
 *  Funzioni di ricerca per artisti
 * 
********************************************************/

// funzione per cercare un artista per nome
void ricerca_artisti_nome( char *nome_cercato );

// funzione per cercare un artista per noe d'arte
void ricerca_artisti_nome_arte( char *nome_arte_cerca );

/********************************************************
 * 
 *  Funzioni di ricerca per album
 * 
********************************************************/

// funzione di ricerca per titolo di album
void ricerca_album_titolo( char *titolo_cercato );

// funzione di ricerca per anno di album
void ricerca_album_anno( int anno_cercato );

/********************************************************
 * 
 *  Funzioni di ricerca per genere
 * 
********************************************************/

// funzione di ricerca di un genere per titolo
void ricerca_genere_nome( char *nome_genere_cercato );

/********************************************************
 * 
 *  Funzioni di ricerca per playlist
 * 
 ********************************************************/

// funzione per ricercare per nome una playlist
void ricerca_playlist_nome( char* nome_cercato, int id_utente_cercato );

// funzione per cercare per nome una playlist nelle playlist pubbliche
void ricerca_playlist_pubbliche_nome( char* nome_cercato );

// funzione per cercare le playlist pubbliche
void ricerca_playlist_pubbliche();


/********************************************************
 *
 *  Funzioni di ricerca per le relazioni
 *
 ********************************************************/

//funzione che cerca la relazione branoArtista associata ad un brano
brano_artista cerca_relazione_branoArtista( int id_brano );

//funzione che cerca la relazione branoAlbum associata ad un brano
brano_album cerca_relazione_branoAlbum( int id_brano );

//funzione che cerca la relazione branoGenere associata ad un brano
brano_genere cerca_relazione_branoGenere( int id_brano );

// funzione che conta il numero di voltec che compare un brano in una playlist
int conta_brani_playlist( int id_brano );

#endif /* RICERCA_H_ */
