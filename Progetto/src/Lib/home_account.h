/**
 * @file home_account.h
 *
 *  Created on: 16 giu 2021
 *
 *  Libreria che contiene le procedure utili per i menu'/home degli utenti
 *  @authors: Alessandro, Alessia
 *
 */

#ifndef LIB_HOME_ACCOUNT_H_
#define LIB_HOME_ACCOUNT_H_

/**
 * Procedura che si occupa delle funzioni che l'acquirente puo' eseguire
 * per gli acquisti e per la visualizzazione di essi in base all'utente che ha effettuato l'accesso.
 * @param user dell'utente che ha effettuato l'accesso
 */
void home_acquirente(char *user);

/**
 * Procedura che si occupa delle funzioni che l'esercente puo' eseguire per la vendita e per la
 * visualizzazione degli articoli messi in vendita in base all'utente che ha effettuato l'accesso.
 * @param user dell'utente che ha effettuato l'accesso
 */
void home_esercente(char *user);

/**
 * Procedura che si occupa delle funzioni che il corriere puo' eseguire.
 */
void home_corriere();

#endif /* LIB_HOME_ACCOUNT_H_ */
