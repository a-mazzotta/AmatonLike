 /*
 ============================================================================
 Name        : main.c
 Authors     : Alessandro, Alessia
 Version     : 1.0
 Description : Caso di studio G21 III luglio2021
 ============================================================================
 */

#include "Lib/librerie.h"
#include "Lib/login.h"
#include "Lib/home_account.h"

/*
 * All'inizio del programma vengono aperti i file utili all'esecuzione.
 * Se l'apertura dei file viene eseguita correttamente, viene chiamata la funzione login che permette l'accesso al programma e tramite l'user restituito dal login
 * il programma riesce ad acquisire il tipo dell'account.
 * In base al tipo di account, viene chiamata la procedura che permette di visualizzare il menu.
 */
int main() {
	int flag = 0, tipo = 0;
	char *user;
	flag = apri_files();
	if(flag == 0) { //se i file vengono aperti correttamente

		do {
			user = login();
			tipo = tipo_account(user);

			if(tipo == 1) {
				home_acquirente(user);
			} else if(tipo == 2) {
				home_esercente(user);
			} else if(tipo == 3) {
				home_corriere(user);
			} else {
				printf("\nErrore, tipo dell'account non valido!\n");
				system("pause");
				exit(0);// exit = esci del programma a causa di un errore
			}


		} while(flag == 0); //se l'utente decide di uscire dal menu account, torna alla fase di login

	} else {
		printf("File mancanti o corrotti\n\n");
		system("pause");
	}

	chiudi_files();

	return EXIT_SUCCESS;
}
