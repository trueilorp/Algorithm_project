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

#include <cstdlib>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include <math.h>
#include <chrono> //libreria per il clock di sistema 
#include "Header.h"

using namespace std;
using namespace std::chrono; //per il clock di sistema 

#define A 1000
#define B 1.06478598  //trovato per tentativi
#define E 0.001 //Errore relativo massimo ammissibile


/**
 * @brief Calcola l'esponente
 * 
 * @return int 
 */

int generatoreNumeri(int n) {
  std::random_device rd;  
  std::mt19937 gen(rd()); 
  std::uniform_int_distribution<> distrib(1, n);
  return distrib(gen);
}

int scegliEsponente() 
{
    return generatoreNumeri(100);
}


/**
 * Questa funziona genera casualmente un numero da 1000 a 500.000 che sarà poi la lunghezza della stringa 
 * 
*/
int generaLunghezzaStringa()
{
    int x = scegliEsponente();
    int n = floor (A*pow(B,x)); //x deve essere scelta tra 0 e 99
    cout << "Lunghezza stringa: " << n << endl;
    return n;
}

/**
     * @brief Funzione per calcolare il tempo di esecuzione usando n fisso a 99
     * Genera numeri random prendendo da un alfabeto binario/terziario e memorizzando tutti i numeri in un array
     */
string generaStringa(int n){
    string a = (char*)malloc(sizeof(char)*n);;
	int i;
    int tmp;
    
    cout << "Stringa: ";

	for (i=0; i<n; i++){		
		tmp=generatoreNumeri(3); //qui cambio il %2 in %3 per usare rispettivamente alfabeto binario o terziario
        if(tmp == 1){
            a = a + 'a';
        } else if(tmp == 2){
            a = a + 'b';
        } else {
            a = a + 'c';
        }
	}
				
    //stampo i numeri dell'array
	/*for (j=0; j<n; j++){		
		   cout << a[j];
	}*/
    cout << a << endl;
    return a;
}

/**
 * @brief Il primo passo consiste nello stimare la risoluzione del clock di sistema,
 * utilizzando un ciclo while per calcolare l'intervallo minimo di tempo misurabile
 */
double getResolution() 
{
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> secs;
    return duration_cast<secs>(end - start).count();
}

/**
 * @brief Successivamente, in funzione della risoluzione stimata R e dell'errore relativo massimo ammissibile (E=0.001), 
 * si calcola il tempo minimo misurabile
 * 
 * T_min = R⋅(1/E+1).
 */
double tempoMinimoMisurabile(double R)
{
    double t_minimo;
    t_minimo = R*(1/E + 1);
    return t_minimo;
}

/**
 * @brief Infine, si utilizza un ciclo while per iterare l'esecuzione dell'algoritmo, misurando il tempo trascorso dall'inizio dell'iterazione, 
 * fino a quando tale tempo non risulti superiore a Tmin.
 * Il tempo medio di esecuzione per una singola istanza di input sarà quindi dato dal rapporto fra il tempo trascorso
 * e il numero di iterazioni eseguite.
 */


/**
 * Funzione che prepara la stringa per l'esecuzione dell'algoritmo
*/
string preparaStringa()
{
    int n = generaLunghezzaStringa();
    string stringa = generaStringa(n);
    return stringa;
}

/**
 * funzione che calcola il tempo totale e le iterazioni fatte
*/

void calcolaTempo(){
    double R = getResolution(); //stima il clock di sistema 
    double t_minimo = tempoMinimoMisurabile(R); //calcolo il tempo minimo misurabile
    
    clock_t t_TOT, t_inizioFunzione, t_fineFunzione;
    double t, t_medio;
    int count = 0, k = 0;
    
    do{
        string *s = new string;
        *s = preparaStringa();  //prepara la stringa
        t_inizioFunzione = clock(); //setto l'inizio del cronometro
        k = periodSmart(*s); //eseguo l'algoritmo
        t_fineFunzione = clock();//fermo il cronometro
        t = ((double) (t_fineFunzione - t_inizioFunzione) / CLOCKS_PER_SEC);//calcolo il tempo di esecuzione
        delete(s);
        cout << '\n';
        cout << t << endl;
        cout << t_minimo << endl;
        count++;//tengo traccia del numero di iterazioni fatte
    }while(t < t_minimo);
    t_TOT = ((double) (t_TOT + t) / CLOCKS_PER_SEC);
    t_medio = ((double) (t_TOT) / CLOCKS_PER_SEC) / count;
    cout << '\n';
    cout << count << endl;
    // cout << t_medio << endl;
}

int main(){
    
    calcolaTempo();
    cout << endl;

	return 0;	
}


/*

L'idea è quella di creare una variabile che prenda il tempo di inizio dell'esecuzione del programma ed una che 
prenda il tempo di fine esecuzione e poi si fa la sottrazione tenendo conto di eventuali errori ect..

*/

/*
CODICE PER LA STIMA DEI TEMPI CON chatGBT

#include <iostream>
#include <ctime>

using namespace std;

void myFunction() {
  // qui inserisci la tua funzione
}

int main() {
  clock_t start, end;
  double cpu_time_used;

  start = clock(); // inizio del conteggio del tempo

  myFunction(); // chiamata alla tua funzione

  end = clock(); // fine del conteggio del tempo
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  cout << "Tempo di esecuzione: " << cpu_time_used << " secondi." << endl;

  return 0;
}


*/