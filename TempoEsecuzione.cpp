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

#define E 0.001 //Errore relativo massimo ammissibile

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
 * Stima del tempo di generazione della stringa che poi dovrà essere sottratto al tempo di esecuzione dell'algoritmo
*/
void stimaTempoPreparazioneStringa(double tempiMedi[]){
    steady_clock::time_point t_inizio, t_fine;
    double t, t_minimo = tempoMinimoMisurabile();
    int count = 0;
    string s;
    for(int i = 0; i < 100; i++){
        t_inizio = steady_clock::now();
        do{
            s = generaStringa(i);
            t_fine = steady_clock::now();
            t = duration_cast<secs>(t_fine - t_inizio).count();
            count++;
        } while ( t < t_minimo);
        tempiMedi[i] = t / count;
        count = 0;
    }
}


void calcolaTempo(){
    steady_clock::time_point t_inizioFunzione, t_fineFunzione;
    double t, t_minimo;
    int count = 0, k = 0;

    double tempoPreparazioneStringa[100];
    stimaTempoPreparazioneStringa(tempoPreparazioneStringa);
    
    for(int i = 0; i < 100; i++){
        t_minimo = tempoMinimoMisurabile();
        t_inizioFunzione = steady_clock::now(); //setto l'inizio del cronometro
        do{
            string s = preparaStringa(i);  //prepara la stringa
            k = periodNaiveConCompare(s); //eseguo l'algoritmo
            t_fineFunzione = steady_clock::now();
            t = duration_cast<secs>(t_fineFunzione - t_inizioFunzione).count(); //calcolo il tempo di esecuzione
            count++; //tengo traccia del numero di iterazioni fatte
        } while(t < t_minimo);
        cout << (t / count) - (tempoPreparazioneStringa[i] * count) << endl; //calcolo il tempo medio di esecuzione dividento il tempo totale per il numero di esecuzioni fatte
        count = 0;
    }
}