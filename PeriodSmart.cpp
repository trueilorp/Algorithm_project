#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Calcola il periodo frazionario in tempo lineare sfruttando la definizione di bordo massimo
 * @param s stringa ricevuta in input
 * @return periodo frazionario
 */
int periodSmart(string s)
{
    int n = s.length();
    int r[n+1];
    r[1] = 0;
    
    for(int i=1; i<n;i++){ 
        int z = r[i];
        while((s[i+1] != s[z+1]) && z>0){

        }
        if (s[i+1] == s[z+1]){
            r[i+1] = z+1;
        }else{
            r[i+1] = 0;
        }
    }
    int p = n - r[n];
    return p; 
}

