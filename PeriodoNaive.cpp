/**
 * @file PERIODONAIVE
 * @author DARIO SIMONE, MONTE STEFANO
 * @date 2023-03-01
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

int periodNaive (string s)
{
  int p=1;
  int ps=0;

  for (int i=0; i<=s.length(); i++) 
  {
      for (int j=i+1; j<=s.length(); j++)
      {
          if(s[i] != s[j])
          {
              p++;
          }
          if(ps < p)
            {
               ps = p;
            }
            else{
            p=0;}
      }
      p=0;
  }  
  return ps;
}

int main()
{
  string s;
  cout << "Inserire stringa:";
  cin >> s;

  printf("%d ", periodNaive(s));
  return 0;
}

/*
int main()
{
  char s[1000];
  int p=1;
  int ps=0;
  printf("Inserire stringa: \n");
  scanf( "%s", s);

  for (int i=0; i<=strlen(s); i++) 
  {
      for (int j=i+1; j<=strlen(s); j++)
      {
          if(s[i] != s[j])
          {
              p++;
          }
          else
          {
            if(ps < p)
            {
               ps = p;
            }
            p=0;
          }
      }
      p=0;
  }
  printf("%d ", ps);
  return 0;
}*/