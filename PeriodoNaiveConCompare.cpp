#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

/**
 * @brief Calcolo del periodo frazionario con string compare
 * @param s stringa ricevuta in input
 * @return periodo frazionario
 */
int periodNaiveConCompare(string s){
    int n = s.length();
    for (int p=1; p<=n; p++){
        string s1= s.substr(0, n-p);
        string s2= s.substr(p, n-p);
        if(s1.compare(s2) == 0){
            return p;
        }
    }
    return n; // return di errore
}
