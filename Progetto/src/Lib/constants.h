/**
 * @file constants.h
 *
 *  Created on: 9 giu 2021
 *
 *  Libreria che contiene le costanti utili al programma
 *  @authors: Alessandro, Alessia
 */



#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include"librerie.h"

/**
 * Lunghezza per le stringhe generali
 */
#define STR 50

/**
 * Lunghezza massima per la password
 */
#define LUNGHEZZA_PSW 5

/**
 * Lunghezza massima per il numero di telefono
 */
#define LUNGHEZZA_TEL 10

/**
 * Variabile di tipo FILE per gli acquirenti
 */
FILE *acquirenti;

/**
 * Variabili di tipo FILE per gli esercenti
 */
FILE *esercenti;

/**
 * Variabili di tipo FILE per i corrieri
 */
FILE *corrieri;

/**
 * Variabili di tipo FILE per il catalogo
 */
FILE *catalogo;

/**
 * Variabili di tipo FILE per gli acquisti
 */
FILE *acquisti;

#endif /* CONSTANTS_H_ */
