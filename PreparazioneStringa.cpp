#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define A 1000
#define B 1.06478598  //B = (n/A)^(1/i) = (500000/1000)^(1/99)

/**
 * @brief Restituisce la lunghezza della stringa 
 * @param x intero compreso tra 0 e 99
 * @return lunghezza della stringa 
 */
int generaLunghezzaStringa(int x){
    int n = floor (A*pow(B,x)); 
    return n;
}

/**
 * @brief Genera in modo casuale una stringa sull'alfabeto ternario (a,b,c)
 * @param n lunghezza stringa
 * @return string che andrà analizzata
 */
string generaStringa(int n){
    string stringa(n, 'a');
    char tmp;
	for (int i=0; i<n; i++){	
        tmp = rand() % 3 + 'a';
		stringa[i] = tmp;
	}
    return stringa;
}

/**
 * @brief mette assieme le due operazioni precedenti
 */
string preparaStringa(int x){
    int lunghezza = generaLunghezzaStringa(x);
    string stringa = generaStringa(lunghezza);
    return stringa;
}