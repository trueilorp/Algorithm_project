/**
 * @file TempoEsecuzione.cpp
 * @author DARIO-MONTE
 * @brief 
 * @version 0.1
 * @date 2023-03-07
 * 
 * @copyright Copyright (c) 2023
 * 
 * 1. Calcolare n, che è la lunghezza della stringa: deve avere una funzione esponenziale del tipo pavimento (A * B^i) dove i va da 0...99
 *    Inoltre vale che n=1000 quando i=0 ed n=500000 quando i=99.
 * 2. Generare la stringa s usando uno dei tre metodi a scelta proposti dal prof. stando all'interno di un alfabeto o binario o terziario
 *    Noi usiamo il primo metodo che sembra quello più facile --> 
 *    --> le lettere s(i) della stringa, per ogni i=1,…,n, vengono generate in modo pseudo-casuale e indipendentemente una dall'altra.
 *    
 * 
 */

#include <iostream>
#include <random>
#include <string>
#include <math.h>
#include <chrono> //libreria per il clock di sistema 
#include "Header.h"

using namespace std;
using namespace std::chrono; //per il clock di sistema 
typedef duration<double, seconds::period> secs;

#define A 1000
#define B 1.06478598  //trovato per tentativi
#define E 0.001 //Errore relativo massimo ammissibile

/**
 * @brief Calcola l'esponente
 * 
 * @return int 
 */

int generatoreNumeri(int n){
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, n);
    return distrib(gen);
}

/*
int generaEsponente(){
    return generatoreNumeri(99);
}
*/


/**
 * Questa funziona genera casualmente un numero da 1000 a 500.000 che sarà poi la lunghezza della stringa 
 * 
*/
int generaLunghezzaStringa(int x){
    int n = floor (A*pow(B,x)); //x deve essere scelta tra 0 e 99
    // cout << "Lunghezza stringa: " << n << endl;
    return n;
}

/**
 * @brief Funzione per calcolare il tempo di esecuzione usando n fisso a 99
 * Genera numeri random prendendo da un alfabeto binario/terziario e memorizzando tutti i numeri in un array
*/
string generaStringa(int n){
    string stringa;
	int i;
    int tmp;

	for (i=0; i<n; i++){		
		tmp=generatoreNumeri(2); //qui cambio il %2 in %3 per usare rispettivamente alfabeto binario o terziario
        if(tmp == 1){
            stringa = stringa + 'a';
        } else if(tmp == 2){
            stringa = stringa + 'b';
        } else {
            stringa = stringa + 'c';
        }
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

/**
 * @brief Il primo passo consiste nello stimare la risoluzione del clock di sistema,
 * utilizzando un ciclo while per calcolare l'intervallo minimo di tempo misurabile
 */
double getResolution(){
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    return duration_cast<secs>(end - start).count();
}

/**
 * @brief Successivamente, in funzione della risoluzione stimata R e dell'errore relativo massimo ammissibile (E=0.001), 
 * si calcola il tempo minimo misurabile
 * 
 * T_min = R⋅(1/E+1).
 */
double tempoMinimoMisurabile(){
    double R = getResolution();
    double t_minimo = R*((1/E) + 1);
    return t_minimo;
}

/**
 * @brief Infine, si utilizza un ciclo while per iterare l'esecuzione dell'algoritmo, misurando il tempo trascorso dall'inizio dell'iterazione, 
 * fino a quando tale tempo non risulti superiore a Tmin.
 * Il tempo medio di esecuzione per una singola istanza di input sarà quindi dato dal rapporto fra il tempo trascorso
 * e il numero di iterazioni eseguite.
 */


/**
 * funzione che calcola il tempo totale e le iterazioni fatte
*/

void calcolaTempo(){
    
    steady_clock::time_point t_inizioFunzione, t_fineFunzione;
    double t, t_minimo, t_medio, t_TOT;
    int count = 0, k = 0;
    
    for(int i = 0; i < 100; i++){
        t_minimo = tempoMinimoMisurabile();
        t_inizioFunzione = steady_clock::now(); //setto l'inizio del cronometro
        do{
            string s = preparaStringa(i);  //prepara la stringa
            k = periodSmart(s); //eseguo l'algoritmo
            t_fineFunzione = steady_clock::now();
            t = duration_cast<secs>(t_fineFunzione - t_inizioFunzione).count(); //calcolo il tempo di esecuzione

            t_TOT = t_TOT + t; //tengo traccia del tempo totale di esecuzione dell'algoritmo
            count++; //tengo traccia del numero di iterazioni fatte
            // cout << "Tempo di esecuzione: " << t << endl;
            // cout << "Tempo minimo stimato: " << t_minimo << endl;
        }while(t < t_minimo);
        cout << t / count << endl;; //calcolo il tempo medio di esecuzione dividento il tempo totale per il numero di esecuzioni fatte
        count = 0;
        // cout << '\n';
        // cout << count << endl;
        // cout << t_medio << endl;
    }
}


/**
 * la modifica nel programma consiste nel valutare l'algoritmo sempre su una stringa di lunghezza prefissata
 * iterando la procedura fino a quando il tempo di esecuzione supera la risoluzione del clock di sistema
*/


/*

L'idea è quella di creare una variabile che prenda il tempo di inizio dell'esecuzione del programma ed una che 
prenda il tempo di fine esecuzione e poi si fa la sottrazione tenendo conto di eventuali errori ect..

*/