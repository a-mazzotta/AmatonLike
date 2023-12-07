/*
 * login.c
 *
 *  Created on: 9 giu 2021
 *
 * Libreria che contiene le funzioni e procedure utili all' inizio del programma e alla fase di login
 * authors: Alessandro, Alessia
 */

#include "librerie.h"
#include "struct.h"
#include "menu_design.h"
#include "input.h"
#include "login.h"

/*
 * Funzione che si occupa della fase di login e permette all'utente di scegliere se accedere o registra.
 * Nel caso l'utente scelga di accedere, il programma memorizzera' l'username con cui si e' effettuato l'accesso e lo restituira'.
 * Nel caso l'utente scelga di registrarsi, il programma acquisira' le informazioni utili alla registrazione e tornera' alla fase login.
 */
char* login() {
	int scelta = 0;
	char *user;
	do {
		menu_login(); //Stampera' 1) Accesso - 2) Registrazione
		scelta = input_int(); // l'utente inserisce la scelta

		if(scelta == 1) {
			user = accesso();
		} else if(scelta == 2) {
			registrazione();
		} else if(scelta == 3) {
			exit(0);
		}
	} while((scelta != 1 && scelta != 3) || (strcmp(user, "0") == 0)); //se l'utente decide di uscire dalla fase di accesso, user sara' uguale a 0
	return user; //ritorno dell' username
}

/*
 * Funzione che si occupa dell'accesso al programma, chiedendo in input all'utente username e password che verranno confrontati con quelli registrati.
 * Se l'accesso viene eseguito correttamente, la funzione restituira' l'username con cui si e' fatto l'accesso.
 */
char *accesso() {
	acquirente_t acquir = {0, ""}; //Per la lettura nel file degli acquirenti
	esercente_t eser = {0, ""}; //Per la lettura nel file degli esercenti
	corriere_t corr = {0, ""}; //Per la lettura nel file dei corrieri
	int scelta = 0, flag = 0; //Se l'accesso viene eseguito correttamente
	char *username = NULL, *password = NULL;
	username = malloc(sizeof(char)*STR); //alloca la memoria per la restituzione dell'user

	do {
		do {
			printf("\nInserire username\n"
					">> ");
			username = input_str();

			printf("\nInserire password (MAX. 5 caratteri, almeno una maiuscola ed un numero)\n"
					">> ");
			password = input_str();
		} while((strlen(username) == 0) || (strlen(password) == 0));

		//Leggi dal file acquirenti
		rewind(acquirenti);
		while(fread(&acquir, sizeof(acquirente_t), 1, acquirenti) == 1) {

			//Confronta
			if((strcmp(username, acquir.user) == 0)) { //se l'username e' giusto
				if(strcmp(password, acquir.psw) == 0) { //se la password e' giusta
					flag = 1;
				}
			}
		}

		if(flag == 1) {
			printf("\nAccesso effettuato con successo!\n");
			system("pause");
			system("cls");
		} else { //Se nel file acquirenti non sono stati trovati i dati inseriti
			//Leggi dal file esercenti
			rewind(esercenti);
			while(fread(&eser, sizeof(esercente_t), 1, esercenti) == 1) {

				//Confronta
				if((strcmp(username, eser.user) == 0)) { //se l'username e' giusto
					if(strcmp(password, eser.psw) == 0) { //se la password e' giusta
						flag = 1;
					}
				}
			}

			if(flag == 1) {
				printf("\nAccesso effettuato con successo!\n");
				system("pause");

			} else { //Se nel file esercenti non sono stati trovati i dati inseriti
				//Leggi dal file corrieri
				rewind(corrieri);
				while(fread(&corr, sizeof(corriere_t), 1, corrieri) == 1) {

					//Confronta
					if((strcmp(username, corr.user) == 0)) { //se l'username e' giusto
						if(strcmp(password, corr.psw) == 0) { //se la password e' giusto
							flag = 1;
						}
					}
				}


				if(flag == 0) {
					printf("\n\nUsername o password errati!\n");

					do {
						printf("\nVuoi uscire?\n"
								"[1] - Si\n"
								"[2] - No\n"
								">> ");
						scelta = input_int();

						if(scelta == 1) {
							strcpy(username, "0");
						}

						if(scelta != 1 && scelta != 2) {
							printf("\nScelta non valida!");
							system("pause");
						}

						system("cls");
					} while(scelta != 1 && scelta != 2);

				}
			}
		}
	} while(flag == 0 && scelta != 1); //Se non sono stati trovati i dati inseriti, vengono chiesti nuovamente a meno che l'utente non decide di uscire
	return username; // ritorna l'username che porteremo avanti nel codice per vedere quale utente ha fatto l'accesso
}

/*
 * Procedura che acquisisce i dati utili per la registrazione di un nuovo account nel programma.
 * L'utente dovra' prima scegliere che tipo di account registrare ed in base al tipo scelto, verranno chiesti determinati dati.
 */
void registrazione() {
	int scelta = 0, conferma = 0, flag = 0; //Scelta: per il tipo di account - Conferma: per la conferma della password - Flag: per il controllo dell'username
	char conferma_pass[LUNGHEZZA_PSW];
	acquirente_t acquir = {0, ""}; //Per la scrittura sul file acquirenti
	esercente_t eser = {0, ""}; //Per la scrittura sul file esercenti
	corriere_t corr = {0, ""}; //Per la scrittura sul file corrieri

	do {
		menu_account_registrazione(); //Stampa i possibili tipi di account
		scelta = input_int();

		if(scelta == 1) { //se viene scelto acquirente
			system("cls");

			acquir.tipo_acc = scelta; //tipo_account = acquirente(1)

			do {
				printf("Inserisci il tuo nome\n"
						">> ");
				strcpy(acquir.nome_acquirente, input_str());

			} while(controllo_num_string(acquir.nome_acquirente) != 0); //non possono esserci numeri nel nome


			do {
				printf("Inserisci il tuo cognome\n"
						">> ");
				strcpy(acquir.cognome_acquirente, input_str());
			} while(controllo_num_string(acquir.cognome_acquirente) != 0); //non possono esserci numeri nel cognome


			printf("\nInserisci il tuo indirizzo\n"
					">> ");
			strcpy(acquir.indirizzo_acquirente, input_str());

			printf("\nInserisci il tuo numero di telefono\n"
					">> ");
			strcpy(acquir.tel, input_tel()); //puo' avere solo numeri e deve essere lungo 10 numeri

			do {
				printf("\nInserisci il tuo username\n"
						">> ");
				strcpy(acquir.user, input_str()); //copia la stringa inserita all'interno della variabile

				flag = controllo_username(acquir.user); //confronta la variabile con quella presente nel file
				if(flag == 1) { //se l'username esiste gia'
					printf("\nUsername gia' esistente!\n");
					system("pause");
				}
			} while(flag == 1); // Finchè l'username inserito corrisponde ad uno esistente


			printf("\nInserisci la tua password (MAX. 5 caratteri, almeno una maiuscola ed un numero)\n"
					">> ");
			strcpy(acquir.psw, input_pass()); //Verrà copiata la stringa inserita all'interno della variabile


			do {

				printf("\nConferma password\n"
						">> ");
				strcpy(conferma_pass, input_pass());//Verrà copiata la stringa inserita all'interno della variabile

				if(strcmp (conferma_pass, acquir.psw) == 1) { //vengono confrontate le due password inserite
					printf("\nPassword errata!\n"
							"Riconfermare\n"
							">> ");

				} else {
					conferma = 1;
					printf("\nRegistrazione effettuata con successo!\n");
					system("pause");
				}
			} while(conferma == 0); //fin quando le due password non sono uguali

			//scrittura su file acquirenti
			fseek(acquirenti, 0, SEEK_END);
			fwrite(&acquir, sizeof(acquirente_t), 1, acquirenti);

		}else if(scelta == 2) { //se viene scelto esercente
			system("cls");

			eser.tipo_acc = scelta; //tipo_account = esercente(2)

			do {
				printf("\nInserisci il nome della tua azienza\n"
						">> ");
				strcpy(eser.nome_azienda, input_str());
			} while(controllo_num_string(eser.nome_azienda) != 0); //il nome dell'azienda non puo' contenere numeri

			do {
				printf("\nInserisci il codice della azienza\n"
						">> ");
				strcpy(eser.cod_azienda, input_str());
			} while(controllo_num_string(eser.cod_azienda) == 0); //il codice dell'azienda deve essere formato solo da numeri



			printf("\nInserisci l'indirizzo della azienza\n"
					">> ");
			strcpy(eser.indirizzo_sede, input_str());


			printf("\nInserisci il tuo numero di telefono\n"
					">> ");
			strcpy(eser.tel, input_tel()); //puo' avere solo numeri e deve essere lungo 10 numeri

			do {
				printf("\nInserisci il tuo username\n"
						">> ");
				strcpy(eser.user, input_str());

				flag = controllo_username(eser.user); //confronta la variabile con quella presente nel file
				if(flag == 1) { //se l'username esiste gia'
					printf("\nUsername gia' esistente!\n");
					system("pause");
				}
			} while(flag == 1); //finche' non inserisce un username univoco

			printf("\nInserisci la tua password (MAX. 5 caratteri, almeno una maiuscola ed un numero)\n"
					">> ");
			strcpy(eser.psw, input_pass());

			do {

				printf("\nConferma password\n"
						">> ");
				strcpy(conferma_pass, input_pass());

				if(strcmp (conferma_pass, eser.psw) == 1) { //confronta le due password
					printf("\nPassword errata!\n"
							"Riconfermare\n"
							">> ");

				} else {
					conferma = 1;

					printf("\nRegistrazione effettuata con successo!\n");
					system("pause");
				}
			} while(conferma == 0);

			//scrittura su file esercenti
			fseek(esercenti, 0, SEEK_END);
			fwrite(&eser, sizeof(esercente_t), 1, esercenti);

		} else if(scelta == 3){ //se viene scelto corriere
			system("cls");

			corr.tipo_acc = scelta; //tipo_account = corriere(3)

			do {
				printf("Inserisci il nome della tua azienza\n"
						">> ");
				strcpy(corr.nome_azienda, input_str());
			} while(controllo_num_string(corr.nome_azienda) != 0); //il nome dell'azienda non puo' contenere numeri


			do {
				printf("Inserisci il tuo nome\n"
						">> ");
				strcpy(corr.nome, input_str());
			} while(controllo_num_string(corr.nome) != 0); //il nome non puo' contenere numeri


			do {
				printf("\nInserisci il tuo cognome\n"
						">> ");
				strcpy(corr.cognome, input_str());
			} while(controllo_num_string(corr.cognome) != 0); //il cognome non puo' contenere numeri

			printf("\nInserisci il tuo numero di telefono\n"
					">> ");
			strcpy(corr.tel, input_tel()); //puo' avere solo numeri e deve essere lungo 10 numeri

			do {
				printf("\nInserisci il tuo username\n"
						">> ");
				strcpy(corr.user, input_str());

				flag = controllo_username(corr.user); //confronta la variabile con quella presente nel file
				if(flag == 1) { //se l'username esiste gia'
					printf("\nUsername gia' esistente!\n");
					system("pause");
				}
			} while(flag == 1); //Finchè non inserisce un username univoco

			printf("\nInserisci la tua password (MAX. 5 caratteri, almeno una maiuscola ed un numero)\n"
					">> ");
			strcpy(corr.psw, input_pass());

			do {

				printf("\nConferma password\n"
						">> ");
				strcpy(conferma_pass, input_pass());

				if(strcmp(conferma_pass, corr.psw) != 0) { //confronta le due password
					printf("\nPassword errata!\n"
							"Riconfermare\n"
							">> ");
				} else {
					conferma = 1;
					printf("\nRegistrazione effettuata con successo!\n");
					system("pause");
				}
			} while(conferma == 0);

			//scrittura su file corrieri
			fseek(corrieri, 0, SEEK_END);
			fwrite(&corr, sizeof(corriere_t), 1, corrieri);


		} else if(scelta == 4) { //se scegle di uscire
			break;
		}

	} while(scelta <= 0 || scelta >= 5); //fin quando non viene fatta una scelta valida
}

/*
 * Funzione che prende come parametro l'username con cui si e' effettuato l'acesso, ne ricava il tipo ritornandolo,
 * controllando in quale file si trova quell'username.
 * ritorna 1 se trova l'username nel file acquirenti,
 * 2 se trova l'username nel file esercenti,
 * 3 se trova l'username nel file corrieri.
 */
int tipo_account(char* user) {
	int tipo = 0, flag = 0;
	acquirente_t acquir = {0, ""}; //Per la lettura nel file acquirenti
	esercente_t eser = {0, ""}; //Per la lettura nel file esercenti
	corriere_t corr = {0, ""}; //Per la lettura nel file corrieri

	//Fin quando leggi da tutti i file utente
	rewind(acquirenti);
	rewind(esercenti);
	rewind(corrieri);
	while((fread(&acquir, sizeof(acquirente_t), 1, acquirenti) == 1) ||
			(fread(&eser, sizeof(esercente_t), 1, esercenti) == 1) ||
			(fread(&corr, sizeof(corriere_t), 1, corrieri) == 1)) {

		//compara l'username, se lo trova avvalora la variabile tipo
		if(strcmp(user, acquir.user) == 0 ) {
			flag = 1;
			tipo = acquir.tipo_acc;
			break;
		} else if(strcmp(user, eser.user) == 0) {
			flag = 1;
			tipo = eser.tipo_acc;
			break;
		} else if(strcmp(user, corr.user) == 0) {
			flag = 1;
			tipo = corr.tipo_acc;
			break;
		}
	}
	if(flag == 0) {
		printf("\nC'e' stato un errore con i dati dell'account'\n");
		system("pause");
	}
	return tipo;
}

/*
 * Funzione che apre tutti i file, in caso l'apertura ha successo, ritorna 1, se fallisce ritorna 0
 */
int apri_files() {
	int flag = 0;

	acquirenti = fopen("DatFiles/acquirenti.dat", "rb+");
	esercenti = fopen("DatFiles/esercenti.dat", "rb+");
	corrieri = fopen("DatFiles/corrieri.dat", "rb+");
	catalogo = fopen("DatFiles/catalogo.dat", "rb+" );
	acquisti = fopen("DatFiles/acquisti.dat", "rb+");

	if((acquirenti == NULL) || (esercenti == NULL) || (corrieri == NULL) || (catalogo == NULL) || (acquisti == NULL)) {
		flag = 1;
	} else {
		flag = 0;
	}

	return flag;
}

/*
 * Procedura che chiude tutti i file
 */
void chiudi_files() {
	fclose(acquirenti);
	fclose(esercenti);
	fclose(corrieri);
	fclose(catalogo);
	fclose(acquisti);
}


























