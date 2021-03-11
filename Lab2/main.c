#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"

#define N 3

void print_mx(char *mx_name, float **arr,int mx_size);
void fileprint_mx(FILE *plik,char *mx_name, float **arr,int mx_size);


int main(){


  float **A = matrix(1,N,1,N);
  float **B = matrix(1,N,1,N);


  int x = 1;

  for(int i = 1; i <= N; i++){
    for(int j = 1; j<=N; j++){
      A[i][j] = x;
      B[i][j] = x;
      x++;
    }
  }

  B[1][1] = 1.1;

  FILE *plik = fopen("plik.txt", "w");

  print_mx("Macierz A",A,N);
  print_mx("Macierz B",B,N);
  fileprint_mx(plik,"Macierz A",A,N);
  fileprint_mx(plik,"Macierz B",B,N);

  int *indexA = ivector(1,N);
  int *indexB = ivector(1,N);

  float da;
  float db;

  float **X = matrix(1,N,1,N);
  float **Y = matrix(1,N,1,N);

  for(int i = 1; i <= N; i++){
    for(int j = 1; j<=N; j++){
      X[i][j] = A[i][j];
      Y[i][j] = B[i][j];
      
    }
  }
  
  ludcmp(X,N,indexA,&da);
  ludcmp(Y,N,indexB,&db);
  
  
  float **LA = matrix(1,N,1,N);
  float **LB = matrix(1,N,1,N);
  float **UA = matrix(1,N,1,N);
  float **UB = matrix(1,N,1,N);
  

  for(int i = 1; i <= N; i++){
    for(int j = 1; j<=N; j++){
       if(i == j){
          LA[i][j] = LB[i][j] = 1;   
          UA[i][j]= X[i][j];
          UB[i][j]= Y[i][j];
       }else if(i<j){
         LA[i][j] = LB[i][j] = 0;
          UA[i][j]= X[i][j];
          UB[i][j]= Y[i][j];
       }else{
          LA[i][j] = X[i][j];
          LB[i][j] = Y[i][j];
         
       }

    }
  }


 

 
  print_mx("Macierz LA",LA,N);
  print_mx("Macierz UA",UA,N);
  print_mx("Macierz LB",LB,N);
  print_mx("Macierz UB",UB,N);
  fileprint_mx(plik,"Macierz LA",LA,N);
  fileprint_mx(plik,"Macierz UA",UA,N);
  fileprint_mx(plik,"Macierz LB",LB,N);
  fileprint_mx(plik,"Macierz UB",UB,N);

  float *a1 = vector(1,N);
  float *a2 = vector(1,N);
  float *a3 = vector(1,N);
  float *b1 = vector(1,N);
  float *b2 = vector(1,N);
  float *b3 = vector(1,N);

  a1[1] = 1; 
  a1[2] = 0;
  a1[3] = 0;

  a2[1] = 0; 
  a2[2] = 1;
  a2[3] = 0;

  a3[1] = 0; 
  a3[2] = 0;
  a3[3] = 1;

  b1[1] = 1; 
  b1[2] = 0;
  b1[3] = 0;

  b2[1] = 0; 
  b2[2] = 1;
  b2[3] = 0;

  b3[1] = 0; 
  b3[2] = 0;
  b3[3] = 1;

  lubksb(X,N,indexA,a1);
  lubksb(X,N,indexA,a2);
  lubksb(X,N,indexA,a3);
  lubksb(Y,N,indexB,b1);
  lubksb(Y,N,indexB,b2);
  lubksb(Y,N,indexB,b3);

  float **A_odwrotna = matrix(1,N,1,N);
  float **B_odwrotna = matrix(1,N,1,N);

  for(int i = 1; i <= N ; i++){
    A_odwrotna[i][1] = a1[i];
    A_odwrotna[i][2] = a2[i];
    A_odwrotna[i][3] = a3[i];
    B_odwrotna[i][1] = b1[i];
    B_odwrotna[i][2] = b2[i];
    B_odwrotna[i][3] = b3[i];
  }

  print_mx("Macierz A^-1",A_odwrotna,N);
  print_mx("Macierz B^-1",B_odwrotna,N);
  fileprint_mx(plik,"Macierz A^-1",A_odwrotna,N);
  fileprint_mx(plik,"Macierz B^-1",B_odwrotna,N);


  float **iloczyn_A_A_odwrotna = matrix(1,N,1,N);
  float **iloczyn_B_B_odwrotna = matrix(1,N,1,N);

  


  int k;

   for(int i = 1; i<=N; i++){
      for(int j = 1; j<=N; j++){
        iloczyn_A_A_odwrotna[i][j] = 0;
        iloczyn_B_B_odwrotna[i][j] = 0;
          for(k = 1; k<=N;k++){
            iloczyn_A_A_odwrotna[i][j] += A[i][k]*A_odwrotna[k][j];
            iloczyn_B_B_odwrotna[i][j] += B[i][k]*B_odwrotna[k][j];
          }

      }
    
    }



  print_mx("Macierz A*A^-1",iloczyn_A_A_odwrotna,N);
  print_mx("Macierz b*B^-1",iloczyn_B_B_odwrotna,N);
  fileprint_mx(plik,"Macierz A*A^-1",iloczyn_A_A_odwrotna,N);
  fileprint_mx(plik,"Macierz B*B^-1",iloczyn_B_B_odwrotna,N);

  fclose(plik);

  free_matrix(A,1,N,1,N);
  free_matrix(B,1,N,1,N);
  free_matrix(X,1,N,1,N);
  free_matrix(Y,1,N,1,N);
  free_matrix(LA,1,N,1,N);
  free_matrix(LB,1,N,1,N);
  free_matrix(UA,1,N,1,N);
  free_matrix(UB,1,N,1,N);
  free_matrix(A_odwrotna,1,N,1,N);
  free_matrix(B_odwrotna,1,N,1,N);
  free_matrix(iloczyn_A_A_odwrotna,1,N,1,N);
  free_matrix(iloczyn_B_B_odwrotna,1,N,1,N);

  free_vector(a1,1,N);
  free_vector(a2,1,N);
  free_vector(a3,1,N);
  free_vector(b1,1,N);
  free_vector(b2,1,N);
  free_vector(b3,1,N);

  free_ivector(indexA,1,N);
  free_ivector(indexB,1,N);


}


void print_mx(char *mx_name, float **arr,int mx_size){

  printf("\n%s\n", mx_name);

  for(int i = 1; i <= mx_size; i++){
    for(int j = 1; j<=mx_size; j++){
      printf("%12g\t",arr[i][j]);
      
    }
    printf("\n");
  }

}


void fileprint_mx(FILE *plik,char *mx_name, float **arr,int mx_size){
  fprintf(plik,"\n%s\n", mx_name);

  for(int i = 1; i <= mx_size; i++){
    for(int j = 1; j<=mx_size; j++){
      fprintf(plik,"%12g\t",arr[i][j]);
      
    }
    fprintf(plik,"\n");
  }
}