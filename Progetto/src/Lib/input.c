/*
 * file input.c
 *
 *  Created on: 9 giu 2021
 *
 *  Libreria che si occupa degli iserimenti in input e dei controlli degli inserimenti
 *  e l'incremento degli id per quanto riguarda i prodotti
 *  authors: Alessandro, Alessia
 */
#include "librerie.h"
#include "constants.h"
#include "struct.h"
#include "home_account.h"

/*
 * Funzione che si occupa dell'inserimento di interi con programmazione difensiva nel caso non viene inserito un intero.
 *
 */
int input_int() {
	int intero = 0;

	while(scanf("%d", &intero) == 0) {
		printf("Inserimento non valido!\n"
				">> ");

		while(getchar() != '\n');
	}
	return intero;
}

/*
 * Funzione che si occupa dell'inserimento di float con programmazione difensiva nel caso non viene inserito un float.
 * Ritorna il float inserito.
 */
float input_float() {
	float decimale = 0;

	while(scanf("%f", &decimale) == 0) {
		printf("Inserimento non valido!\n"
				">> ");

		while(getchar() != '\n');
	}
	return decimale;
}

/*
 * Funzione che si occupa dell'inserimento di stringhe con programmazione difensiva nel caso non viene inserita una stringa
 * o la stringa inserita e' vuota.
 * Ritorna la stringa.
 */
char *input_str() {
	char *stringa;
	stringa = malloc(sizeof(char)*STR);

	do {
		fflush(stdin);
		gets(stringa);

		if(strlen(stringa) > STR) {
			printf("Inserimento non valido!\n"
					"Riprovare\n"
					">> ");
		}

		if(isspace(stringa[0]) != 0) {   //stringa[0] se vede che il primo carattere e' uno spazio da errore
			printf("Inserimento non valido!\n"
					"Riprovare\n"
					">> ");
		}

		if(strlen(stringa) == 0) { //se vede che non c'e' stato un inserimento, da errore
			printf("\nL'inserimento non puo' essere vuoto!\n"
					"Riprovare\n"
					">> ");
		}

	} while((strlen(stringa) > STR) || (isspace(stringa[0]) != 0) || (strlen(stringa) == 0));

	return stringa;
}

/*
 * Funzione che si occupa dell'inserimento del numero di telefono con programmazione difensiva nel caso
 * il numero inserito non e' lungo 10 numeri o nel caso non ci sono numeri.
 * Ritorna il numero di telefono.
 */
char *input_tel() {
	int i = 0, flag = 0;
	char *tel;
	tel = malloc(sizeof(char)*LUNGHEZZA_TEL);

	do {
		flag = 0;
		fflush(stdin);
		gets(tel);

		if(strlen(tel) > LUNGHEZZA_TEL || strlen(tel) < LUNGHEZZA_TEL) {
			printf("\nInserimento non valido!\n"
					"Riprovare\n"
					">> ");
		} else {
			for(i = 0; i< LUNGHEZZA_TEL; i++) {
				if(isdigit(tel[i]) == 0) {
					flag = 1;
				}
				if(flag == 1) {
					printf("Inserimento non valido!\n""Riprovare\n"
							">> ");

				}
			}
		}
	} while(strlen(tel) > LUNGHEZZA_TEL || strlen(tel) < LUNGHEZZA_TEL || flag == 1);

	return tel;
}

/*
 * Funzione che si occupa dell'inserimento della password con programmazione difensiva nel caso
 * la password e' piu' lunga di 5 caratteri e non contiene una maiuscola ed un numero.
 * Restituisce la password
 */
char *input_pass() {
	int numero = 0, maiuscola = 0, i = 0;
	char *pass;

	pass = malloc(sizeof(char)*LUNGHEZZA_PSW);

	do {
		maiuscola = 0;
		numero = 0;

		fflush(stdin);
		gets(pass);

		if(strlen(pass) > LUNGHEZZA_PSW) {
			printf("\nInserire una password valida!\n"
					">> ");
		} else {
			for(i = 0; i <= LUNGHEZZA_PSW; i++) {
				if(isdigit(pass[i]) != 0) {
					numero = 1;
				}
				if(isupper(pass[i]) != 0) {
					maiuscola = 1;
				}
			}
			if(numero == 0 || maiuscola == 0) {
				printf("\nInserire una password valida!\n"
						">> ");
			}
		}
	} while((strlen(pass) > LUNGHEZZA_PSW) || (numero == 0) || (maiuscola == 0));

	return pass;
}

/*
 * Funzione che controlla se la stringa presa come parametro contiene numeri.
 * ritorna 1 nel caso ci sono numeri o 0 se non ci sono.
 */
int controllo_num_string(char* stringa) {

	int flag = 0, lunghezza = 0, i = 0;

	lunghezza= strlen(stringa);


	for(i=0; i<lunghezza; i++) {

		if(isdigit(stringa[i]) != 0) {
			flag = 1;
		}
	}
	return flag;
}

/*
 * Funzione che legge nei file utente, se trova l'username preso come parametro, all'interno di un file,
 * allora l'username e' gia' esistente.
 * ritorna 0 se l'username non esista gia', 1 se l'username esiste gia'.
 */
int controllo_username(char *input) {
	int flag = 0;
	acquirente_t acquir = {0, ""};
	esercente_t eser = {0, ""};
	corriere_t corr = {0, ""};

	//legge acquirenti
	rewind(acquirenti);
	while(fread(&acquir, sizeof(acquirente_t), 1, acquirenti) == 1) {
		if(strcmp(input, acquir.user) == 0){ //compara l'username parametro con quello nel file
			flag = 1;
		}
	}

	if(flag == 0) { //se non lo trova in acquirenti, controlla nel file esercenti

		//legge esercenti
		rewind(esercenti);
		while(fread(&eser, sizeof(esercente_t), 1, esercenti) == 1) {
			if(strcmp(input, eser.user) == 0) { //compara l'username parametro con quello nel file
				flag = 1;
			}
		}

		if(flag == 0) { // se non lo trova in esercenti, controlla nel file corrieri

			//legge corrieri
			rewind(corrieri);
			while(fread(&corr, sizeof(corriere_t), 1, corrieri) == 1) {
				if(strcmp(input, corr.user) == 0) { // compara l'username paramentro con quello del file
					flag = 1;
				}
			}
		}
	}

	return flag;
}

/*
 * Funzione che legge nel file catalogo trovando l'id maggiore tra tutti i prodotti, lo incrementa e lo restituisce.
 */
int incrementa_id_prodotto() {
	int id = 0, max = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};

	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {
		if(max < prodotto.id_prod) {
			max = prodotto.id_prod;
		}
	}

	id = max + 1;

	return id;
}

/*
 * Funzione che legge nel file acquisti trovando l'id maggiore tra tutti i prodotti, lo incrementa e lo restituisce.
 */
int incrementa_id_ordine() {
	int id = 0, max = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};

	rewind(acquisti);
	while(fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1) {
		if(max < prodotto.id_ordine) {
			max = prodotto.id_ordine;
		}
	}

	id = max + 1;

	return id;
}



















