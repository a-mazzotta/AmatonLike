/**
 * @file input.h
 *
 *  Created on: 9 giu 2021
 *
 *  Libreria che si occupa degli iserimenti in input e dei controlli degli inserimenti
 *  e l'incremento degli id per quanto riguarda i prodotti
 *  @authors: Alessandro, Alessia
 *
 */

#ifndef INPUT_H_
#define INPUT_H_

/**
 * Funzione che si occupa dell'inserimento di interi con programmazione difensiva nel caso non viene inserito un intero.
 * @return l'intero inserito.
 */
int input_int();

/**
 * Funzione che si occupa dell'inserimento di float con programmazione difensiva nel caso non viene inserito un float.
 * @return il numero decimale inserito.
 */
float input_float();

/**
 * Funzione che si occupa dell'inserimento di stringhe con programmazione difensiva nel caso non viene inserita una stringa
 * o la stringa inserita e' vuota.
 * @return la stringa inserita.
 */
char *input_str();

/**
 * Funzione che si occupa dell'inserimento del numero di telefono con programmazione difensiva nel caso
 * il numero inserito non e' lungo 10 numeri o nel caso non ci sono numeri.
 * @return il numero di telefono.
 */
char *input_tel();

/**
 * Funzione che si occupa dell'inserimento della password con programmazione difensiva nel caso
 * la password e' piu' lunga di 5 caratteri e non contiene una maiuscola ed un numero.
 * @return la password
 */
char* input_pass();

/**
 * Funzione che controlla se la stringa presa come parametro contiene numeri.
 * @param stringa da controllare.
 * @return 1 nel caso ci sono numeri o 0 se non ci sono.
 */
int controllo_num_string(char* stringa);

/**
 * Funzione che legge nei file utente, se trova l'username preso come parametro, all'interno di un file,
 * allora l'username e' gia' esistente.
 * @param input inserito dall'utente.
 * @return 0 se l'username non esista gia', 1 se l'username esiste gia'.
 */
int controllo_username(char* input);

/**
 * Funzione che legge nel file catalogo l'ultimo prodotto controllandone l'id prodotto ed incrementandolo di uno.
 * @return l'id incrementato.
 */
int incrementa_id_prodotto();

/**
 * Funzione che legge nel file acquisti l'ultimo prodotto controllandone l'id ordine ed incrementandolo di uno
 * @return l'id incrementato.
 */
int incrementa_id_ordine();

#endif /* INPUT_H_ */
