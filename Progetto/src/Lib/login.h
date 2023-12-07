/**
 * @file login.h
 *
 *  Created on: 9 giu 2021
 *
 *  Libreria che contiene le funzioni e procedure utili all' inizio del programma e alla fase di login
 *  @authors: Alessandro, Alessia
 *
 */

#ifndef LOGIN_H_
#define LOGIN_H_

/**
 * Funzione che si occupa della fase di login e permette all'utente di scegliere se accedere o registra.
 * Nel caso l'utente scelga di accedere, il programma memorizzera' l'username con cui si e' effettuato l'accesso.
 * Nel caso l'utente scelga di registrarsi, il programma acquisira' le informazioni utili alla registrazione e tornera' alla fase login.
 * @return l'username dell'utente che ha effettuato l'accesso.
 */
char* login();

/**
 * Funzione che si occupa dell'accesso al programma, chiedendo in input all'utente username e password che verranno confrontati con quelli registrati.
 * @return l'username dell'utente che ha effettuato l'accesso.
 */
char *accesso();

/**
 * Procedura che acquisisce i dati utili per la registrazione di un nuovo account nel programma.
 * L'utente dovra' prima scegliere che tipo di account registrare ed in base al tipo scelto, verranno chiesti determinati dati.
 */
void registrazione();

/**
 * Funzione che prende come parametro l'username con cui si e' effettuato l'acesso, ne ricava il tipo ritornandolo,
 * controllando in quale file si trova quell'username.
 * @param user dell'utente che ha effettuato l'accesso.
 * @return 1 se trova l'username nel file acquirenti, 2 se trova l'username nel file esercenti,
 * 3 se trova l'username nel file corrieri.
 */
int tipo_account(char* user);

/**
 * Funzione che apre tutti i file
 * @return 1 se ha successo l'apertura, 0 altrimenti
 */
int apri_files();

/**
 * Procedura che chiude tutti i file
 */
void chiudi_files();

#endif /* LOGIN_H_ */
