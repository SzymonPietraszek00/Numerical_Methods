#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "nrutil.h"

#define N 200 // rozmiar macierzy M: NxN
int main(void)
{

	 float **M, **b;

	 //	Alokacja macierzy
	 M = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);


  int A = 1;
  int v0 = 0;
  float h = 0.1;
  int omega = 1;
  
  	for (int i = 1; i <= N; i++){
      	for (int j = 1; j <= N; j++){

          if(i == j||i == j+2) M[i][j] = 1;
          if(i == j+1) M[i][j] = omega*omega*h*h-2;

        }
    }
    
    b[1][1] = A;
    b[1][2] = v0*h;
    M[2][1] = -1;

	//	Rozwiazanie ukladu rownan Mx=b - wywolanie procedury:
	gaussj(M, N, b, 1);

	//	Wypisanie rozwiazania, ktore procedura gaussj(M, N, b, 1); zapisala w wektorze b.
	for (int i = 1; i <= N; ++i)
		printf("%.6f %.6f\n",h*i ,b[i][1]);

	//	Zwolnienie pamieci
	free_matrix(M, 1, N, 1, N);
	free_matrix(b, 1, N, 1, 1);

	return 0;
}






