#ifndef GESTIONE_UTENTI_H_
#define GESTIONE_UTENTI_H_

#define DIMUSER 60
#define DIMPASS 60

typedef struct {
	int id;
	char username[DIMUSER];
	char password[DIMPASS];
	int admin;
	int eliminato;
} utente;

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_utente(utente utente_selezionato);
void leggi_username_utente(utente utente_selezionato, char *username_letto);
void leggi_password_utente(utente utente_selezionato, char *password_letta);
int leggi_admin_utente(utente utente_selezionato);
int leggi_flag_eliminato_utente(utente utente_selezionato);

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_utente(utente *utente_selezionato, int id);
void scrivi_username_utente(utente *utente_selezionato, char *username);
void scrivi_password_utente(utente *utente_selezionato, char *password);
void scrivi_admin_utente(utente *utente_selezionato, int admin);
void scrivi_flag_eliminato_utente(utente *utente_selezionato, int flag_eliminato);

/* -------------------------
	Funzioni su file
------------------------- */
int aggiungi_utente(utente *utente_selezionato);
void mostra_utenti();
void mostra_utente(utente utente_selezionato);
long posizione_utente(int id_utente);
int elimina_utente(int id_utente);
utente cerca_utente(int id_utente);
int modifica_utente(int id_utente, utente utente_modificato);
int inserisci_admin( utente* admin_inserito );
int controllo_presenza_utente(utente utente_selezionato);
int controllo_credenziali(char *username, char *password);

#endif /* GESTIONE_UTENTI_H_ */
