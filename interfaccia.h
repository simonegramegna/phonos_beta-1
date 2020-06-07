#ifndef INTERFACCIA_H_
#define INTERFACCIA_H_

// funzione per leggere da tastiera un valore intero
void leggere_intero( int *valore );

// funzione per leggere da tastiera una stringa di lunghezza qualsiasi
void leggere_stringa( char *stringa );

// funzione per pulire lo schermo 
void pulisci_schermo();

// funzione per mostrare il logo del software
void logo();

// funzione per mostrare l'header del menu' principale
void titolo();

// funzione per ritornare al menu' principale
void replay();

// funzione per mostrare il menu' principale
void interfaccia_principale();

// funzione per mostrare l'interfaccia di inserimento di un brano
void interfaccia_inserimento_brano();

// funzione per mostrare l'interfaccia di inserimento di un artista
void interfaccia_inserimento_artista();

// funzione per mostrare l'interfaccia di inserimento di un genere
void interfaccia_inserimento_genere();

// funzione per mostrare l'interfaccia di inserimento playlist
void interfaccia_inserimento_playlist();

// funzione per mostrare l'interfaccia di registrazione
void interfaccia_registrazione();

// funzione per mostrare l'interfaccia di login
void interfaccia_login();

//funzione per mostrare il menu iniziale degli utenti non admin
void interfaccia_utente();

//funzione per mostrare il menu iniziale degli admin
void interfaccia_admin();

//funzione che permette all'utente di scegliere se accedere o registrarsi
void interfaccia_iniziale();


void interfaccia_ricerca();

void interfaccia_ricerca_brani();
void interfaccia_ricerca_brano_per_titolo();
void interfaccia_ricerca_brano_per_anno();
void interfaccia_ricerca_brano_per_durata();

void interfaccia_ricerca_artisti();
void interfaccia_ricerca_artista_per_nome();
void interfaccia_ricerca_artista_per_nome_arte();

void interfaccia_ricerca_playlist();

void interfaccia_ricerca_album();
void interfaccia_ricerca_album_per_titolo();
void interfaccia_ricerca_album_per_anno();

#endif /* INTERFACCIA_H_ */
