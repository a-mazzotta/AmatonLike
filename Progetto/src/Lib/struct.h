/**
 * @file struct.h
 *
 *  Created on: 9 giu 2021
 *
 * 	Libreria che contiene le struct che gestiscono i dati degli utenti e dei prodotti
 *  @authors: Alessandro, Alessia
 *
 */

#ifndef STRUCT_H_
#define STRUCT_H_

#include "constants.h"

/**
 * Struttura che contiene i dati utili per gli acquirenti
 */
typedef struct {
	/**
	 * Tipo account
	 */
	short int tipo_acc;
	/**
	 * Nome acquirente
	 */
	char nome_acquirente[STR];
	/**
	 * Cognome acquirente
	 */
	char cognome_acquirente[STR];
	/**
	 * Indirizzo acquirente
	 */
	char indirizzo_acquirente[STR];
	/**
	 * Username dell'acquirente
	 */
	char user[STR];  //username
	/**
	 * Password
	 */
	char psw[LUNGHEZZA_PSW]; //password
	/**
	 * Numero di telefono
	 */
	char tel[LUNGHEZZA_TEL]; //numero di telefono
}acquirente_t;

/**
 * Struttura che contiene i dati utili per gli esercenti
 */
typedef struct{
	/**
	 * Tipo account
	 */
	short int tipo_acc;
	/**
	 * Nome azienda venditrice
	 */
	char nome_azienda[STR];
	/**
	 * Codice azienda
	 */
	char cod_azienda[STR];
	/**
	 * Indirizzo dell'azienda
	 */
	char indirizzo_sede[STR];
	/**
	 * Username dell'esercente
	 */
	char user[STR];
	/**
	 * Password dell'esercente
	 */
	char psw[LUNGHEZZA_PSW]; //password
	/**
	 * Numero di telefono dell'esercente
	 */
	char tel[LUNGHEZZA_TEL]; //numero di telefono
}esercente_t;

/**
 * Struttura che contiene i dati utili per i corrieri
 */
typedef struct{
	/**
	 * Tipo account
	 */
	short int tipo_acc;
	/**
	 * Nome dell'azienda del corriere
	 */
	char nome_azienda[STR];
	/**
	 * Nome del corriere
	 */
	char nome[STR];
	/**
	 * Cognome del corriere
	 */
	char cognome[STR];
	/**
	 * Username del corriere
	 */
	char user[STR];
	/**
	 * Password del corriere
	 */
	char psw[LUNGHEZZA_PSW]; //password
	/**
	 * Telefono del corriere
	 */
	char tel[LUNGHEZZA_TEL]; //numero di telefono
}corriere_t;

/**
 * Struttura che contiene i dati del prodotto
 */
typedef struct{
	/**
	 * ID dell'ordine del prodotto
	 */
	int id_ordine; //id prodotto dell'ordine (Poiche' ci potrebbero essere piu' ordini dello stesso prodotto')
	/**
	 * ID del prodotto
	 */
	int id_prod; //id prodotto nel catalogo
	/**
	 *  Totale dei prodotti disponibili
	 */
	int tot_prod_disp; //prodotti disponibili
	/**
	 * Numero dei prodotti venduti
	 */
	int prodotti_venduti;
	/**
	 * La quantità ha due significati: per l'acquirente quanti prodotti vuole acquistare
	 * e per l'esercente quanti ne vuole mettere inv vedinta
	 */
	int quantita; //quantità dei prodotti che vuoi vendere come esercente e che vuoi comprare come acquirente
	/**
	 * Costo del prodotto
	 */
	float costo;
	/**
	 * Nome del prodotto
	 */
	char nome_prodotto[STR];
	/**
	 * Categoria del prodotto
	 */
	char categoria[STR];
	/**
	 * Stato spedizione del prodotto
	 */
	char spedizione[STR]; //stato di spedizione
	/**
	 * Venditore prodotto
	 */
	char esercente[STR]; //chi ha venduto il prodotto
	/**
	 * Acquirente prodotto
	 */
	char acquirente[STR]; //chi ha comprato il prodotto
}prodotto_t;

#endif /* STRUCT_H_ */
