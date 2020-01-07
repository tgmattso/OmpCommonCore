//
//  Strassen matrix multiplication
//
// HISTORY: orignial program provided by Clay Breshears
//

#include <stdio.h>   
#include <stdlib.h>  
#include <omp.h>
#include "2DArray.h"

#define MM 1000
#define NN 1000
#define PP 1000
#define THRESHOLD  8192 /* product size below which matmultleaf is used */  

double dabs(double d){return (d<0.0?d:(-d));}

void seqMatMult(int m, int n, int p, double** A, double** B, double** C)   
{    
  for (int i = 0; i < m; ++i)   
      for (int k = 0; k < p; ++k)   
         for (int j = 0; j < n; ++j)    
            C[i][j] += A[i][k]*B[k][j];   
}  
  
void matmultleaf(int ml, int nl, int pl, double **A, double **B, double **C)    
/*  
  subroutine that uses the simple triple loop to multiply  
  a submatrix from A with a submatrix from B and store the  
  result in a submatrix of C.   
*/  
// 0 ml; /* first and last+1 i index */  
// 0 nl; /* first and last+1 j index */  
// 0 pl; /* first and last+1 k index */  
{      
   for (int i = 0; i < ml; ++i)   {
      for (int l = 0; l < nl; ++l) 
         C[i][l] = 0.0;  // for temp matrices during Strassen
      for (int k = 0; k < pl; ++k)   
         for (int j = 0; j < nl; ++j) 
            C[i][j] += A[i][k]*B[k][j];  
   } 
}   
  

void copyQtrMatrix(double **X, int m, double **Y, int mf, int nf)
// pointer copy from original data for quarter matrix
{
   for (int i = 0; i < m; ++i) 
      X[i] = &Y[mf+i][nf];
}

void AddMatBlocks(double **T, int m, int n, double **X, double **Y)
// Add matrices X(m,n) to Y(m,n) and store in T
{
   for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
         T[i][j] = X[i][j] + Y[i][j];
}

void SubMatBlocks(double **T, int m, int n, double **X, double **Y)
// Subtract matrix Y(m,n) from X(m,n) and store in T
{
   for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
         T[i][j] = X[i][j] - Y[i][j];
}


void strassenMMult(double **C, double **A, double **B, int ml, int pl, int nl)
{
//
// Check sizes of matrices;
// if below threshold then compute product w/o recursion
//
   if (((float)ml)*((float)nl)*((float)pl) < THRESHOLD)   
      matmultleaf(ml, nl, pl, A, B, C); 

   else {
//
// Apply OpenMP tasks to the eight recursive calls below
//   be sure to not create data races between tasks
//
      int m2 = ml/2;
      int n2 = nl/2;
      int p2 = pl/2;

      double **S1 = Allocate2DArray< double >(m2, p2);
      double **S2 = Allocate2DArray< double >(m2, p2);
      double **S3 = Allocate2DArray< double >(m2, p2);
      double **S4 = Allocate2DArray< double >(m2, p2);
      double **S5 = Allocate2DArray< double >(p2, n2);
      double **S6 = Allocate2DArray< double >(p2, n2);
      double **S7 = Allocate2DArray< double >(p2, n2);
      double **S8 = Allocate2DArray< double >(p2, n2);
      
      double **M1 = Allocate2DArray< double >(m2, n2);
      double **M2 = Allocate2DArray< double >(m2, n2);
      double **M3 = Allocate2DArray< double >(m2, n2);
      double **M4 = Allocate2DArray< double >(m2, n2);
      double **M5 = Allocate2DArray< double >(m2, n2);
      double **M6 = Allocate2DArray< double >(m2, n2);
      double **M7 = Allocate2DArray< double >(m2, n2);

      double **T1 = Allocate2DArray< double >(m2, n2);
      double **T2 = Allocate2DArray< double >(m2, n2);

      double **A11 = new double*[m2];
      double **A12 = new double*[m2];
      double **A21 = new double*[m2];
      double **A22 = new double*[m2];

      double **B11 = new double*[p2];
      double **B12 = new double*[p2];
      double **B21 = new double*[p2];
      double **B22 = new double*[p2];

      double **C11 = new double*[m2];
      double **C12 = new double*[m2];
      double **C21 = new double*[m2];
      double **C22 = new double*[m2];

      copyQtrMatrix(A11, m2, A,  0,  0);
      copyQtrMatrix(A12, m2, A,  0, p2);
      copyQtrMatrix(A21, m2, A, m2,  0);
      copyQtrMatrix(A22, m2, A, m2, p2);

      copyQtrMatrix(B11, p2, B,  0,  0);
      copyQtrMatrix(B12, p2, B,  0, n2);
      copyQtrMatrix(B21, p2, B, p2,  0);
      copyQtrMatrix(B22, p2, B, p2, n2);

      copyQtrMatrix(C11, m2, C,  0,  0);
      copyQtrMatrix(C12, m2, C,  0, n2);
      copyQtrMatrix(C21, m2, C, m2,  0);
      copyQtrMatrix(C22, m2, C, m2, n2);

      // S1 = A21 + A22
      AddMatBlocks(S1, m2, p2, A21, A22);

      // S2 = S1 - A11
      SubMatBlocks(S2, m2, p2, S1, A11);

      // S3 = A11 - A21
      SubMatBlocks(S3, m2, p2, A11, A21);
      
      // S4 = A12 - S2
      SubMatBlocks(S4, m2, p2, A12, S2);

      // S5 = B12 - B11
      SubMatBlocks(S5, p2, n2, B12, B11);

      // S6 = B22 - S5
      SubMatBlocks(S6, p2, n2, B22, S5);

      // S7 = B22 - B12
      SubMatBlocks(S7, p2, n2, B22, B12);
      
      // S8 = S6 - B21
      SubMatBlocks(S8, p2, n2, S6, B21);

      // M1 = S2 * S6
      strassenMMult(M1, S2,  S6,  m2, p2, n2);

      // M2 = A11 * B11
      strassenMMult(M2, A11, B11, m2, p2, n2);

      // M3 = A12 * B21
      strassenMMult(M3, A12, B21, m2, p2, n2);

      // M4 = S3 * S7
      strassenMMult(M4, S3,  S7,  m2, p2, n2);
      
      // M5 = S1 * S5
      strassenMMult(M5, S1,  S5,  m2, p2, n2);

      // M6 = S4 * B22
      strassenMMult(M6, S4,  B22, m2, p2, n2);

      // M7 = A22 * S8
      strassenMMult(M7, A22, S8,  m2, p2, n2);

      // T1 = M1 + M2
      AddMatBlocks(T1, m2, n2, M1, M2);

      // T2 = T1 + M4
      AddMatBlocks(T2, m2, n2, T1, M4);

      // C11 = M2 + M3
      // C12 = T1 + M5 + M6
      // C21 = T2 - M7
      // C22 = T2 + M5

      for (int i = 0; i < m2; ++i)
         for (int j = 0; j < n2; ++j) {
            C11[i][j] = M2[i][j] + M3[i][j];
            C12[i][j] = T1[i][j] + M5[i][j] + M6[i][j];
            C21[i][j] = T2[i][j] - M7[i][j];
            C22[i][j] = T2[i][j] + M5[i][j];
         }

      Free2DArray< double >(S1);
      Free2DArray< double >(S2);
      Free2DArray< double >(S3);
      Free2DArray< double >(S4);
      Free2DArray< double >(S5);
      Free2DArray< double >(S6);
      Free2DArray< double >(S7);
      Free2DArray< double >(S8);

      Free2DArray< double >(M1);
      Free2DArray< double >(M2);
      Free2DArray< double >(M3);
      Free2DArray< double >(M4);
      Free2DArray< double >(M5);
      Free2DArray< double >(M6);
      Free2DArray< double >(M7);

      Free2DArray< double >(T1);
      Free2DArray< double >(T2);

      delete[] A11; delete[] A12; delete[] A21; delete[] A22;
      delete[] B11; delete[] B12; delete[] B21; delete[] B22;
      delete[] C11; delete[] C12; delete[] C21; delete[] C22;
   }
}
              
//
//  "Helper" function to intialize C and start recursive routine
//
void matmultS(int m, int n, int p, double **A, double **B, double **C)
{   
    strassenMMult(C, A, B, m, n, p);
}  


int CheckResults(int m, int n, double **C, double **C1)
{
#define ERR_THRESHOLD 0.001
//
//  May need to take into consideration the floating point roundoff error
//    due to parallel execution
//
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dabs(C[i][j] - C1[i][j]) > ERR_THRESHOLD ) {
        printf("%f  %f\n", C[i][j], C1[i][j]);
        return 1;
      }
    }
  }
  return 0;
}


  
int main(int argc, char* argv[])   
{      
  double before, time1, time2;
  int M = MM;
  int N = NN;
  int P = PP;

//
// If 3 values on command line, use those for matrix sizes
//
// Best to use values that are evenly divisible by 2 up to the THRESHOLD size
//
 
  if (argc != 4) {
          printf("Suggested Usage: %s <M> <N> <P> \n", argv[0]);
     printf("Using default values\n");
  }
  else {
     M = atoi(argv[1]);
     N = atoi(argv[2]);
     P = atoi(argv[3]);
  }

  double **A = Allocate2DArray< double >(M, P);
  double **B = Allocate2DArray< double >(P, N);
  double **C = Allocate2DArray< double >(M, N);
  double **C4 = Allocate2DArray< double >(M, N);

  int i, j;   

//
// Initialize with random values
//
  for (i = 0; i < M; ++i) {   
    for (j = 0; j < P; ++j) {   
      A[i][j] = 5.0 - ((double)(rand()%100) / 10.0);  
    }      
  }   

  for (i = 0; i < P; ++i) {   
    for (j = 0; j < N; ++j) {   
      B[i][j] = 5.0 - ((double)(rand()%100) / 10.0);   
    }      
  }   

  for (i = 0; i < M; ++i) {   
    for (j = 0; j < N; ++j) {   
      C[i][j] = 0.0;
      C4[i][j] = 0.0;
    }      
  }   

  printf("Execute Standard matmult  M = %d  N = %d  P = %d\n\n", M, N, P);
  before = omp_get_wtime();
  seqMatMult(M, N, P, A, B, C);
  time1 = omp_get_wtime() - before;
  printf("Standard matrix function done in %7.2f secs\n\n\n",(float)time1);

  before = omp_get_wtime();
  matmultS(M, N, P, A, B, C4);
  time2 = omp_get_wtime() - before;
  printf("Strassen matrix function done in %7.2f secs\n\n\n",time2);

   printf("Checking...");
   if (CheckResults(M, N, C, C4))
     printf("Error in Recursive Matrix Multiplication\n\n");
   else {
     printf("OKAY\n\n");
     printf("Speedup = %5.1fX\n", time1/time2);
   }

  Free2DArray< double >(A);
  Free2DArray< double >(B);
  Free2DArray< double >(C);
  Free2DArray< double >(C4);

  return 0;   
}  
