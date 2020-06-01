#ifndef RICERCA_H_
#define RICERCA_H_


/********************************************************
 * 
 *  Funzioni di ricerca per brani
 * 
********************************************************/

// funzione per cercare un brano per titolo
void ricerca_brani_per_titolo(char *titolo_cercato);

// funzione per cercare un brano per durata
void ricerca_brani_per_durata( int durata_cercata );

// funzione per verificare l'aèèartenenza della durata di un brano ad una classe di equivalenza (di durata)
int classe_durata_brano(int durata_cercata, int classe_durata);

/********************************************************
 * 
 *  Funzioni di ricerca per artisti
 * 
********************************************************/

// funzione per cercare un artista per nome
void ricerca_artisti_per_nome( char *nome_cercato );

#endif /* RICERCA_H_ */
