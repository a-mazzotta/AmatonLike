/*
 *  menu_design.c
 *
 *  Created on: 9 giu 2021
 *
 *	Libreria che contiene le implementazioni delle procedure
 *	che gesticono le interfacce grafiche del programma
 *  authors: Alessandro, Alessia
 */

#ifndef MENU_DESIGN_C_
#define MENU_DESIGN_C_

#include "librerie.h"

void menu_login() {
	system("cls");
	printf("[1] - Accesso\n"
		"[2] - Registrazione\n"
		"[3] - Esci\n"
		">> ");
}

void menu_account_registrazione() {
	system("cls");
	printf("Scegliere il tipo di account\n"
		"[1] - Account Acquirente\n"
		"[2] - Account Esercente\n"
		"[3] - Account Corriere\n"
		"[4] - Menu' Principale\n"
		">> ");

}

void menu_acquirente(){
	system("cls");
	printf("[1] - Ricerca di un prodotto\n"
		"[2] - Visualizzare acquisti\n"
		"[3] - Indietro\n"
		">> ");

}

void menu_esercente(){
	system("cls");
	printf("[1] - Ricerca di un prodotto\n"
		"[2] - Vendi un prodotto\n"
		"[3] - Visualizza i tuoi prodotti in vendita\n"
		"[4] - Indietro\n"
		">> ");
}

void menu_corriere(){
	system("cls");
	printf(
		  	"\n   .----------------.\n"
            "   |_I_I_I_I_I_I_I_I]___ \n"
        	"   |_          : ; _    )\n"
        	"   (_)----------=-(_)-'  \n\n"
			"[1] - Visualizza prodotti da spedire\n"
			"[2] - Indietro\n"
			">> ");
}

void menu_categorie(){
	printf("\nCategorie disponibili :\n");
	printf("[1] - Tecnologia\n"
		"[2] - Casa\n"
		"[3] - Indumenti\n"
		">> ");
}

void menu_ricerca_prodotto(){
	printf("Come vuoi ricercare il prodotto:\n"
		"[1] - Ricerca per categoria\n"
		"[2] - Ricerca per nome\n"
		"[3] - Annulla\n"
		">> ");
}

void menu_acquisto(){
	printf("\nVuoi acquistare un prodotto?\n"
		"[1] - Si\n"
		"[2] - No\n"
		">> ");
}

void menu_filtro(){
	printf("Filtra per:\n"
		"[1] - Costo ordine crescente\n"
		"[2] - Costo ordine decrescente\n"
		"[3] - Non filtrare\n"
		">> ");
}

#endif /* MENU_DESIGN_C_ */
