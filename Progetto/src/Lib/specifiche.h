/**
 * @file specifiche.h
 *
 *  Created on: 16 giu 2021
 *
 *  Libreria che contiene tutte le funzioni e procedure che riguardano le azioni che gli utenti possono fare nel programma.
 *  @authors: Alessandro, Alessia
 */

#ifndef LIB_SPECIFICHE_H_
#define LIB_SPECIFICHE_H_

#include "struct.h"

/**
 * Funzione che si occupa della ricerca dei prodotti in base alla categoria scelta dall'utente.
 * Il risultato della ricerca viene passato ad un array che successivamente viene ordinato (se l'utente sceglie un filtro per l'ordinamento del risultato).
 * @return 1 se la ricerca non ha trovato prodotti nel file catalogo, oppure 0 se ha trovato dei prodotti
 */
int ricerca_per_categoria();

/**
 * Funzione che si occupa della ricerca dei prodotti in base al nome del prodotto (la ricerca puo' avvenire anche con sottostringa).
 * Il risultato della ricerca viene passato ad un array che successivamente viene ordinato (se l'utente sceglie un filtro per l'ordinamento del risultato).
 * @return 1 se la ricerca non ha prodotto risultato, oppure 0 se la ricerca e' andata a buon fine.
 */
int ricerca_per_nome();

/**
 * Procedura che si occupa dell'ordinamento e della stampa dei prodotti che sono stati precedentemente cercati tramite le funzioni di ricerca.
 * @param array dei prodotti da ordinare
 * @param dim (dimensione) dell'array
 * @param scelta del filtro, se si vuole ordinare per costo crescente, costo decrescente o non si vuole ordinare
 */
void ordinamento_insert_sort(prodotto_t *array, int dim, int scelta);

/**
 * Procedura che permette all'acquirente di acquistare un prodotto che ha precedentemente cercato.
 * @param user (username) dell'utente che ha effettuato l'accesso
 */
void acquisto(char *user);

/**
 * Procedura che permette all'acquirente di cancellare un ordine non ancora consegnato.
 * @param user (username) dell'utente che ha effettuato l'accesso
 */
void cancellazione_acquisti(char *user);

/**
 * Procedura che permette all'acquirente di visualizzare tutti gli acquisti effettuati.
 * @param user (username) dell'utente che ha effettuato l'accesso
 */
void visualizza_acquisti(char *user);

/**
 * Procedura che permette all'esercente di inserire nel catalogo un prodotto, inserendo i dati richiesti.
 * @param user (username) dell'utente che ha effettuato l'accesso
 */
void vendi_prodotto(char *user);

/**
 * Procedura che permette all'esercente di visualizzare i suoi prodotti in vendita e di visualizzarne le statistiche come
 * prodotto con piu' vendite, prodotto piu' costoso messo in vendita, numero prodotti per categoria.
 * @param user (username) dell'utente che ha effettuato l'accesso
 */
void visualizza_prodotti_esercente(char *user);

/**
 * Procedura che permette al corriere di visualizzare tutti gli stati di spedizione dei prodotti acquistati e di prenderne il carico.
 * Non puo' visualizzare i prodotti gia' consegnati.
 */
void visualizza_spedizione();

/**
 * Procedura che permette al corriere di modificare lo stato di spedizione di un prodotto.
 * La modifica avviene da "in attesa" a "spedito", da "spedito" a "consegnato".
 */
void modifica_stato_spedizione();

#endif /* LIB_SPECIFICHE_H_ */
