#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_utenti.h"
#include "genera_id.h"

/* -------------------------
	Funzioni di lettura
------------------------- */
int leggi_id_utente( utente utente_selezionato )
{
	return utente_selezionato.id;
}

void leggi_username_utente( utente utente_selezionato, char *username_letto )
{
	strcpy(username_letto, utente_selezionato.username);
}

void leggi_password_utente( utente utente_selezionato, char *password_letta )
{
	strcpy(password_letta, utente_selezionato.password);
}

int leggi_admin_utente( utente utente_selezionato )
{
	return utente_selezionato.admin;
}

int leggi_flag_eliminato_utente( utente utente_selezionato) 
{
	return utente_selezionato.eliminato;
}

/* -------------------------
	Funzioni di scrittura
------------------------- */
void scrivi_id_utente( utente *utente_selezionato, int id )
{
	utente_selezionato->id = id;
}

void scrivi_username_utente( utente *utente_selezionato, char *username )
{
    strcpy(utente_selezionato->username, username);
}

void scrivi_password_utente( utente *utente_selezionato, char *password ) 
{
    strcpy(utente_selezionato->password, password);
}

void scrivi_admin_utente( utente *utente_selezionato, int admin )
{
	utente_selezionato->admin = admin;
}

void scrivi_flag_eliminato_utente( utente *utente_selezionato, int flag_eliminato )
{
	utente_selezionato->eliminato = flag_eliminato;
}

/* -------------------------
	Funzioni su file
------------------------- */

int aggiungi_utente(utente *utente_selezionato)
{
	FILE *tabella_utenti;
	int aggiunto;

	tabella_utenti = fopen("utenti.dat", "ab");
	aggiunto = 0;

	if(tabella_utenti != NULL)
	{
		scrivi_id_utente(utente_selezionato, genera_id());
		scrivi_admin_utente(utente_selezionato, 0);
		scrivi_flag_eliminato_utente(utente_selezionato, 0);

		fwrite(utente_selezionato, sizeof(utente), 1, tabella_utenti);
		aggiunto = 1;
	}
	fclose(tabella_utenti);

	return aggiunto;
}

void mostra_utenti()
{
	utente utente_corrente;
	FILE *tabella_utenti;

	tabella_utenti = fopen("utenti.dat", "rb");

	if(tabella_utenti != NULL)
	{
		while( fread(&utente_corrente, sizeof(utente), 1, tabella_utenti) )
		{
			mostra_utente(utente_corrente);
		}
	}
	fclose(tabella_utenti);
}

void mostra_utente( utente utente_selezionato )
{
	if( utente_selezionato.eliminato != 1 )
	{
		printf("ID: %d				\n", utente_selezionato.id);
		printf("Username: %s		\n", utente_selezionato.username);
		printf("Eliminato: %d		\n", utente_selezionato.eliminato);
		printf("Admin: %d			\n", utente_selezionato.admin);
	}
	printf("\n");
}
long posizione_utente( int id_utente )
{
	FILE *tabella_utenti;
    long posizione;
    
   	tabella_utenti = fopen("utenti.dat", "rb");
    posizione = -1;
   
	if( tabella_utenti != NULL )
	{
		utente utente_corrente;

        while(!feof(tabella_utenti) && posizione == -1)
		{
			int id_corrente;

            fread(&utente_corrente, sizeof(utente), 1, tabella_utenti);
            id_corrente = leggi_id_utente(utente_corrente);

            if( id_corrente == id_utente )
			{
                posizione = ftell(tabella_utenti) - sizeof(utente); // perche' la ftell restituisce blocco successivo
            }
        }
    }
	fclose(tabella_utenti);

    return posizione;
}

int elimina_utente( int id_utente )
{
	FILE *tabella_utenti;
	int eliminato;
	
	tabella_utenti = fopen("utenti.dat", "rb+");
	eliminato = 0;

	if( tabella_utenti != NULL )
	{
		long posizione;
		utente utente_trovato;

		posizione = posizione_utente(id_utente);
		utente_trovato = cerca_utente(id_utente);
		scrivi_flag_eliminato_utente(&utente_trovato, 1);

		fseek(tabella_utenti, posizione, SEEK_SET);
		fwrite(&utente_trovato, sizeof(utente), 1, tabella_utenti);
		eliminato = 1;
	}
	fclose(tabella_utenti);

	return eliminato;
}

utente cerca_utente(int id_utente)
{
	utente utente_trovato;
	FILE *tabella_utenti;
	
	tabella_utenti = fopen("utenti.dat", "rb");

	if( tabella_utenti != NULL )
	{
		long posizione;
		posizione = posizione_utente(id_utente);

		if(posizione != -1)
		{
			fseek(tabella_utenti, posizione, SEEK_SET);
			fread(&utente_trovato, sizeof(utente), 1, tabella_utenti);
		} 
		else 
		{
			printf("utente non trovato \n");
		}
	}
	fclose(tabella_utenti);

	return utente_trovato;
}

int modifica_utente( utente utente_modificato )
{
	FILE *tabella_utenti;
	int modificato;
	
	tabella_utenti = fopen("utenti.dat", "rb+");
	modificato = 0;

	if(tabella_utenti != NULL)
	{
		long posizione;
		int id_utente;

		id_utente = leggi_id_utente(utente_modificato);
		posizione = posizione_utente(id_utente);
		
		fseek(tabella_utenti, posizione, SEEK_SET);
		fwrite(&utente_modificato, sizeof(utente), 1, tabella_utenti);
		modificato = 1;
	}
	fclose(tabella_utenti);

	return modificato;
}

int controllo_presenza_utente(utente utente_selezionato)
{
	int controllo = 0;

	FILE* tabella_utenti = fopen("utenti.dat","rb");

	if( tabella_utenti != NULL )
	{
		char username_utente[DIMUSER];

		leggi_username_utente(utente_selezionato, username_utente );

		while( !feof(tabella_utenti) && controllo == 0 )
		{
			utente utente_confronto;
			char username_confronto[DIMUSER];

			fread(&utente_confronto, sizeof(utente),1, tabella_utenti);

			leggi_username_utente(utente_confronto, username_confronto);

			if( strcmp(username_utente, username_confronto) == 0 )
			{
				controllo = 1;
			}
		}
	}
	fclose(tabella_utenti);

	return controllo;
}

int inserisci_admin( utente* admin_inserito )
{
	FILE *tabella_utenti;
	int aggiunto;
	
	tabella_utenti = fopen("utenti.dat", "ab");
	aggiunto = 0;

	if(tabella_utenti != NULL)
	{
		scrivi_id_utente( admin_inserito, genera_id() );
		scrivi_admin_utente( admin_inserito, 1 );
		scrivi_flag_eliminato_utente( admin_inserito, 0 );

		fwrite(admin_inserito, sizeof(utente), 1, tabella_utenti);
		aggiunto = 1;
	}
	fclose(tabella_utenti);

	return aggiunto;
}

int controllo_credenziali( char *username, char *password ) 
{
	FILE *tabella_utenti;
	int autenticato; 

	tabella_utenti = fopen("utenti.dat", "rb");
	autenticato = 0;

	if(tabella_utenti != NULL)
	{
		while( !feof(tabella_utenti) )
		{
			utente utente_confronto;
			char username_confronto[DIMUSER];
			char password_confronto[DIMPASS];

			fread(&utente_confronto, sizeof(utente), 1, tabella_utenti);
			leggi_username_utente(utente_confronto, username_confronto);
			leggi_password_utente(utente_confronto, password_confronto);

			if( strcmp(username_confronto, username) == 0 && strcmp(password_confronto, password) == 0 )
			{
				autentica(utente_confronto);
				autenticato = 1;
			}
		}
	}
	fclose(tabella_utenti);

	return autenticato;
}

void autentica( utente utente_autenticato )
{
	FILE *file_autenticazione;
	file_autenticazione = fopen("autenticazione.dat", "rb+");

	if(file_autenticazione != NULL)
	{
		fwrite(&utente_autenticato, sizeof(utente), 1, file_autenticazione);
	}

	fclose(file_autenticazione);
}

utente leggi_utente_corrente()
{
	utente utente_autenticato;
	FILE *file_autenticazione;

	file_autenticazione = fopen("autenticazione.dat", "rb");

	if(file_autenticazione != NULL)
	{
		fread(&utente_autenticato, sizeof(utente), 1, file_autenticazione);
	}

	fclose(file_autenticazione);

	return utente_autenticato;
}
