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

#endif /* INTERFACCIA_H_ */
