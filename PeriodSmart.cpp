#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

/*
p=periodo di s 
t=bordo di s 
lunghezza del bordo = n-p
s stringa di lunghezza n, t1,...,tk tutti i bordi di s ordinati per lunghezza decrescente 

sia s una stringa e a un carattere (come passiamo da s a s - a, ovvero s estesa con un carattere a)
allora t' è un bordo di s - a  ->> 
->> t'=epsilon 
->> t'=t-a, t è un bordo di s
->> s[t]=a

s |------------| - a
t'|---a|        |---a|
t |--|a         |--|a 

Corollario:
s[0 ... n-1] stringa
per i che va da 1 a n
r[i] è la massima lunghezza di un bordo del prefisso s[0, .., i-1]
Allora ->>
->> r[i+1] = 0 se non esiste k t.c. s[r^k[i]]=s[i]
             r^k0[i]+1 se esiste k t.c. s[r^k[i]]=s[i] & k0 = minimo di questi k

r^k[i]= se k=1 -> r[i]
      se k>1 -> r^(k-1) [r[i]]




s = a b a a b a a b
t1 = bordo1 = ab 
t2 = bordo2 = abaab
t3 = bordo3 = abbab

Pseudocodice per calcolare il bordo massimo
maxBorder(s)
{
    n=s; =lunghezza stringa
    r[1...n]=nuovo array
    r[1]=0
    for i=1 fino a n-1 //calcolo r[i+1]
    {
        z=r[i]  //invariante z=r^k[i]
        while(s[z]!=s[i] & z>0)
        {
            z=r[z] //z<i sempre 
        }
        if (s[z]=s[i])
        {
            r[i+1]=z+1
        }else
        {
            r[i+1]=0
        }
    }
    return r[n]
}
*/

int periodSmart(string s)
{
    int n = s.length();
    int r[n+1]; //inizializzo un array che mi serve per memorizzare i bordi
    r[1] = 0;
    //calcolo r(i+1) basandomi sui valori che ho calcolato in precendenza --> r(1), r(2)...

    //prima devo cercare un bordo z di s[1...i] che soddisfi s[i+1] = s[z+1] e z deve essere massimo
    for(int i=1; i<n;i++) //calcolo r[i+1]
    { 
        int z = r[i];  //invariante z=r^k[i]
        while((s[i+1] != s[z+1]) && z>0){
            //ovvero mentre la condizione non è soddisfatta mi vado a cercare il bordo più piccolo
            z = r[z]; //z<i sempre 
        }
        if (s[i+1] == s[z+1])
        {
            r[i+1] = z+1;
        }else
        {
            r[i+1] = 0;
        }
    }
    int p = n - r[n];
    return p; // che è il bordo massimo di s
}

