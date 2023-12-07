/*
 * home_account.c
 *
 *  Created on: 16 giu 2021
 *
 *  Libreria che contiene le procedure utili per i menu'/home degli utenti
 *  author: Alessandro, Alessia
 *
 */

#include "librerie.h"
#include "menu_design.h"
#include "input.h"
#include "constants.h"
#include "specifiche.h"

/*
 * Procedura che si occupa delle funzioni che l'acquirente puo' eseguire
 * per gli acquisti e per la visualizzazione di essi in base all'utente che ha effettuato l'accesso.
 */
void home_acquirente(char *user) {
	int scelta = 0, scelta_ricerca = 0, risultato = 0;

	do {
		printf("\nSelezionare una opzione\n"
			">> ");
		menu_acquirente(); //1)ricerca prodotto - 2)visualizza acquisti - 3)torna al login
		scelta = input_int();

		if(scelta == 1) { // Ricerca di un prodotto
			do {
				system("cls");
				menu_ricerca_prodotto();//1)Ricerca per categoria - 2)Ricerca per nome - 3)Esci
				scelta_ricerca = input_int();

				if(scelta_ricerca == 1) { //Ricerca per categoria
					risultato = ricerca_per_categoria();
					if (risultato == 0) { //Se la ricerca ha portato ad un risultato allora sara' possibile acquistare
						acquisto(user);
					}
				} else if(scelta_ricerca == 2) { //Ricerca per nome
					risultato = ricerca_per_nome();
					if(risultato == 0) { //Se la ricerca ha portato ad un risultato allora sara' possibile acquistare
						acquisto(user);
					}
				} else if(scelta_ricerca == 3) { //esci
					break;
				} else {
					printf("\nScelta non valida!\n");
					system("pause");
					system("cls");
				}
			} while(scelta_ricerca != 3);

		} else if(scelta == 2) { //Visualizzare acquisti
			visualizza_acquisti(user);

		} else if(scelta == 3) { //esci
			break;

		} else {
			printf("\nScelta non valida!\n");
			system("pause");
			system("cls");

		}
	} while(scelta != 3);
}

/*
 * Procedura che si occupa delle funzioni che l'esercente puo' eseguire per la vendita e per la
 * visualizzazione degli articoli messi in vendita in base all'utente che ha effettuato l'accesso.
 */
void home_esercente(char *user) {
	int scelta = 0, scelta_ricerca = 0;

	do {
		printf("\nSelezionare una opzione\n"
			">> ");
		menu_esercente(); //1)Ricerca prodotto - 2)Vendi prodotto - 3)Visualizza prodotti in vendita - 4)Esci
		scelta = input_int();

		if(scelta == 1) { // Ricerca di un prodotto
			do {
				system("cls");
				menu_ricerca_prodotto();
				scelta_ricerca = input_int();

				if(scelta_ricerca == 1) { //Ricerca per categoria
					ricerca_per_categoria();
					printf("\n");
					system("pause");
				} else if(scelta_ricerca == 2) { //Ricerca per nome
					ricerca_per_nome();
					printf("\n");
					system("pause");
				} else if(scelta_ricerca == 3) { //Esci
					break;
				} else {
					printf("\nScelta non valida!\n");
					system("pause");
					system("cls");
				}
			} while(scelta_ricerca != 3);

		} else if(scelta == 2) { //Vendi un prodotto
			vendi_prodotto(user);
		} else if(scelta == 3) {//Visualizza tuoi prodotti in vendita
			visualizza_prodotti_esercente(user);

		} else if(scelta == 4) { //Esci
			break;

		} else {
			printf("\nScelta non valida!\n");
			system("pause");
			system("cls");

		}
	} while(scelta != 4);
}


//Procedura che si occupa delle funzioni che il corriere puo' eseguire.
void home_corriere() {
	int scelta = 0;

	do {
		printf("\nSelezionare una opzione\n"
			">> ");
		menu_corriere(); //1)Visualizza/Modifica spedizione - 2)Esci
		scelta = input_int();

		if(scelta == 1) { // Visualizzazione/Modifica stato di spedizione
			visualizza_spedizione();

		} else if(scelta == 2) { //Esci
			break;

		} else {
			printf("\nScelta non valida!\n");
			system("pause");
			system("cls");

		}
	} while(scelta != 2);
}

