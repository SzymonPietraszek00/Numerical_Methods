#include <iostream>
#include <cmath>
#include <stdio.h>

#define N 7
#define IT_MAX 12

void macierz_vector(double macierz[N][N], double vector[N], double vectorwynik[N]){


  double x = 0;
  for(int i = 0; i < N; i++){

    x = 0;

    for(int j = 0; j < N; j++){

      x+= macierz[i][j] * vector[j];

    }

    vectorwynik[i] = x;
  }
}


double vector_vector(double vector[N], double vector2[N]){


  double iloczyn = 0;

  for( int i = 0; i < N; i++){

    iloczyn += vector[i] * vector2[i];
  }
  
  return iloczyn;
}

void vect_vect(double vector[N], double vector2[N]){


  double x = 0;

  for( int i = 0; i < N; i++){

    x += vector2[i] * vector2[i];
  }

  x = sqrt(x);

  for( int i = 0; i < N; i++){
    vector[i] = vector2[i] / x;
  }

}

void check(double matrix[N][N], double lamb, double vector[N]){

  for(int i = 0; i<N; i++){

    for(int j = 0; j<N; j++)
        matrix[i][j] = matrix[i][j] - lamb * vector[i] * vector[j];

  }

}

void matrix_matrix(double matrixResult[N][N], double matrixA[N][N], double matrixB[N][N]){

  for(int i = 0; i < N; i++){

    for(int j = 0; j < N; j++){

      double x = 0;
      matrixResult[i][j] = 0;

      for(int k = 0; k < N; k++){


        x +=  matrixResult[i][j] + matrixA[i][k] * matrixB[k][j]; 

      }

      matrixResult[i][j] = x;


    }



  }


}

int main(){

  FILE *plik1 = fopen("lambda.dat", "w");
  FILE *plik2= fopen("plik2.txt", "w");

  double macierzA[N][N];

  double macierzW0[N][N];

  double macierzX[N][N];

  double macierzD[N][N];

  double vectorX[N];

  double vectorX2[N];

  double lambda;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){

      macierzW0[i][j] = macierzA[i][j] = (1 / sqrt(2 + abs(i-j)));
     
    } 
    
  }

  for(int k = 0; k < N; k++){

    for(int i = 0; i < N; i++){

      vectorX[i] = 1;

    }

    for(int i = 1; i <= IT_MAX; i++){

      macierz_vector(macierzW0, vectorX, vectorX2);

      lambda = vector_vector(vectorX, vectorX2) / vector_vector(vectorX, vectorX);

      vect_vect(vectorX,vectorX2);

      fprintf(plik1, "%d %lf\n",i,lambda);
    }


    fprintf(plik1, "\n\n");

    check(macierzW0,lambda,vectorX);

    for(int i = 0; i < N; i++){

      macierzX[i][k] = vectorX[i];
    }
  }

  double macierzX_T[N][N];
 

 
  double macierzD_Temp[N][N];

  //transponowanie
  for(int i = 0; i<N; i++)
    for(int j = 0; j<N; j++)
      macierzX_T[j][i] = macierzX[i][j];





  matrix_matrix(macierzD_Temp,macierzX_T,macierzA);
  matrix_matrix(macierzD,macierzD_Temp,macierzX);


  for(int i = 0; i<N; i++){

    for(int j = 0; j<N; j++){

      fprintf(plik2,"%15g\t", macierzD[i][j] );
    }

    fprintf(plik2,"\n");
  }

  fclose(plik1);
  fclose(plik2);
}