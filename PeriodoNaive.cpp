/**
 * @file PERIODONAIVE
 * @author DARIO SIMONE, MONTE STEFANO
 * @date 2023-03-01
 */

#include <iostream>
#include <string>

using namespace std;

int periodNaive(string s){
  int p=1;
  int ps=0;

  for (int i=0; i<=s.length(); i++){
      for (int j=i+1; j<=s.length(); j++){
          if(s[i] != s[j]){
              p++;
          }
          if(ps < p){
               ps = p;
          }else{
            p=0;
          }
      }
      p=0;
  }  
  return ps;
}



