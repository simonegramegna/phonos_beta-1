#ifndef GESTIONE_UTENTI_H_
#define GESTIONE_UTENTI_H_

// definisco dimensione massima di un utente 
#define DIMUSER 60

// definisco dimesione massima di una password
#define DIMPASS 60

// definisco tipo di dato utente
typedef struct{
	
	int id;
	char username[DIMUSER];
	char password[DIMPASS];
	int admin;
	int eliminato;

}utente;

/* -------------------------
	Funzioni di lettura
------------------------- */

// funzione per leggere l'id di un utente 
int leggi_id_utente( utente utente_selezionato );

// funzione per leggere l'username di un utente
void leggi_username_utente( utente utente_selezionato, char *username_letto );

// funzione per leggere la password di un utente
void leggi_password_utente( utente utente_selezionato, char *password_letta );

// funzione per leggere il flag 'admin' di un utente
int leggi_admin_utente(utente utente_selezionato);

// funzione per leggere il flag di eliminazione di un utente
int leggi_flag_eliminato_utente(utente utente_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */

// funzione per scrivere l'id di un utente 
void scrivi_id_utente( utente *utente_selezionato, int id );

// funzione per scrivere l'username di un utente
void scrivi_username_utente( utente *utente_selezionato, char *username );

// funzione per scrivere la password di un utente 
void scrivi_password_utente( utente *utente_selezionato, char *password );
 
// funzione per scrivere il campo 'admin' di un utente
void scrivi_admin_utente( utente *utente_selezionato, int admin );

// funzione per scrivere il flag di eliminazione di un utente
void scrivi_flag_eliminato_utente( utente *utente_selezionato, int flag_eliminato );

/* -------------------------
	Funzioni su file
------------------------- */

// funzione per aggiungere un utente nella tabella
int aggiungi_utente( utente *utente_selezionato );

// funzione per mostrare tutti gli utenti
void mostra_utenti();

// funzione per mostrare un determinato utente
void mostra_utente( utente utente_selezionato );

// funzione per cercare la posizione di un utente
long posizione_utente( int id_utente );

// funzione per eliminare un utente per id
int elimina_utente( int id_utente );

// funzione per leggere un utente per id
utente cerca_utente( int id_utente );

// fuznione per modificare un utente
int modifica_utente( utente utente_modificato );

// funzione per inserire un admin
int inserisci_admin( utente* admin_inserito );

// funzione per il controllo della presenza di un utente
int controllo_presenza_utente(utente utente_selezionato);

// funzione per il controllo credenziali di un utente
int controllo_credenziali( char *username, char *password );

// funzione per autenticare un utente 
void autentica( utente utente_autenticato );

// funzione per leggere l'utente corrente
utente leggi_utente_corrente();

//funzione che verifica se un determinato unsername è già stato preso
int username_esiste(char *username);

#endif /* GESTIONE_UTENTI_H_ */
