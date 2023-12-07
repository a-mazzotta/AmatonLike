/*
 * specifiche.c
 *
 *  Created on: 16 giu 2021
 *
 *  Libreria che contiene tutte le funzioni e procedure che riguardano le azioni che gli utenti possono fare nel programma.
 *  author: Alessandro, Alessia
 */

#include "constants.h"#include "struct.h"
#include "input.h"
#include "menu_design.h"
#include "specifiche.h"
#include "login.h"

/*
 * Funzione che si occupa della ricerca dei prodotti in base alla categoria scelta dall'utente.
 * Il risultato della ricerca viene passato ad un array che successivamente viene ordinato (se l'utente sceglie un filtro per l'ordinamento del risultato).
 * Ritorna la variabile int risultato che puo' essere 1 se la ricerca non ha trovato prodotti nel file catalogo, oppure 0 se ha trovato dei prodotti
 */
int ricerca_per_categoria() {
	int i = 0, flag = 0, scelta_filtro = 0, risultato = 0;
	prodotto_t prodotto  = {0, 0, 0, 0, 0, 0, ""}, *array = NULL; // array di tipo costo
	char *scelta_categoria = NULL;

	do {
		menu_categorie(); //1)Tecnologia - 2)Casa - 3)Indumenti
		printf("Cerca in:  \n");
		scelta_categoria = input_str(); //la scelta puo' avvenire anche tramite stringa

		for(i = 0; i < strlen(scelta_categoria); i++) { //la categoria scelta viene trasformata in minuscolo
			scelta_categoria[i] = tolower(scelta_categoria[i]);
		}

	} while(((strcmp(scelta_categoria, "tecnologia") != 0) &&  (strcmp(scelta_categoria, "1") != 0)) &&
			((strcmp(scelta_categoria, "casa") != 0) &&  (strcmp(scelta_categoria, "2") != 0)) &&
			((strcmp(scelta_categoria, "Indumenti") != 0) &&  (strcmp(scelta_categoria, "3") != 0)));

	do {
		menu_filtro(); //1)Costo crescente - 2)Costo decrescente - 3)Non filtrare
		scelta_filtro = input_int();

		if((scelta_filtro < 1) || (scelta_filtro > 3)) {
			printf("\nValore non valido!\n");
			system("pause");
			system("cls");
		}
	} while((scelta_filtro < 1) || (scelta_filtro > 3));

	//lettura del numero dei prodotti per l'allocazione dinamica dell'array
	i = 0;
	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {
		i++;
	}

	array = malloc(sizeof(prodotto_t)*i); //allocazione dinamica

	//ogni volta che viene trovato un prodotto consono alla ricerca, viene assegnato all'array
	i = 0;
	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1){
		if(((strcmp(scelta_categoria, "tecnologia") == 0) || (strcmp(scelta_categoria, "1") == 0))) {

			if(strcmp(prodotto.categoria, "tecnologia") == 0) {
				flag = 1; //prodotto trovato
				array[i] = prodotto; //assegnazione all'array
				i++;
			}
		} else if((strcmp(scelta_categoria, "Casa") == 0) || (strcmp(scelta_categoria, "2") == 0)) {

			if(strcmp(prodotto.categoria, "casa") == 0) {
				flag = 1; //prodotto trovato
				array[i] = prodotto; //assegnazione all'array
				i++;
			}
		}else if(((strcmp(scelta_categoria, "indumenti") == 0) || (strcmp(scelta_categoria, "3") == 0))) {

			if(strcmp(prodotto.categoria, "indumenti") == 0) {
				flag = 1; //prodotto trovato
				array[i] = prodotto; //assegnazione all'array
				i++;
			}
		}
	}
	//se non sono stati trovati prodotti, la funzione restituisce risultato = 1
	if(flag == 0) {
		risultato = 1;
		printf("\nNon ci sono prodotti di questa categoria!\n");
		system("pause");
	} else { //se sono stati trovati prodotti, il programma procede all'ordinamento ed alla stampa
		ordinamento_insert_sort(array, i, scelta_filtro);
	}
	return risultato;
}

/*
 * Funzione che si occupa della ricerca dei prodotti in base al nome del prodotto (la ricerca puo' avvenire anche con sottostringa).
 * Il risultato della ricerca viene passato ad un array che successivamente viene ordinato (se l'utente sceglie un filtro per l'ordinamento del risultato).
 * Ritorna la variabile int risultato che puo' essere 1 se la ricerca non ha prodotto risultato, oppure 0 se la ricerca e' andata a buon fine.
 */
int ricerca_per_nome() {
	char *nome_cercato = NULL;
	int flag = 0, i = 0, scelta_filtro = 0, risultato = 0, j = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""}, *array = NULL;

	printf("\nCerca: ");
	nome_cercato = input_str();

	do {
		menu_filtro(); //1)Costo crescente - 2)Costo decrescente - 3)Non filtrare
		scelta_filtro = input_int();

		if((scelta_filtro < 1) || (scelta_filtro > 3)) {
			printf("\nValore non valido!\n");
			system("pause");
			system("cls");
		}
	} while((scelta_filtro < 1) || (scelta_filtro > 3));

	for(i = 0; i < strlen(nome_cercato); i++) { //il nome cercato viene trasformato in minuscolo
		nome_cercato[i] = tolower(nome_cercato[i]);
	}

	//lettura del numero dei prodotti per l'allocazione dinamica dell'array
	i = 0;
	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {
		i++;
	}

	array = malloc(sizeof(prodotto_t)*i); //allocazione dinamicamente

	//ogni volta che viene trovato un prodotto consono alla ricerca, viene assegnato all'array
	i = 0;
	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {

		for(j = 0; j < strlen(prodotto.nome_prodotto); j++) { //il nome del prodotto nel file viene trasformato in minuscolo
			prodotto.nome_prodotto[j] = tolower(prodotto.nome_prodotto[j]);
		}

		if(strncmp(prodotto.nome_prodotto, nome_cercato, strlen(nome_cercato)) == 0) { //viene comparato tramite sottostringa
			flag = 1; //prodotto trovato
			array[i] = prodotto; //assegnazione all'array
			i++;
		}
	}
	//se non sono stati trovati prodotti, la funzione restituisce risultato = 1
	if(flag == 0) {
		printf("\nNon ci sono prodotti con questo nome!\n");
		system("pause");
		risultato = 1;
	} else { //se sono stati trovati prodotti, il programma procede all'ordinamento ed alla stampa
		ordinamento_insert_sort(array, i, scelta_filtro);
	}
	return risultato;
}

/*
 * Procedura che si occupa dell'ordinamento e della stampa dei prodotti che sono stati precedentemente cercati tramite le funzioni di ricerca.
 * Prende come parametro, l'array da ordinare, la sua dimensione e la scelta del filtro che l'utente ha effettuato.
 */
void ordinamento_insert_sort(prodotto_t *array, int dim, int scelta) {
	int i = 0, j = 0;
	prodotto_t temp = {0, 0, 0, 0, 0, 0, ""};

	printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+\n");
	printf("|%-10s |%-30s |%-10s |%-20s |%-20s |", "ID PROD.", "NOME PRODOTTO", "COSTO", "DISPONIBILITA'", "VENDITORE");
	printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+");

	if (scelta == 1) { //se e' stato scelto di ordinare per costo crescente

		for (i=1; i<dim; i++) { // ciclo che scorre tutti gli elementi (parte dal secondo)

			temp = array[i]; // salva il valore da posizionare
			j = i-1; // memorizza l’indice dell’ultimo valore ordinato
			while (j>=0 && array[j].costo>temp.costo) { // ciclo per individuare la posizione corretta

				array[j+1] = array[j]; // se si è arrivati al primo elemento (j==0) oppure
				j--; // se l’elemento corrente è più piccolo di quello da posizionare
			}
			array[j+1] = temp;  // esce dal ciclo quando ha trovato la posizione per l’elemento
		}
		for(i = 0; i < dim; i++ ){

			printf("\n|%-10d |%-30s |%-10.2f |%-20d |%-20s |",
					array[i].id_prod, array[i].nome_prodotto, array[i].costo, array[i].tot_prod_disp, array[i].esercente);
			printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+");
		}
	} else if(scelta == 2){ //se e' stato scelto di ordinare per costo decrescente

		for (i=1; i<dim; i++) { // ciclo che scorre tutti gli elementi (parte dal secondo)

			temp = array[i]; // salva il valore da posizionare
			j = i-1; // memorizza l’indice dell’ultimo valore ordinato
			while (j>=0 && array[j].costo<temp.costo) { // ciclo per individuare la posizione corretta

				array[j+1] = array[j]; // se si è arrivati al primo elemento (j==0) oppure
				j--; // se l’elemento corrente è più piccolo di quello da posizionare
			}
			array[j+1] = temp;  // esce dal ciclo quando ha trovato la posizione per l’elemento
		}
		for(i = 0; i < dim; i++ ){

			printf("\n|%-10d |%-30s |%-10.2f |%-20d |%-20s |",
					array[i].id_prod, array[i].nome_prodotto, array[i].costo, array[i].tot_prod_disp, array[i].esercente);
			printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+");
		}
	} else {//se e' stato scelto di non filtrare il risultato della ricerca
		for(i = 0; i < dim; i++ ){
			printf("\n|%-10d |%-30s |%-10.2f |%-20d |%-20s |",
					array[i].id_prod, array[i].nome_prodotto, array[i].costo, array[i].tot_prod_disp, array[i].esercente);
			printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+");
		}
	}
}

/*
 * Procedura che permette all'acquirente di acquistare un prodotto che ha precedentemente cercato.
 * Prende come parametro l'username dell'utente che ha effettuato l'accesso per memorizzare l'utente che
 * sta effettuando l'acquisto.
 */
void acquisto(char *user) {
	int scelta = 0, ID_scelto = 0, flag = 0, quantita = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};
	FILE *tmp_catalogo = NULL;

	do {
		menu_acquisto(); //Vuoi effettuare un acquisto? 1)Si - 2)No
		scelta = input_int();

		if (scelta == 1) {

			do {
				printf("\nInserire l'ID del prodotto che si vuole acquistare oppure inserire 0 per uscire\n"
						">> ");
				ID_scelto = input_int();

				if(ID_scelto == 0) {
					break;
				}

				//fin quando puoi leggere dal catalogo o fin quando non trovi il prodotto cercato
				rewind(catalogo);
				while((fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) && (flag == 0)){
					if(ID_scelto == prodotto.id_prod) {
						flag = 1; //prodotto trovato
						strcpy(prodotto.acquirente, user);

						do {
							printf("\nQuanti ne vuoi acquistare? Inserire 0 per uscire\n"
									">> ");
							quantita = input_int();

							if(quantita == 0) {
								break;
							}

							if((quantita <= 0) || (quantita > prodotto.tot_prod_disp)) { //controllo sulla quantita'
								printf("\nQuantita' non disponibile!\n");
								system("pause");
							}
						} while((quantita <= 0) || (quantita > prodotto.tot_prod_disp));

						prodotto.id_ordine = incrementa_id_ordine(); //viene assegnato un nuovo id all'ordine
						prodotto.quantita = quantita;

						tmp_catalogo = fopen("DatFiles/tmp_catalogo.dat", "wb+"); //viene creato un file temporaneo per la modifica fisica del file

						//vengono modificati i dati per quanto riguarda la disponibilita' del prodotto e del numero di prodotti venduti
						prodotto.tot_prod_disp = prodotto.tot_prod_disp - quantita;
						prodotto.prodotti_venduti = prodotto.prodotti_venduti + quantita;

						//scrive l'acquisto nel file acquisti
						fseek(acquisti, 0, SEEK_END);
						fwrite(&prodotto, sizeof(prodotto_t), 1, acquisti);

						//i dati relativi all'acquisto vengono resettati
						prodotto.quantita = 0;
						strcpy(prodotto.acquirente, "");

						//scrittura sul file temporaneo del prodotto
						fseek(tmp_catalogo, 0, SEEK_END);
						fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_catalogo);

						//riscrivo tutti i prodotti che c'erano in catalogo dentro il file temporaneo, tranne quello appena modificato
						rewind(catalogo);
						while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {
							if(prodotto.id_prod != ID_scelto) {

								fseek(tmp_catalogo, 0, SEEK_END);
								fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_catalogo);
							}
						}

						//vengono chiusi i file per poterli rimuovere/rinominare
						fclose(catalogo);
						fclose(tmp_catalogo);

						remove("DatFiles/catalogo.dat");
						rename("DatFiles/tmp_catalogo.dat", "DatFiles/catalogo.dat");

						//viene riaperto il file temporaneo come file principale
						catalogo = fopen("DatFiles/catalogo.dat", "rb+");
					}
				}
				if(flag == 1) {
					printf("\nProdotto acquistato correttamente!\n");
					system("pause");
					system("cls");
				} else {
					printf("\nProdotto non esistente!\n");
					system("pause");
				}

			} while(flag == 0);

		}else if (scelta == 2) {
			break;
		} else {
			printf("\nScelta non valida!\n");
			system("pause");
			system("cls");
		}

	} while(scelta != 1);
}

/*
 * Procedura che permette all'acquirente di cancellare un ordine non ancora consegnato.
 * Prende come parametro l'username dell'utente che ha effettuato l'accesso per
 * effettuare il controllo sul proprietario dell'ordine da voler cancellare.
 */
void cancellazione_acquisti(char* user){
	int id = 0, flag = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};
	FILE *tmp_acquisti = NULL, *tmp_catalogo = NULL;

	//inserimento ID
	do {
		printf("\nInserisci l'ID dell'ordine che vuoi eliminare oppure inserire 0 per uscire\n"
				">> ");
		id = input_int();

		if(id == 0) { //sentinella
			break;
		}

		//legge da acquisti e ricerca l'ordine da cancellare
		rewind(acquisti);
		while((fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1) ) {
			if((prodotto.id_ordine == id) && (strcmp(prodotto.acquirente, user) == 0)) { //controllo

				if(strcmp(prodotto.spedizione, "Consegnato") == 0) { //controllo
					flag = 2;
					printf("\nUn prodotto gia' consegnato, non puo' essere eliminato!\n");
					system("pause");
					system("cls");

				} else {
					flag = 1;// quando ha eliminato un prodotto
				}
			}
		}

		if(flag == 1) { //file temporanei per la cancellazione e la modifica
			tmp_acquisti = fopen("DatFiles/tmp_acquisti.dat", "wb+");
			tmp_catalogo = fopen("DatFiles/tmp_catalogo.dat", "wb+");

			//leggi, se trova il prodotto da cencellare, lo modifica nel catalogo, mentre gli altri prodotti li trascrive nel file temporaneo degli acquisti
			rewind(acquisti);
			while((fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1)){
				if(prodotto.id_ordine == id) {

					//modifica
					prodotto.tot_prod_disp = prodotto.tot_prod_disp + prodotto.quantita;
					prodotto.prodotti_venduti = prodotto.prodotti_venduti - prodotto.quantita;

					//trascrive la modifica nel file temporaneo del catalogo
					fseek(tmp_catalogo, 0, SEEK_END);
					fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_catalogo);

					//riscrive tutti i vecchi prodotti tranne quello appena modificato nel nuovo file catalogo
					rewind(catalogo);
					while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1) {
						if(prodotto.id_ordine != id) {
							fseek(tmp_catalogo, 0, SEEK_END);
							fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_catalogo);
						}
					}

					//trascrive tutti i vecchi prodotti tranne quello da cancellare nel nuovo file acquisti
				} else {
					fseek(tmp_acquisti, 0, SEEK_END);
					fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_acquisti);
				}
			}

			printf("\nOrdine eliminato con successo\n");
			system("pause");
			system("cls");

			//cancellazione fisica
			fclose(acquisti);
			fclose(tmp_acquisti);
			fclose(catalogo);
			fclose(tmp_catalogo);

			remove("DatFiles/acquisti.dat");
			rename("DatFiles/tmp_acquisti.dat", "DatFiles/acquisti.dat");
			remove("DatFiles/catalogo.dat");
			rename("DatFiles/tmp_catalogo.dat", "DatFiles/catalogo.dat");

			acquisti = fopen("DatFiles/acquisti.dat", "rb+");
			catalogo = fopen("DatFiles/catalogo.dat", "rb+");

		} else if(flag == 0) {
			printf("\nProdotto non esistente!\n");
			system("pause");
		}
	} while((flag == 0) || (flag == 2));

}

/*
 * Procedura che permette all'acquirente di visualizzare tutti gli acquisti effettuati.
 * Prende come parametro l'username dell'utente che ha effettuato l'accesso per la ricerca dei suoi acquisti.
 */
void visualizza_acquisti(char *user) {
	int flag = 0, flag1 = 0, scelta = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};
	acquirente_t acquir = {0, ""};
	esercente_t eser = {0, ""};

	rewind(acquirenti); // prende i dati dell'acquirente
	while((flag1 == 0) && (fread(&acquir, sizeof(acquirente_t), 1, acquirenti) == 1)) {

		if(strcmp(acquir.user, user) == 0){ //comparazione username
			flag1 = 1; //trova l'acquirente
		}
	}

	printf("+-----------+-------------------------------+-----------+---------------------+---------------------+-------------------------------+\n");
	printf("|%-10s |%-30s |%-10s |%-20s |%-20s |%-30s |", "ID ORDINE", "NOME PRODOTTO", "COSTO", "QUANTITA' ORDINATA", "STAT. SPED.", "VENDITORE");
	printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+-------------------------------+");

	rewind(acquisti);//ricerca del prodotto nel file acquisti
	while(fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1){

		if(strcmp(prodotto.acquirente, user) == 0){ //se l'username dell'acquirente, corrisponde all'username di chi ha acquistato il prodotto
			flag = 1; //trova il prodotto

			//cerca i dati dell'esercente che ha messo in vendita il prodotto
			rewind(esercenti);
			while(fread(&eser, sizeof(esercente_t), 1, esercenti) == 1) { //cerca nel file esercenti

				if(strcmp(eser.user, prodotto.esercente) == 0) {//se l'username esercente corrisponde al venditore del prodotto
					break;
				}
			}

			//stampa i dati
			printf("\n|%-10d |%-30s |%-10.2f |%-20d |%-20s |%-30s |",
					prodotto.id_ordine, prodotto.nome_prodotto, prodotto.costo, prodotto.quantita, prodotto.spedizione, eser.nome_azienda);
			printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+-------------------------------+");
		}
	}

	if(flag == 0) {
		printf("\nNon hai compiuto acquisti!\n");
		system("pause");
		system("cls");
	} else {
		do { //se trova almeno un prodotto, chiede se si vuole cancellare un prodotto
			printf("\nVuoi cancellare un ordine?\n"
					"[1] - Si\n"
					"[2] - No\n"
					">> ");
			scelta = input_int();

			if(scelta == 1) {
				cancellazione_acquisti(user);
			} else if(scelta == 2) {
				break;
			} else {
				printf("\nScelta non valida!\n");
				system("pause");
				system("cls");
			}
		} while(scelta != 1);
	}
}

/*
 * Procedura che permette all'esercente di inserire nel catalogo un prodotto, inserendo i dati richiesti.
 * Prende come parametro l'username dell'utente che ha effettuato l'accesso, per memorizzare chi ha messo in vendita il prodotto.
 */
void vendi_prodotto(char *user) {
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0,""};
	char *categoria = NULL;
	int i = 0, flag = 0, scelta = 0;

	//assegnamo un id univoco al prodotto nel file catalogo
	do {
		scelta = 0;
		system("cls");

		prodotto.id_prod = incrementa_id_prodotto();

		//nome prodotto
		printf("\nInserisci il nome del prodotto, inserire 0 per tornare indietro.\n"
				">> ");
		strcpy(prodotto.nome_prodotto,input_str());

		if(strcmp(prodotto.nome_prodotto, "0") != 0) {
			//disponibilita' totale del prodotto
			do {
				printf("\nInserisci la disponibilita' del prodotto\n"
						">> ");
				prodotto.tot_prod_disp = input_int();

				if(prodotto.tot_prod_disp <= 0) {
					printf("Disponibilita' non valida\n"
							"Reinserire disponibilita'\n"
							">> ");
					system("pause");
					system("cls");
				}

			} while(prodotto.tot_prod_disp <= 0);

			//costo del prodotto
			do{
				printf("\nInserisci il costo del prodotto\n"
						">> ");
				prodotto.costo = input_float();

				if(prodotto.costo <= 0){
					printf("Prezzo non valido\n"
							"Reinserire costo\n"
							">> ");
					system("pause");
					system("cls");
				}
			}while(prodotto.costo  <= 0);

			//categoria del prodotto
			do {
				flag = 0;
				menu_categorie();
				categoria = input_str();

				for(i = 0; i < strlen(categoria); i++) { //Trasforma la stringa inserita in minuscolo per facilitare la comparazione
					categoria[i] = tolower(categoria[i]);
				}

				//controllo sulla categoria
				if((strcmp(categoria, "tecnologia") == 0) || (strcmp(categoria, "1") == 0)) {
					strcpy(prodotto.categoria, "tecnologia");//assegna al filtro il la categoria tecnologia
				} else if((strcmp(prodotto.categoria, "casa") == 0) || (strcmp(categoria, "2") == 0)) {
					strcpy(prodotto.categoria, "casa");//idem
				} else if((strcmp(categoria, "indumenti") == 0) || (strcmp(categoria, "3") == 0)){ // 0 se sono uguali
					strcpy(prodotto.categoria, "indumenti");//idem
				} else {
					flag = 1;
					printf("\nCategoria non valida!\n");
					system("pause");
					system("cls");
				}
			} while(flag == 1);

			//inizializza lo stato di spedizione
			strcpy(prodotto.spedizione, "In attesa");

			//trascrive l'esercente che sta mettendo in vendita il prodotto
			strcpy(prodotto.esercente, user);

			//scrive il prodotto nel file catalogo
			fseek(catalogo, 0, SEEK_END);
			fwrite(&prodotto, sizeof(prodotto_t), 1, catalogo);

			printf("\nProdotto inserito correttamente\n");
			system("pause");

			//possibilita' di inserire piu' di un prodotto
			do {
				system("cls");
				printf("\nVuoi inserire un altro prodotto?\n"
						" [1] - Si\n"
						" [2] - No\n"
						">> ");
				scelta = input_int();

				if(scelta != 1 && scelta != 2){
					printf("\nScelta non valida!\n");
					system("pause");
					system("cls");
				}
			} while((scelta < 1) || (scelta > 2));
		}

	} while((scelta == 1) && (strcmp(prodotto.nome_prodotto, "0") != 0));// se 0 esce

}

/*
 * Procedura che permette all'esercente di visualizzare i suoi prodotti in vendita e di visualizzarne le statistiche come
 * prodotto con piu' vendite, prodotto piu' costoso messo in vendita, numero prodotti per categoria.
 * Prende come parametro l'username dell'utente che ha effettuato l'accesso per la ricerca dei prodotti da egli messi in vendita.
 */
void visualizza_prodotti_esercente(char *user) {
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""}, max_vendite = {0, 0, 0, 0, 0, 0, ""}, max_costo = {0, 0, 0, 0, 0, 0, ""};
	int flag = 0, contatore_tecnologia = 0, contatore_casa = 0, contatore_indumenti = 0;


	printf("+-----------+-------------------------------+-----------+---------------------+---------------------+---------------------+\n");
	printf("|%-10s |%-30s |%-10s |%-20s |%-20s |%-20s |", "ID PROD.", "NOME PRODOTTO", "COSTO", "PROD. VEND.", "PROD. DISP.", "CATEGORIA");
	printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+---------------------+");

	//legge il catalogo
	rewind(catalogo);
	while(fread(&prodotto, sizeof(prodotto_t), 1, catalogo) == 1){

		if(strcmp(prodotto.esercente, user) == 0){ //se trova un prodotto dell'esercente
			flag = 1;
			//prodotto piu venduto
			if(max_vendite.prodotti_venduti < prodotto.prodotti_venduti) {
				max_vendite = prodotto;
			}
			//prodotto piu costoso
			if(max_costo.costo < prodotto.costo) {
				max_costo = prodotto;
			}
			//Conta il numero prodotti in vendita per categoria
			if(strcmp(prodotto.categoria, "tecnologia") == 0) {
				contatore_tecnologia++;
			} else if (strcmp(prodotto.categoria, "casa") == 0) {
				contatore_casa++;
			} else if(strcmp(prodotto.categoria, "indumenti") == 0) {
				contatore_indumenti++;
			}

			//stampa
			printf("\n|%-10d |%-30s |%-10.2f |%-20d |%-20d |%-20s |",
					prodotto.id_prod, prodotto.nome_prodotto, prodotto.costo, prodotto.prodotti_venduti, prodotto.tot_prod_disp, prodotto.categoria);
			printf("\n+-----------+-------------------------------+-----------+---------------------+---------------------+---------------------+");
		}
	}
	if(flag == 0) {
		printf("\nNon ci sono prodotti in vendita!\n");
		system("pause");
		system("cls");
	} else {
		//stampa statistiche
		printf("\nIl prodotto piu' venduto e':\n ID prodotto:%d\t Nome prodotto:%s\t Costo:%.2f\t Numero pezzi venduti:%d\t Numero pezzi disponibili: %d\tCategoria:%s\t\n ",
				max_vendite.id_prod, max_vendite.nome_prodotto, max_vendite.costo, max_vendite.prodotti_venduti, max_vendite.tot_prod_disp, max_vendite.categoria);

		printf("\nIl prodotto piu' costoso e':\n ID prodotto:%d\t Nome prodotto:%s\t Costo:%.2f\t Numero pezzi venduti:%d\t Numero pezzi disponibili: %d\tCategoria:%s\t\n ",
				max_costo.id_prod, max_costo.nome_prodotto, max_costo.costo, max_costo.prodotti_venduti, max_costo.tot_prod_disp, max_costo.categoria);

		printf("\nHai messo in vendita:\nProdotti Tecnologici: %d\nProdotti per la Casa: %d\nProdotti di Abbigliamento: %d\n",
				contatore_tecnologia, contatore_casa, contatore_indumenti);

		system("pause");
		system("cls");
	}
}

/*
 * Procedura che permette al corriere di visualizzare tutti gli stati di spedizione dei prodotti acquistati e di prenderne il carico.
 * Non puo' visualizzare i prodotti gia' consegnati.
 */
void visualizza_spedizione() {
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};
	acquirente_t acquir = {0, ""};
	int scelta = 0, flag = 0;

	printf("+-----------+---------------------+-------------------------------+-------------------------------+----------------+----------------+\n");
	printf("|%-10s |%-20s |%-30s |%-30s |%-15s |%-15s |", "ID ORDINE", "QUANTITA' ORDINATA", "COGNOME ACQUIRENTE", "INDIRIZZO", "RECAPITO TEL.", "STAT. SPED.");
	printf("\n+-----------+---------------------+-------------------------------+-------------------------------+----------------+----------------+");

	//legge acquisti
	rewind(acquisti);
	while(fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1) {

		//trova dati acquirente
		rewind(acquirenti);
		while(fread(&acquir, sizeof(acquirente_t), 1, acquirenti) == 1) {

			if(strcmp(acquir.user, prodotto.acquirente) == 0) {// se trova i dati
				if((strcmp(prodotto.spedizione, "In attesa") == 0) || (strcmp(prodotto.spedizione, "Spedito") == 0)) { //controllo stato spedizione
					flag = 1;

					//stampa risultati
					printf("\n|%-10d |%-20d |%-30s |%-30s |%-15s |%-15s |",
							prodotto.id_ordine, prodotto.quantita, acquir.cognome_acquirente, acquir.indirizzo_acquirente, acquir.tel, prodotto.spedizione);
					printf("\n+-----------+---------------------+-------------------------------+-------------------------------+----------------+----------------+");
				}
			}
		}
	}
	printf("\n");
	system("pause");

	//presa in carico
	if(flag == 1) {
		do {
			printf("\nVuoi prendere in carico una spedizione?\n"
					" [1] - Si\n"
					" [2] - No\n"
					">> ");
			scelta = input_int();

			if(scelta == 1){
				modifica_stato_spedizione();
			} else if (scelta == 2){
				break;
			} else {
				printf("\nScelta non valida!\n");
				system("pause");
				system("cls");
			}
		} while(scelta != 2);
	} else { //nel caso non vengono trovati acquisti
		printf("\nNon ci sono ordini da spedire al momento!\n");
		system("pause");
		system("cls");
	}

}

/*
 * Procedura che permette al corriere di modificare lo stato di spedizione di un prodotto.
 * La modifica avviene da "in attesa" a "spedito", da "spedito" a "consegnato".
 */
void modifica_stato_spedizione() {
	int id = 0, flag = 0;
	prodotto_t prodotto = {0, 0, 0, 0, 0, 0, ""};
	FILE *tmp_acquisti = fopen("DatFiles/tmp_acquisti.dat", "wb+");

	//inserimento ID
	do {
		printf("\nInserire l'ID dell'ordine oppure inserire 0 per uscire\n"
				">> ");
		id = input_int();

		if(id == 0) { //sentinella
			break;
		}

		//ricerca del prodotto da modificare
		rewind(acquisti);
		while((flag == 0) && (fread(&prodotto, sizeof(prodotto_t), 1, acquisti) == 1)) {

			if(id == prodotto.id_ordine) {
				flag = 1;
				if(strcmp(prodotto.spedizione, "In attesa") == 0) { //se lo stato dell'ordine e' "In attesa"
					strcpy(prodotto.spedizione, "Spedito");			//si trasforma in "Cpedito"
					printf("\nModifica effettuata con successo!\n"
							"Il prodotto %d e' in stato di: %s\n", prodotto.id_ordine, prodotto.spedizione);
					system("pause");
				} else if (strcmp(prodotto.spedizione, "Spedito") == 0) {//se lo stato dell'ordine e' "Spedito"
					strcpy(prodotto.spedizione, "Consegnato");	//si trasforma in "Consegnato"
					printf("\nModifica effettuata con successo!\n"
							"Il prodotto %d e' in stato di: %s\n", prodotto.id_ordine, prodotto.spedizione);
					system("pause");
				} else {
					printf("\nIl prodotto %d  e' stato gia' consegnato!\n\n", prodotto.id_ordine);
					system("pause");
					system("cls");
				}

				//modifica del file
				fseek(tmp_acquisti, 0, SEEK_END);
				fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_acquisti);
			} else {
				fseek(tmp_acquisti, 0, SEEK_END);
				fwrite(&prodotto, sizeof(prodotto_t), 1, tmp_acquisti);
			}

		}
		if(flag == 0) {
			printf("\nProdotto non esistente!\n");
			system("pause");
		}
	} while(flag == 0);

	//modifica fisica
	fclose(tmp_acquisti);
	fclose(acquisti);

	remove("DatFiles/acquisti.dat");
	rename("DatFiles/tmp_acquisti.dat", "DatFiles/acquisti.dat");

	acquisti = fopen("DatFiles/acquisti.dat", "rb+");
}


