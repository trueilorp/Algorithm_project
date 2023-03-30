#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define A 1000
#define B 1.06478598  //trovato per tentativi


/**
 * Funzione che prendendo in input un valore compreso tra 0 e 99 restituisce la lunghezza della stringa
*/
int generaLunghezzaStringa(int x){
    int n = floor (A*pow(B,x)); //x deve essere scelta tra 0 e 99
    cout << n << ";";
    return n;
}

/**
 * @brief Funzione per calcolare il tempo di esecuzione usando n fisso a 99
 * Genera numeri random prendendo da un alfabeto binario/terziario e memorizzando tutti i numeri in un array
*/
string generaStringa(int n){
    string stringa;
	int i;
    char tmp;
	for (i=0; i<n; i++){	
        tmp = random() % 3 + 'a';
		stringa = stringa + tmp;
	}
    return stringa;
}

/**
 * Funzione che prepara la stringa per l'esecuzione dell'algoritmo
*/
string preparaStringa(int x){
    int lunghezza = generaLunghezzaStringa(x);
    string stringa = generaStringa(lunghezza);
    return stringa;
}