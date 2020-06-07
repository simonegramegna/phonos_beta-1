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

//funzione per mostrare l'interfaccia di inserimento album
void interfaccia_inserimento_album();

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

//funzione che permette all'utente di ricercare brani, artisti, generi ed album
void interfaccia_ricerca();

//funzione che permette di scegliere il tipo di ricerca da effettuare sui brani
void interfaccia_ricerca_brani();

//funzione che ricerca un brano per titolo
void interfaccia_ricerca_brano_per_titolo();

//funzione che ricerca un brano per anno di pubblicazione
void interfaccia_ricerca_brano_per_anno();

//funzione che ricerca un brano per durata approssimativa (in minuti)
void interfaccia_ricerca_brano_per_durata();

//funzione che permette di scegliere il tipo di ricerca da effettuare sugli artisti
void interfaccia_ricerca_artisti();

//funzione che ricerca un artista per nome
void interfaccia_ricerca_artista_per_nome();

//funzione che ricerca un artista per nome d'arte
void interfaccia_ricerca_artista_per_nome_arte();

//funzione che permette di scegliere il tipo di ricerca da effettuare sulle playlists
void interfaccia_ricerca_playlist();

//funzione che permette di scegliere il tipo di ricerca da effettuare sugli album
void interfaccia_ricerca_album();

//funzione che ricerca un album per titolo
void interfaccia_ricerca_album_per_titolo();

//funzione che ricerca un album per anno di pubblicazione
void interfaccia_ricerca_album_per_anno();

//funzione che mostra l'interfaccia per effettuare il backup
void interfaccia_backup();

//funzione che mostra l'esito del backup dei brani
void interfaccia_backup_brani();

//funzione che mostra l'esito del backup degli artisti
void interfaccia_backup_artisti();

//funzione che mostra l'esito del backup delle playlist
void interfaccia_backup_playlist();

//funzione che mostra l'esito del backup degli album
void interfaccia_backup_album();

//funzione che mostra l'interfaccia per effettuare il ripristino dei dati
void interfaccia_ripristino();

//funzione che mostra l'esito del ripristino dei brani
void interfaccia_ripristino_brani();

//funzione che mostra l'esito del ripristino degli artisti
void interfaccia_ripristino_artisti();

//funzione che mostra l'esito del ripristino delle playlist
void interfaccia_ripristino_playlist();

//funzione che mostra l'esito del ripristino degli album
void interfaccia_ripristino_album();

#endif /* INTERFACCIA_H_ */
