#include "triFusion.h"
#include <stdio.h>

//--------------------------------------------------
void fusion(int T[], int N, int S[], int M, int TS[]) {
  int t,s,ts; //indices des tableaux T, S et TS

  //initialisation des indices a zero
  t=0;
  s=0;
  ts=0;

  //tant que les deux tableaux d'entree ne sont pas termines
  while ((t < N) && (s < M))
    {
      if (T[t] < S[s])
	{//on avance dans T
	  TS[ts]=T[t];
	  t++;
	}
      else
	{//on avance dans S
	  TS[ts]=S[s];
	  s++;
	}
      ts++;
    }
  //on a fini un des deux tableaux
  //on a soit t>=N soit s>=N
  // il suffit de remplir TS avec le tableau 
  // dont on a pas atteint la fin
  while (t < N)
    {
      TS[ts]=T[t];
      t++;
      ts++;
    }
  while (s < M)
    {
      TS[ts]=S[s];
      s++;
      ts++;
    }
}

void triFusion(int d[], int N) {
  if(N == 1) {
    return;
  } 
  int a = N/2;
  if(N%2 == 1) {
   a = N/2+1; 
  }

  //u = malloc(N/2 * sizeof(int));
  //v = malloc(a * sizeof(int));
  int u[N/2];
  int v[a];
  //if((!u) || (!v)) {
  //  printf("erreur !\n");
  //  return;
  //}

  int i;
  for (i = 0; i < N/2; i++) {
    u[i] = d[i];
  }

  for (i = 0; i < a; i++) {
    v[a] = d[N/2+i];
  }

  triFusion(u, N/2);
  triFusion(v, a);
  fusion(u, N/2, v, a, d);
}


