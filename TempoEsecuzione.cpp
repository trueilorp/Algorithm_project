#include <iostream>
#include <random>
#include <string>
#include <math.h>
#include <chrono> 
#include "Header.h"

using namespace std;
using namespace std::chrono; 
typedef duration<double, seconds::period> secs;

#define E 0.001 //Errore relativo massimo ammissibile

/**
 * @brief Stimo il clock di sistema
 */
double getResolution(){
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do{
        end = steady_clock::now();
    }while (start == end);
    return duration_cast<secs>(end - start).count();
}

/**
 * @brief Calcolo il tempo minimo misurabile con la formula --> T_min = R⋅(1/E+1).
 */
double tempoMinimoMisurabile(){
    double R = getResolution();
    double t_minimo = R*((1/E) + 1);
    return t_minimo;
}

/**
 * @brief Stimo quando tempo ci impiego a preparare una stringa
 * @param tempiMedi array di double dove memorizzo il tempo medio di preparazione per ogni lunghezza di stringa
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

/**
 * @brief Calcolo il tempo che l'algoritmo (Naive o Smart) ci impiega per restituire il periodo frazionario
 * di una determinata stringa 
 */
void calcolaTempo(){
    steady_clock::time_point t_inizioFunzione, t_fineFunzione;
    double t, t_minimo;
    int count = 0, k = 0;

    double tempoPreparazioneStringa[100];
    stimaTempoPreparazioneStringa(tempoPreparazioneStringa);
    
    for(int i = 0; i < 100; i++){
        t_minimo = tempoMinimoMisurabile();
        t_inizioFunzione = steady_clock::now();
        do{
            string s = preparaStringa(i);
            k = periodSmart(s); //periodNaiveConCompare(s)
            t_fineFunzione = steady_clock::now();
            t = duration_cast<secs>(t_fineFunzione - t_inizioFunzione).count(); 
            count++;
        } while(t < t_minimo);
        cout << (t / count) - (tempoPreparazioneStringa[i] * count) << endl; 
        count = 0;
    }
}