#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>



int main(){

  double h;
  double xMin = -5.0, xMax = 5.0;

  std::ofstream file1;
  std::ofstream file2;
  file1.open("czebyszewA.dat");
  file2.open("czebyszewB.dat");


  for(int n = 5; n <= 20; n+=5){

    double *x = new double[n+1];
    double **y = new double*[n+1];

    h = (xMax - xMin) / n ;



      

    for(int i = 0; i < n+1; i++){

      y[i] = new double[n+1];
      // x[i] = xMin + i * h;
      x[i] = ((xMin - xMax) * cos(M_PI * (2.0 * i + 1.0)/ (2.0 * n + 2.0)) + (xMin + xMax)) / 2.0;
      y[i][0] = 1.0 / (1.0 + pow(x[i], 2));
      
      file1 << x[i] << "  " << y[i][0] << std::endl;

    }


    for(int j = 1; j < n+1; j++){

      for(int i = j; i < n+1; i++){

        y[i][j] = (y[i][j-1] - y[i-1][j-1]) / (x[i] - x[i-j]);
      }
    }


    for(double i = xMin; i <= xMax; i += 0.01){

      double temp = 1.0;
      double ret = 0.0;

      for(int j = 0; j < n+1; j++){

        temp = 1.0;

        for(int k = 0; k < j; k++){

          temp = temp * (i-x[k]);
        }

        ret += y[j][j] * temp;
      }

      file2 << i << "  " << ret << "  \n";
    }

    file2 << "\n\n";


    delete [] x;

    for(int i = 0; i < n+1; i++){
      delete [] y[i];
    }

    delete [] y;


  }


  file1.close();
  file2.close();

  return 0;
}