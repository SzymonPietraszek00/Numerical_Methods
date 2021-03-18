#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define N 2000
#define v0 0
#define x0 1
#define maleomega 1

FILE *plik = fopen("out1.dat", "w");

int main(){

  double h = 0.02;
  

  double beta = 0.0, F0 = 0.0, omega = 0.8;
  // double beta = 0.4, F0 = 0.0, omega = 0.8;
  // double beta = 0.4, F0 = 0.1, omega = 0.8;

  double *d0 = new double[N+1];
  double *d1 = new double[N+1];
  double *d2 = new double[N+1];
  double *b = new double[N+1];
  double *xs = new double[N+2];
  double *xn = new double[N+1];

  double a1 = 1.0;
  double a3 = 1 + beta * h;
  double a2 = maleomega * maleomega * h * h - 2 - beta*h;



  for(int i = 2; i < N; i++){
    
    b[i] = F0 * sin(omega * h * i) * h * h;

    d0[i] = a3;
    d1[i] = a2;
    d2[i] = a1;
  }

  d0[0] = 1.0; d0[1] = 1.0;
  d1[0] = 0.0; d1[1] = -1.0;
  d2[0] = 0.0; d2[1] = 0.0;
  b[0] = 1.0; b[1] = 0.0;


  for(int i = 0; i <5; i++)
  std::cout << d0[i] << " " << d1[i] << " " << d2[i] << " " << b[i] << std::endl;


  std::cout << "a1=" <<  a1 << " a2=" << a2 << " a3=" << a3 << std::endl;

  for(int i =0; i<=N; i++){
    xs[i] = xn[i] = 1;
    
  }

  xs[0] = 0.65;
  xs[N+1] = 0;

  xs = xs+2;

  double sn = 0,ss = 0;
  
  int it = 1;

  while(it < 10000){

    for(int i = 0; i <=N; i++){
      xn[i] = (1/d0[i]) * (b[i] - d1[i] *xs[i-1] - d2[i] * xs[i-2]);
       sn = sn + pow(xn[i],2);
      ss = ss + pow(xs[i],2);
    }

    
    if(fabs(sn - ss) < pow(10,-6)) break;

    for(int i = 0; i <=N; i++){
      xs[i] = xn[i];
    }

    it++;
  }
    


    double x = 0;
    for(int i = 0; i <=N; i++){
      fprintf(plik, "%f %f\n", x, xn[i]);
      x = x + h;
    }
  

  fclose(plik);

  xs = xs-2;

  delete [] d0;
  delete [] d1;
  delete [] d2;
  delete [] b;
  delete [] xs;
  delete [] xn;

  
}