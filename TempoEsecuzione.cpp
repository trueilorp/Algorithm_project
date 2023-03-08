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
#define B 1

#define E 0.001 //Errore relativo massimo ammissibile

//INTESTAZIONI
int scegliX();
int generaLunghezzaStringa();
int* generaNumeri(int);
double getResolution();
double tempoMinimoMisurabile(double);



int scegliX()
{
    int x;
    srand(time(NULL)); //serve per evitare che ogni volta venga generato lo stesso numero
    x = rand()%100; //genero x tra 0...99 --> Quindi  rand()%100 restituisce i numeri da 0 a 99.
    cout << x << endl;
    return x;
}

int generaLunghezzaStringa()
{
    int x = scegliX();
    int n = floor (A*pow(B,x)); //x deve essere scelta tra 0 e 99
    cout << n << endl;
    return n;
}

/**
     * @brief Funzione per calcolare il tempo di esecuzione usando n fisso a 99
     * Genera numeri random prendendo da un alfabeto binario/terziario e memorizzando tutti i numeri in un array
     */
int* generaNumeri(int n)
{
    int a[n];
	int j;

	srand(time(NULL));
	for (j=0; j<n; j++){		
		a[j]=rand()%3+1; //qui cambio il %2 in %3 per usare rispettivamente alfabeto binario o terziario
	}
				
    //stampo i numeri dell'array
	/*for (j=0; j<n; j++){		
		   cout << a[j];
	}*/
    return a;
}

/**
 * @brief Converte l'array di int in una stringa
 * @param arr 
 * @param n 
 * @return std::string 
 */
string convert(int arr[], int n) {
    string s;
    for (int i = 0; i < n; i++) {
        s += to_string(arr[i]);
    }
    return s;
}

/**
 * @brief Per ogni stringa s di lunghezza n  generata, occorre quindi stimare il tempo di esecuzione per ognuno dei due algoritmi,
 * PeriodNaive o PeriodSmart. Si richiede una stima del tempo medio di esecuzione al variare della lunghezza n
 * della stringa che garantisca un errore relativo massimo pari a 0.001. A tal fine si procede nel modo seguente. 
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
 * T_min=R⋅(1/E+1).
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

double stimaTempoAlgoritmo()
{
    int t=0;
    int n = generaLunghezzaStringa();
    int* array = generaNumeri(n);
    string s = convert(array,n); //qui ho la mia stringa che darò in pasto all'algoritmo per il periodo frazionario
    double R = getResolution(); //prendo la risoluzione 
    double t_minimo = tempoMinimoMisurabile(R); //calcolo il tempo minimo misurabile
    while(t < t_minimo)
    {
        //esempio: con periodo Smart
        pfLineare(s);
        t++;
    }

    return 0;
    
}

int main()
{
    //int n = generaLunghezzaStringa(); //lunghezza della stringa da scegliere con la funzione esponenziale

	//generaNumeri(n); //genera una stringa di lunghezza n

    cout << stimaTempoAlgoritmo();


	return 0;	
}